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
    if (origin) throw OverlapCreatureException(this, origin);

    // The creature don't have abilities and hill status in default
    for (int i = 0; i < length(abilityShortName); i++)
    {
        this->ability[i] = false;
    }
    this->hillActive = false;
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

inline std::string Creature::getDirectionName(const direction_t direct, bool shortFlag)
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

point_t Creature::getForwordLocation(point_t p) const
{
    switch (this->getDirection())
    {
        case EAST:
            p.c++;
            break;
        case WEST:
            p.c--;
            break;
        case SOUTH:
            p.r++;
            break;
        case NORTH:
            p.r--;
            break;
        default:
            break;
    }
    return p;
}

point_t Creature::getForwordLocation() const
{
    return this->getForwordLocation(this->getLocation());
}

void Creature::hop()
{
    auto p = this->getForwordLocation();
    if (isInside(p) && this->getWorld()->getCreature(p) == NULL)
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

void Creature::infect()
{
    auto p = this->getForwordLocation();

    if (!this->ability[ARCH] && this->isTerrain(p, FOREST))
    {
        this->programID++;
        return;
    }

    auto target = this->getWorld()->getCreature(p);

    if (this->ability[ARCH])
    {
        while(target==NULL)
        {
            p =
        }
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
    auto p = this->getForwordLocation();
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
    auto p = this->getForwordLocation();
    if (!this->isInside(p) || (!this->ability[FLY] && this->isTerrain(p, LAKE)))
    {
        this->go(address);
    } else
    {
        this->programID++;
    }
}

void Creature::ifsame(unsigned int address)
{
    auto p = this->getForwordLocation();
    if (this->getWorld()->getCreature(p) != NULL)
    {
        if (this->getWorld()->getCreature(p)->getSpecies() == this->getSpecies())
        {
            this->go(address);
            return;
        }
    }
    this->programID++;
}

void Creature::ifenemy(unsigned int address)
{
    auto p = this->getForwordLocation();
    if (this->getWorld()->getCreature(p) != NULL)
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