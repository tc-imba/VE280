//
// Created by liu on 17-6-29.
//

#include <sstream>
#include "simulation.h"

using namespace p3;

/**
 * The constructor of Creature
 * @version 2.0 Add the initialization of bool ability[ABILITY_SIZE] and bool hillActive;
 * @throws UnknownSpeciesException
 * @throws UnknownDirectionException
 * @throws OutsideBoundaryException
 * @throws OverlapCreatureException
 * @param world
 * @param name
 * @param direction
 * @param row
 * @param column
 */
Creature::Creature(World *world, std::string name, std::string direction, int row, int column)
{
    this->m_world = world;
    this->programID = 0;

    // Initialize the species of the creature
    this->species = (species_t *) world->getSpecies(name);
    if (this->species == NULL)
    {
        throw UnknownSpeciesException(name);
    }

    // Set and judge the direction
    bool flag = false;
    for (auto direction_i = EAST; direction_i < length(directName); direction_i++)
    {
        if (direction == directName[direction_i])
        {
            this->direction = direction_i;
            flag = true;
            break;
        }
    }
    if (!flag) throw UnknownDirectionException(direction);

    // Set and judge the location
    this->location.r = row;
    this->location.c = column;
    if (!isInside()) throw OutsideBoundaryException(this);

    // Judge whether there is a creature at the location
    auto origin = this->getWorld()->getCreature(this->location);
    if (origin != NULL) throw OverlapCreatureException(this, origin);

    // The creature don't have abilities and hill status in default
    for (int i = 0; i < length(abilityShortName); i++)
    {
        this->ability[i] = false;
    }
    this->hillActive = false;
}

inline unsigned int Creature::getProgramID() const
{
    return this->programID;
}

/**
 * Add an ability to the creature
 * If the ability is unknown, throws an exception
 * @version 2.0 Added
 * @throws UnknownAbilityException
 * @param ability
 */
void Creature::addAbility(std::string ability)
{
    for (auto i = 0; i < length(abilityShortName); i++)
    {
        if (abilityShortName[i] == ability)
        {
            this->ability[i] = true;
            return;
        }
    }
    throw UnknownAbilityException(this, ability);
}

inline bool Creature::hasAbility(const ability_t &ability) const
{
    return this->ability[ability];
}

inline const std::string &Creature::getDirectionName(const direction_t &direct, bool shortFlag)
{
    return shortFlag ? directShortName[direct] : directName[direct];
}

inline void Creature::changeSpecies(const Species *species)
{
    this->species = (species_t *) species;
    this->programID = 0;
}

inline const Species *Creature::getSpecies() const
{
    return (Species *) this->species;
}

inline direction_t Creature::getDirection() const
{
    return this->direction;
}

inline const point_t &Creature::getLocation() const
{
    return this->location;
}

inline const World *Creature::getWorld() const
{
    return m_world;
}

std::string Creature::serialize() const
{
    std::stringstream ss;
    ss << this->getSpecies()->getName() << " ";
    ss << this->getDirectionName(this->getDirection()) << " ";
    ss << this->getLocation().r << " " << this->getLocation().c;
    return ss.str();
}

inline bool Creature::isInside(const point_t &p) const
{
    return this->getWorld()->getGrid()->isInside(p);
}

inline bool Creature::isInside() const
{
    return this->isInside(this->getLocation());
}

inline bool Creature::isTerrain(const point_t &p, terrain_t terrain) const
{
    return this->getWorld()->getGrid()->isTerrain(p, terrain);
}

inline bool Creature::isTerrain(terrain_t terrain) const
{
    return this->isTerrain(this->getLocation(), terrain);
}

point_t Creature::getForwardLocation(const point_t &p) const
{
    auto p2 = p;
    switch (this->getDirection())
    {
        case EAST:
            p2.c++;
            break;
        case WEST:
            p2.c--;
            break;
        case SOUTH:
            p2.r++;
            break;
        case NORTH:
            p2.r--;
            break;
        default:
            break;
    }
    return p2;
}

point_t Creature::getForwardLocation() const
{
    return this->getForwardLocation(this->getLocation());
}

/**
 * @version 2.0 Add ability FLY and terrain LAKE
 */
void Creature::hop()
{
    auto p = this->getForwardLocation();
    if (isInside(p) && this->getWorld()->getCreature(p) == NULL &&
        (this->ability[FLY] || !this->isTerrain(p, LAKE)))
    {
        this->getWorld()->getGrid()->move(this->getLocation(), p);
        this->location = p;
    }
    this->programID++;
}

void Creature::left()
{
    this->direction = direction_t(((((int) this->direction) - 1) + length(directName)) % length(directName));
    this->programID++;
}

void Creature::right()
{
    this->direction = direction_t((((int) this->direction) + 1) % length(directName));
    this->programID++;
}

/**
 * @version 2.0 Add ability ARCH and terrain FOREST
 */
void Creature::infect()
{
    auto p = this->getForwardLocation();
    auto target = this->getWorld()->getCreature(p);

    if (this->ability[ARCH])
    {
        while (target == NULL || target->getSpecies() == this->getSpecies())
        {
            p = this->getForwardLocation(p);
            if (!this->isInside(p))break;
            target = this->getWorld()->getCreature(p);
        }
    } else if (this->isTerrain(p, FOREST))
    {
        target = NULL;
    }

    if (target != NULL)
    {
        if (target->getSpecies() != this->getSpecies())
        {
            target->changeSpecies(this->getSpecies());
        }
    }
    this->programID++;
}


void Creature::ifempty(unsigned int address)
{
    auto p = this->getForwardLocation();
    if (this->isInside(p) && this->getWorld()->getCreature(p) == NULL)
    {
        this->go(address);
    } else
    {
        this->programID++;
    }
}

/**
 * @version 2.0 Let lake as a wall if cannot fly
 * @param address
 */
void Creature::ifwall(unsigned int address)
{
    auto p = this->getForwardLocation();
    if (!this->isInside(p) || (!this->ability[FLY] && this->isTerrain(p, LAKE)))
    {
        this->go(address);
    } else
    {
        this->programID++;
    }
}

/**
 * @version 2.0 terrain FOREST is always NOT same
 * @param address
 */
void Creature::ifsame(unsigned int address)
{
    auto p = this->getForwardLocation();
    if (this->getWorld()->getCreature(p) != NULL && !this->isTerrain(p, FOREST))
    {
        if (this->getWorld()->getCreature(p)->getSpecies() == this->getSpecies())
        {
            this->go(address);
            return;
        }
    }
    this->programID++;
}

/**
 * @version 2.0 terrain FOREST is always NOT enemy
 * @param address
 */
void Creature::ifenemy(unsigned int address)
{
    auto p = this->getForwardLocation();
    if (this->getWorld()->getCreature(p) != NULL && !this->isTerrain(p, FOREST))
    {
        if (this->getWorld()->getCreature(p)->getSpecies() != this->getSpecies())
        {
            this->go(address);
            return;
        }
    }
    this->programID++;
}

void Creature::go(unsigned int address)
{
    this->programID = address;
}

/**
 * @version 2.0 Added
 * @return
 */
bool Creature::stayHill()
{
    if (this->isTerrain(HILL) && !this->hasAbility(FLY) && !this->hillActive)
    {
        return (this->hillActive = true);
    }
    return false;
}

void Creature::enterHill()
{
    this->hillActive = false;
}
