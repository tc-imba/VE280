//
// Created by liu on 17-6-29.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "simulation.h"

using namespace p3;

Controller::Controller(int argc, char *argv[])
{
    if (argc < 4)
    {
        throw MissingArgumentException();
    }
    std::stringstream(argv[3]) >> this->round_max;
    if (round_max < 0)
    {
        throw NegativeRoundException();
    }
    this->world = new World();
    this->verbose = false;
    if (argc > 4)
    {
        std::string str = argv[4];
        if (str == "v" || str == "verbose")
        {
            this->verbose = true;
        }
    }
}

void Controller::readSpecies(const std::string speciesPath)
{
    // Open the species summary file
    std::ifstream speciesSummary(speciesPath);
    std::string speciesDirectory;
    if (!speciesSummary.is_open())
    {
        throw FailureFileException(speciesPath);
    }
    speciesSummary >> speciesDirectory;
    while (!speciesSummary.eof())
    {
        // Open the files in the species directory
        std::string speciesName;
        speciesSummary >> speciesName;
        if (speciesName == "") continue;
        std::string speciesFullPath = speciesDirectory + "/" + speciesName;
        std::ifstream speciesFile(speciesFullPath);
        if (!speciesFile.is_open())
        {
            throw FailureFileException(speciesFullPath);
        }

        // Examine the number of current species before adding a new one
        if (this->world->numSpecies >= MAXSPECIES)
        {
            throw TooManySpeciesException();
        }

        // Create the species
        auto species = this->world->m_species[this->world->numSpecies++] = new Species(speciesName);
        std::stringstream ss;
        while (!speciesFile.eof())
        {
            std::string optionLine, optionStr;
            int optionAddress = 0;
            std::getline(speciesFile, optionLine);
            ss.clear();
            ss.str(optionLine);
            if (!ss.eof()) ss >> optionStr;
            if (optionStr == "") break;
            if (!ss.eof()) ss >> optionAddress;

            species->addInstruction(optionStr, optionAddress);

        }
        speciesFile.close();
    }
    speciesSummary.close();
}

/**
 * @version 2.0 Add terrains and abilities
 * @throws FailureFileException
 * @throws IllegalHeightException
 * @throws IllegalWidthException
 * @throws TooManyCreatureException
 * @param worldPath
 */
void Controller::readWorld(std::string worldPath)
{
    std::ifstream worldFile(worldPath);
    if (!worldFile.is_open())
    {
        throw FailureFileException(worldPath);
    }

    // Read height and width
    int height = 0, width = 0;
    worldFile >> height >> width;
    if (height <= 0 || height > MAXHEIGHT)
    {
        throw IllegalHeightException();
    }
    if (width <= 0 || width > MAXWIDTH)
    {
        throw IllegalWidthException();
    }
    this->world->grid.height = (unsigned) height;
    this->world->grid.width = (unsigned) width;

    // Read the terrain of each box, assuming that the format is correct
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char terrain;
            worldFile >> terrain;
            this->world->getGrid()->setTerrain(point_t{i, j}, terrain);
        }
    }

    // Read creatures
    std::stringstream ss;
    while (!worldFile.eof())
    {
        std::string worldLine;
        getline(worldFile, worldLine);
        if (worldLine == "")continue;
        if (this->world->numCreatures >= MAXCREATURES)
        {
            throw TooManyCreatureException();
        }
        ss.clear();
        ss.str(worldLine);
        std::string name, direction;
        int row, column;
        ss >> name >> direction >> row >> column;

        auto creature = new Creature(this->world, name, direction, row, column);
        this->world->m_creatures[this->world->numCreatures++] = creature;
        this->world->getGrid()->squares[row][column] = (creature_t *) creature;

        std::string ability;
        while (!ss.eof())
        {
            ss >> ability;
            if (ability.length() > 0) creature->addAbility(ability);
        }

        if (creature->isTerrain(LAKE) && !creature->ability[FLY])
        {
            throw CannotFlyException(creature);
        }
    }
}

void Controller::creatureMove(Creature *creature)
{
    if (creature->isTerrain(HILL) && !creature->ability[FLY] && !creature->hillActive)
    {
        creature->hillActive = true;
        return;
    }

    auto species = creature->getSpecies();
    auto programID = creature->programID;
    auto instruction = species->program[programID];
    switch (instruction.op)
    {
        case HOP:
            creature->hop();
            break;
        case LEFT:
            creature->left();
            break;
        case RIGHT:
            creature->right();
            break;
        case INFECT:
            creature->infect();
            break;
        case IFEMPTY:
            creature->ifempty(instruction.address);
            break;
        case IFENEMY:
            creature->ifenemy(instruction.address);
            break;
        case IFSAME:
            creature->ifsame(instruction.address);
            break;
        case IFWALL:
            creature->ifwall(instruction.address);
            break;
        case GO:
            creature->go(instruction.address);
            break;
        default:
            break;
    }
    if (this->verbose)
    {
        std::cout << std::endl << "Instruction " << programID + 1 << ":";
    }
    if (Species::isEndOption(instruction.op))
    {
        std::cout << " " << Species::getOptionName(instruction.op);
        if (creature->isTerrain(HILL) && !creature->ability[FLY])
        {
            creature->hillActive = false;
        }
    } else
    {
        if (this->verbose)
        {
            std::cout << " " << Species::getOptionName(instruction.op) << " " << instruction.address + 1;
        }
        creatureMove(creature);
    }
}

void Controller::simulateRound()
{
    std::cout << "Round " << (this->round + 1) << std::endl;
    for (int i = 0; i < this->world->numCreatures; i++)
    {
        std::cout << "Creature (" << this->world->m_creatures[i]->serialize() << ") takes action:";
        this->creatureMove(this->world->m_creatures[i]);
        std::cout << std::endl;
        if (this->verbose || i == this->world->numCreatures - 1)
        {
            std::cout << this->world->getGrid()->serialize();
        }
    }
}

void Controller::simulate()
{
    std::cout << "Initial state" << std::endl;
    std::cout << this->world->getGrid()->serialize();
    for (this->round = 0; this->round < this->round_max; this->round++)
    {
        this->simulateRound();
    }
}
