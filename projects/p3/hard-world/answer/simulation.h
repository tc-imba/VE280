//
// Created by liu on 17-6-29.
//
// Version 2.0
// Updated 2017.6
//

#ifndef VE280_SIMULATION_H
#define VE280_SIMULATION_H

#include "world_type.h"

namespace p3
{
    // Definition of classes
    class Species;

    class Creature;

    class Grid;

    class World;

    class Controller;

    // Definition of Exceptions
    class MyException;

    class MissingArgumentException;

    class NegativeRoundException;

    class FailureFileException;

    class TooManySpeciesException;

    class TooManyInstructionException;

    class UnknownInstructionException;

    class IllegalHeightException;

    class IllegalWidthException;

    class UnknownTerrainException;

    class TooManyCreatureException;

    class UnknownSpeciesException;

    class UnknownDirectionException;

    class OutsideBoundaryException;

    class UnknownAbilityException;

    class OverlapCreatureException;

    class CannotFlyException;


    template<class T>
    inline int length(T &a)
    {
        return sizeof(a) / sizeof(a[0]);
    }

    template<class T>
    inline T operator++(T &a, int)
    {
        auto old = a;
        a = T(a + 1);
        return old;
    }

    // Overload operator== for point_t to enable comparing
    inline bool operator==(const point_t &a, const point_t &b)
    {
        return a.c == b.c && a.r == b.r;
    }


    class Species : protected species_t
    {
    public:
        explicit Species(const std::string &);

        static std::string getOptionName(const opcode_t &);

        static bool isEndOption(const opcode_t &);

        const instruction_t &getInstruction(const int &) const;

        void addInstruction(const std::string &, const int & = 0);

        std::string getName() const;
    };

    class Creature : protected creature_t
    {
    protected:
        World *m_world;
    public:

        explicit Creature(World *, std::string, std::string, int, int);

        unsigned int getProgramID() const;

        void addAbility(std::string ability);

        bool hasAbility(const ability_t &) const;

        static const std::string& getDirectionName(const direction_t &, bool = false);

        void changeSpecies(const Species *);

        const Species *getSpecies() const;

        direction_t getDirection() const;

        const point_t &getLocation() const;

        const World *getWorld() const;

        std::string serialize() const;

        bool isInside(const point_t &) const;

        bool isInside() const;

        bool isTerrain(const point_t &, terrain_t) const;

        bool isTerrain(terrain_t) const;

        point_t getForwardLocation(const point_t &) const;

        point_t getForwardLocation() const;

        void hop();

        void left();

        void right();

        void infect();

        void ifempty(unsigned int);

        void ifwall(unsigned int);

        void ifsame(unsigned int);

        void ifenemy(unsigned int);

        void go(unsigned int);

        bool stayHill();

        void enterHill();
    };

    class Grid : protected grid_t
    {
    public:

        explicit Grid(grid_t &);

        void setSize(const unsigned int &, const unsigned int &);

        void setTerrain(const point_t &, char);

        bool isInside(const point_t &) const;

        bool isTerrain(const point_t &, terrain_t) const;

        void addCreature(Creature *);

        Creature *getCreature(const point_t &) const;

        int getHeight() const;

        int getWidth() const;

        void move(const point_t &, const point_t &);

        std::string serialize() const;
    };

    class World : protected world_t
    {
    protected:
        Species *m_species[MAXSPECIES];
        Creature *m_creatures[MAXCREATURES];
    public:

        explicit World();

        Grid *getGrid() const;

        Creature *addCreature(Creature *);

        Creature *getCreature(const point_t &) const;

        Creature *getCreature(const unsigned int &) const;

        Species *addSpecies(Species *);

        Species *getSpecies(const std::string &) const;

        int getCreatureNum() const;

        int getSpeciesNum() const;
    };

    class Controller
    {
    private:
        int round, round_max;
        bool verbose;
        World *world;
    public:
        explicit Controller(int argc, char *argv[]);

        void readSpecies(const std::string &);

