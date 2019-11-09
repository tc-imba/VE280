//
// Created by liu on 17-6-29.
//

#include "simulation.h"

using namespace p3;

Grid::Grid(grid_t &grid)
{
    for (auto i = 0; i < MAXHEIGHT; i++)
    {
        for (auto j = 0; j < MAXWIDTH; j++)
        {
            this->squares[i][j] = NULL;
        }
    }
    grid = *this;
}

inline void Grid::setSize(const unsigned int &height, const unsigned int &width)
{
    this->height = height;
    this->width = width;
}

/**
 * @version 2.0 Added
 * @throws UnknownTerrainException
 * @param p
 * @param terrain
 */
void Grid::setTerrain(const point_t &p, char terrain)
{
    for (int i = 0; i < length(terrainShortName); i++)
    {
        if (terrainShortName[i][0] == terrain)
        {
            this->terrain[p.r][p.c] = terrain_t(i);
            return;
        }
    }
    throw UnknownTerrainException(p, terrain);
}

inline bool Grid::isInside(const point_t &p) const
{
    return p.c >= 0 && p.r >= 0 && p.c < this->width && p.r < this->height;
}

/**
 * @version 2.0 Added
 * @param p
 * @param terrain
 * @return
 */
inline bool Grid::isTerrain(const point_t &p, terrain_t terrain) const
{
    return this->isInside(p) && this->terrain[p.r][p.c] == terrain;
}

inline void Grid::addCreature(Creature *creature)
{
    auto p = creature->getLocation();
    this->squares[p.r][p.c] = (creature_t *) creature;
}

inline Creature *Grid::getCreature(const point_t &p) const
{
    if (isInside(p))
    {
        return (Creature *) this->squares[p.r][p.c];
    }
    return NULL;
}

inline int Grid::getHeight() const
{
    return this->height;
}

inline int Grid::getWidth() const
{
    return this->width;
}

void Grid::move(const point_t &a, const point_t &b)
{
    this->squares[b.r][b.c] = this->squares[a.r][a.c];
    this->squares[a.r][a.c] = NULL;
}

std::string Grid::serialize() const
{
    std::string str;
    for (auto i = 0; i < this->height; i++)
    {
        for (auto j = 0; j < this->width; j++)
        {
            Creature *creature = (Creature *) squares[i][j];
            if (creature == NULL)
            {
                str += "____";
            } else
            {
                str += creature->getSpecies()->getName().substr(0, 2);
                str += "_" + creature->getDirectionName(creature->getDirection(), true);
            }
            str += " ";
        }
        str += "\n";
    }
    return str;
}