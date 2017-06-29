//
// Created by liu on 17-6-29.
//

#include "simulation.h"
using namespace p3;

World::World()
{
    this->numCreatures = this->numSpecies = 0;
    this->grid = Grid();
}

inline Grid *World::getGrid() const
{
    return (Grid *) &this->grid;
}

inline Creature *World::getCreature(const point_t &p) const
{
    return this->getGrid()->getCreature(p);
}

Species *World::getSpecies(const std::string name) const
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

int World::getSpeciesNum() const
{
    return this->numSpecies;
}