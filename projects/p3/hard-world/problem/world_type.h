#ifndef WORLD_TYPE_H
#define WORLD_TYPE_H

#include <string>

using namespace std;

const unsigned int MAXSPECIES = 10; // Max number of species in the
                                    // world
const unsigned int MAXPROGRAM = 40; // Max size of a species program
const unsigned int MAXCREATURES = 50; // Max number of creatures in
                                      // the world
const unsigned int MAXHEIGHT = 20; // Max height of the grid
const unsigned int MAXWIDTH = 20;  // Max width of the grid


enum direction_t { EAST, SOUTH, WEST, NORTH, DIRECT_SIZE };
/*
// Type: direction_t
// ----------------
// This type is used to represent direction, which can take one of
// the four values: East, South, West, and North. The last one,
// DIRECT_SIZE, can be used to indicate the end of this enum type.
// This convention is applied to the other enum types defined below.
*/

enum terrain_t { PLAIN, LAKE, FOREST, HILL, TERRAIN_SIZE };
/*
// Type: terrain_t
// ----------------
// This type is used to represent terrain type of a square, which
// can take one of the four values: Plain, Lake, Forest, Hill.
*/

enum ability_t { FLY, ARCH, ABILITY_SIZE };
/*
// Type: ability_t
// ----------------
// This type is used to represent special abilities of a creature,
// which can take one of the two values: Flying and Archery.
*/

enum opcode_t { HOP, LEFT, RIGHT, INFECT, IFEMPTY, IFENEMY, IFSAME, IFWALL,
    GO, OP_SIZE };
/*
// Type: opcode_t
// -------------
// The type opcode_t is an enumeration of all of the legal
// command names.
*/

struct point_t
{
    int r;
    int c;
};
/*
// Type: point_t
// ------------
// This type is used to represent a point in the grid.
// Its component r corresponds to the row number; its component
// c corresponds to the column number;
//
*/

const string directName[] = {"east", "south", "west", "north"};
// An array of strings representing the direction name.

const string directShortName[] = {"e", "s", "w", "n"};
// An array of strings representing the short name of direction.

const string terrainName[] = {"plain", "lake", "forest", "hill"};
// An array of strings representing the terrain type name.

const string terrainShortName[] = {"P", "L", "F", "H"};
// An array of strings representing the short name of terrain type.

const string abilityName[] = {"fly", "arch"};
// An array of strings representing the ability name.

const string abilityShortName[] = {"f", "a"};
// An array of strings representing the short name of ability.

const string opName[] = {"hop", "left", "right", "infect",
    "ifempty", "ifenemy", "ifsame", "ifwall", "go"};
// An array of strings representing the command name.

struct instruction_t
{
    opcode_t op;
    unsigned int address;
};
/*
// Type: instruction_t
// ------------------
// The type instruction_t is used to represent an
// instruction and consists of a pair of an operation
// code and an integer. For some operation code, the
// integer stores the address of the instruction it jumps
// to (e.g., n in the instruction "ifempty n"). The
// address is optional.
*/

struct species_t
{
    string name;
    unsigned int programSize;
    instruction_t program[MAXPROGRAM];
};
/*
// Type: species_t
// ------------------
// The type species_t is used to represent a species
// and consists of a string, an unsigned int, and an array
// of instruction_t. The string gives the name of the
// species. The unsigned int gives the number of instructions
// in the program of the species. The array stores all the
// instructions in the program according to their sequence.
*/

struct creature_t
{
    point_t location;
    direction_t direction;
    species_t *species;
    unsigned int programID;
    bool ability[ABILITY_SIZE];
    bool hillActive;
};
/*
// Type: creature_t
// ------------------
// The type creature_t is used to represent a creature. It
// consists of a point_t, a direction_t, a pointer to
// species_t, an unsigned int, a bool array, and a bool variable.
// The point_t variable location gives the location of the
// species. The direction_t variable direction gives the direction
// of the species. The pointer to species_t variable species
// points to the species the creature belongs to. The unsigned
// int programID gives the index of the instruction to be executed
// in the instruction_t array of the species. The bool array
// ability indicates the set of abilities the creature has. For
// example, if the creature only has FLY ability, you should set
// ability[FLY] to true and ability[ARCH] to false. The bool
// variable hillActive indicates if the creature is able to simulate
// in the current round if the creature is in a hill square. It does
// not serve any other purpose if the creature is not in a hill square.
*/

struct grid_t
{
    unsigned int height;
    unsigned int width;
    creature_t *squares[MAXHEIGHT][MAXWIDTH];
    terrain_t terrain[MAXHEIGHT][MAXWIDTH];
};
/*
// Type: grid_t
// ------------------
// The type grid_t consists of the height and the width of
// the grid, a two-dimensional array of pointers to creature_t,
// and a two-dimensional array of terrain_t type. If there is
// a creature at the point (r, c) in the grid, then squares[r][c]
// stores a pointer to that creature. If point (r, c) is not
// occupied by any creature, then squares[r][c] is a NULL pointer.
// The two-dimensional array terrain stores the terrain type for
// each square in the grid.
*/

struct world_t
{
    unsigned int numSpecies;
    species_t species[MAXSPECIES];

    unsigned int numCreatures;
    creature_t creatures[MAXCREATURES];

    grid_t grid;
};
/*
// Type: world_t
// --------------
// This type consists of two unsigned ints, an array of species_t,
// an array of creature_t, and a grid_t object. The first unsigned
// int numSpecies specifies the number of species in the creature
// world. The second unsigned int numCreatures specifies the number
// of creatures in the world. All the species are stored in the array 
// species and all the creatures are stored in the array creatures.
// The grid is given in the object grid.
*/

#endif
