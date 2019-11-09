//
// Created by liu on 17-6-29.
//

#include <sstream>
#include "simulation.h"

using namespace p3;

void MyException::make()
{
    for (int i = 1; i <= this->errNum; i++)
    {
        auto pos_1 = this->errStr[0].find('<');
        auto pos_2 = this->errStr[0].find('>');
        this->errStr[0].replace(pos_1, pos_2 - pos_1 + 1, this->errStr[i].c_str());
    }
}

inline const char *MyException::what() const noexcept
{
    return this->errStr[0].c_str();
}

MissingArgumentException::MissingArgumentException()
{
    this->errStr[0] = "Error: Missing arguments!\n";
    this->errStr[0] += "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]";
}

NegativeRoundException::NegativeRoundException()
{
    this->errStr[0] = "Error: Number of simulation rounds is negative!";
}

FailureFileException::FailureFileException(std::string filename)
{
    this->errStr[0] = "Error: Cannot open file <filename>!";
    this->errStr[++errNum] = filename;
    this->make();
}

TooManySpeciesException::TooManySpeciesException()
{
    this->errStr[0] = "Error: Too many species!\n";
    this->errStr[0] += "Maximal number of species is <MAXSPECIES>.";
    std::stringstream ss;
    ss << MAXSPECIES;
    ss >> this->errStr[++errNum];
    this->make();
}

TooManyInstructionException::TooManyInstructionException(std::string SPECIES_NAME)
{
    this->errStr[0] = "Error: Too many instructions for species <SPECIES_NAME>!\n";
    this->errStr[0] += "Maximal number of instructions is <MAXPROGRAM>.";
    this->errStr[++errNum] = SPECIES_NAME;
    std::stringstream ss;
    ss << MAXPROGRAM;
    ss >> this->errStr[++errNum];
    this->make();
}

UnknownInstructionException::UnknownInstructionException(std::string UNKNOWN_INSTRUCTION)
{
    this->errStr[0] = "Error: Instruction <UNKNOWN_INSTRUCTION> is not recognized!";
    this->errStr[++errNum] = UNKNOWN_INSTRUCTION;
    this->make();
}

IllegalHeightException::IllegalHeightException()
{
    this->errStr[0] = "Error: The grid height is illegal!";
}

IllegalWidthException::IllegalWidthException()
{
    this->errStr[0] = "Error: The grid width is illegal!";
}

UnknownTerrainException::UnknownTerrainException(const point_t &p, char terrain)
{
    this->errStr[0] = "Error: Terrain square (<CHAR> <R> <C>) is invalid!";
    this->errStr[++errNum] = terrain;
    std::stringstream ss;
    ss << p.c << " " << p.r;
    ss >> this->errStr[++errNum] >> this->errStr[++errNum];
    this->make();
}

TooManyCreatureException::TooManyCreatureException()
{
    this->errStr[0] = "Error: Too many creatures!\n";
    this->errStr[0] += "Maximal number of creatures is <MAXCREATURES>.";
    std::stringstream ss;
    ss << MAXCREATURES;
    ss >> this->errStr[++errNum];
    this->make();
}

UnknownSpeciesException::UnknownSpeciesException(std::string UNKNOWN_SPECIES)
{
    this->errStr[0] = "Error: Species <UNKNOWN_SPECIES> not found!";
    this->errStr[++errNum] = UNKNOWN_SPECIES;
    this->make();
}

UnknownDirectionException::UnknownDirectionException(std::string UNKNOWN_DIRECTION)
{
    this->errStr[0] = "Error: Direction <UNKNOWN_DIRECTION> is not recognized!";
    this->errStr[++errNum] = UNKNOWN_DIRECTION;
    this->make();
}

OutsideBoundaryException::OutsideBoundaryException(Creature *creature)
{
    this->errStr[0] = "Error: Creature (<CREATURE>) is out of bound!\n";
    this->errStr[0] += "The grid size is <HEIGHT>-by-<WIDTH>.";
    this->errStr[++errNum] = creature->serialize();
    auto grid = creature->getWorld()->getGrid();
    std::stringstream ss;
    ss << grid->getHeight() << " " << grid->getWidth();
    ss >> this->errStr[++errNum] >> this->errStr[++errNum];
    this->make();
}

UnknownAbilityException::UnknownAbilityException(Creature *creature, std::string ability)
{
    this->errStr[0] = "Error: Creature (<CREATURE>) has an invalid ability <ABILITY>!";
    this->errStr[++errNum] = creature->serialize();
    this->errStr[++errNum] = ability;
    this->make();
}

OverlapCreatureException::OverlapCreatureException(Creature *newCreature, Creature *originCreature)
{
    this->errStr[0] = "Error: Creature (<CREATURE1>) overlaps with creature (<CREATURE2>)!";
    this->errStr[++errNum] = newCreature->serialize();
    this->errStr[++errNum] = originCreature->serialize();
    this->make();
}

CannotFlyException::CannotFlyException(Creature *creature)
{
    this->errStr[0] = "Error: Creature (<CREATURE>) is in a lake square!\n";
    this->errStr[0] += "The creature cannot fly!";
    this->errStr[++errNum] = creature->serialize();
    this->make();
}
