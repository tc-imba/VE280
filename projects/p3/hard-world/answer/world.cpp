//
// Created by liu on 17-6-29.
//

#include "simulation.h"

using namespace p3;

World::World()
{
    this->numCreatures = this->numSpecies = 0;
    Grid(this->grid);
}

inline Grid *World::getGrid() const
{
    return (Grid *) &this->grid;
}

inline Creature *World::addCreature(Creature *creature)
{
    this->getGrid()->addCreature(creature);
    return this->m_creatures[this->numCreatures++] = creature;
}

inline Creature *World::getCreature(const point_t &p) const
{
    return this->getGrid()->getCreature(p);
}

inline Creature *World::getCreature(const unsigned int &i) const
{
    return this->m_creatures[i];
}

inline Species *World::addSpecies(Species *species)
{
    return this->m_species[this->numSpecies++] = species;
}

Species *World::getSpecies(const std::string &name) const
{
    for (auto i = 0; i < this->numSpecies; i++)
    {
        if (name == this->m_species[i]->getName())
        {
            return this->m_species[i];
        }
    }
    return NULL;
}

inline int World::getCreatureNum() const
{
    return this->numCreatures;
}

inline int World::getSpeciesNum() const
{
    return this->numSpecies;
}