        void readWorld(const std::string &);

        void creatureMove(Creature *);

        void simulateRound();

        void simulate();
    };


    /**
     * The definitions of the Exceptions
     */
    class MyException : public std::exception
    {
    protected:
        std::string errStr[10];
        int errNum = 0;

        void make();

    public:
        virtual const char *what() const noexcept;
    };

    /**
     * Error 1:
     * Check whether the number of arguments is less than three.
     */
    class MissingArgumentException : public MyException
    {
    public:
        explicit MissingArgumentException();
    };

    /**
     * Error 2:
     * Check whether the value <rounds> supplied by the user is negative.
     */
    class NegativeRoundException : public MyException
    {
    public:
        explicit NegativeRoundException();
    };

    /**
     * Error 3:
     * Check whether file open is successful.
     * If opening species summary file, world file, or any species program file fails
     * (for example, the file to be opened does not exist).
    */
    class FailureFileException : public MyException
    {
    public:
        explicit FailureFileException(std::string);
    };

    /**
     * Error 4:
     * Check whether the number of species listed in the species summary file
     * exceeds the maximal number of species MAXSPECIES.
     */
    class TooManySpeciesException : public MyException
    {
    public:
        explicit TooManySpeciesException();
    };

    /**
     * Error 5:
     * Check whether the number of instructions for a species
     * exceeds the maximal size of a species program MAXPROGRAM.
     */
    class TooManyInstructionException : public MyException
    {
    public:
        explicit TooManyInstructionException(std::string);
    };

    /**
     * Error 6:
     * Check whether the instruction name is one of the nine
     * legal instruction names listed in the string array opName
     */
    class UnknownInstructionException : public MyException
    {
    public:
        explicit UnknownInstructionException(std::string);
    };

    /**
     * Error 7:
     * Check whether the grid height given by the world file is legal.
     */
    class IllegalHeightException : public MyException
    {
    public:
        explicit IllegalHeightException();
    };

    /**
     * Error 8:
     * Check whether the grid width given by the world file is legal.
     */
    class IllegalWidthException : public MyException
    {
    public:
        explicit IllegalWidthException();
    };

    /**
     * Error 9:
     * Check whether the two-dimensional array describing the terrain layout is correct.
     */
    class UnknownTerrainException : public MyException
    {
    public:
        explicit UnknownTerrainException(const point_t &, char);
    };

    /**
     * Error 10:
     * Check whether the number of creatures listed in the world file
     * exceeds the maximal number of creatures MAXCREATURES.
     */
    class TooManyCreatureException : public MyException
    {
    public:
        explicit TooManyCreatureException();
    };

    /**
     * Error 11:
     * Check whether each creature in the world file belongs to
     * one of the species listed in the species summary file.
     */
    class UnknownSpeciesException : public MyException
    {
    public:
        explicit UnknownSpeciesException(std::string);
    };

    /**
     * Error 12:
     * Check whether the direction string for each creature in the world file
     * is one of the strings in the array directName
     */
    class UnknownDirectionException : public MyException
    {
    public:
        explicit UnknownDirectionException(std::string);
    };

    /**
     * Error 13:
     * Check whether each creature is inside the boundary of the grid.
    */
    class OutsideBoundaryException : public MyException
    {
    public:
        explicit OutsideBoundaryException(Creature *);
    };

    /**
     * Error 14:
     * Check whether each ability of each creature is valid.
     */
    class UnknownAbilityException : public MyException
    {
    public:
        explicit UnknownAbilityException(Creature *, std::string);
    };

    /**
     * Error 15:
     * Check whether each square in the grid is occupied by at most one creature.
     */
    class OverlapCreatureException : public MyException
    {
    public:
        explicit OverlapCreatureException(Creature *, Creature *);
    };

    /**
     * Error 16:
     * Check whether a creature that cannot fly is not in a lake square.
     */
    class CannotFlyException : public MyException
    {
    public:
        explicit CannotFlyException(Creature *);
    };

}

#endif //VE280_SIMULATION_H
