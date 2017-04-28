#pragma once
#include <string>
#include "world_type.h"
namespace simulation
{

	class Species;
	class Creature;
	class Grid;
	class World;

	class Controller;

	class MyException;
	class MissingArgumentException;
	class NegativeRoundException;
	class FailureFileException;
	class TooManySpeciesException;
	class TooManyInstructionException;
	class UnknownInstructionException;
	class TooManyCreatureException;
	class UnknownSpeciesException;
	class UnknownDirectionException;
	class IllegalHeightException;
	class IllegalWidthException;
	class OutsideBoundaryException;
	class OverlapCreatureException;
	
	// Overload operator== for point_t to enable comparing
	bool operator==(const point_t &, const point_t &);


	class Species :protected species_t
	{
	public:
		friend class Controller;
		friend class Creature;
		Species(const std::string);
		static std::string getOptionName(const opcode_t);
		static bool isEndOption(const opcode_t);
		void addInstruction(const std::string, const int = 0);
		std::string getName() const;
	};

	class Creature: protected creature_t
	{
	protected:
		World* m_world;
	public:
		friend class Controller;
		Creature(World*, std::string, std::string, int, int);
		static std::string getDirectionName(const direction_t, bool = false);
		void changeSpecies(const Species*);
		const Species* getSpecies() const;
		direction_t getDirection() const;
		const point_t& getLocation() const;
		const World* getWorld() const;
		std::string serialize() const;

		bool isInside(const point_t&) const;
		bool isInside() const;
		point_t getForwordLocation() const;

		void hop();
		void left();
		void right();
		void infect();
		void ifempty(int);
		void ifwall(int);
		void ifsame(int);
		void ifenemy(int);
		void go(int);
		
	};

	class Grid : protected grid_t
	{
	public:
		friend class Controller;
		friend class World;
		Grid();

		bool isInside(const point_t&) const;

		Creature* getCreature(const point_t&) const;
		int getHeight() const;
		int getWidth() const;

		void move(const point_t&, const point_t&);
		std::string serialize() const;
	};

	class World : protected world_t
	{
	protected:
		Species* m_species[MAXSPECIES];
		Creature* m_creatures[MAXCREATURES];
	public:
		friend class Controller;
		World();
		Grid* getGrid() const;
		Creature* getCreature(const point_t&) const;
		Species* getSpecies(const std::string) const;
		int getSpeciesNum() const;
	};

	class Controller
	{
	private:
		int round, round_max;
		bool verbose;
		World* world;
	public:
		Controller(int argc, char *argv[]);
		void readSpecies(const std::string);
		void readWorld(const std::string);
		void creatureMove(Creature*);
		void simulateRound();
		void simulate();
	};


	
	class MyException :public std::exception
	{
	protected:
		std::string errStr[10];
		int errNum = 0;
		void make();
	public:
		virtual const char* what() const noexcept;
	};

	/*
	Error 1:
	Check whether the number of arguments is less than three.
	*/
	class MissingArgumentException :public MyException
	{
	public:
		MissingArgumentException();
	};

	/*
	Error 2:
	Check whether the value <rounds> supplied by the user is negative.
	*/
	class NegativeRoundException :public MyException
	{
	public:
		NegativeRoundException();
	};

	/*
	Error 3:
	Check whether file open is successful.
	If opening species summary file, world file, or any species program file fails
	(for example, the file to be opened does not exist).
	*/
	class FailureFileException :public MyException
	{
	public:
		FailureFileException(std::string);
	};

	/*
	Error 4:
	Check whether the number of species listed in the species summary file
	exceeds the maximal number of species MAXSPECIES.
	*/
	class TooManySpeciesException :public MyException
	{
	public:
		TooManySpeciesException();
	};

	/*
	Error 5:
	Check whether the number of instructions for a species 
	exceeds the maximal size of a species program MAXPROGRAM.
	*/
	class TooManyInstructionException :public MyException
	{
	public:
		TooManyInstructionException(std::string);
	};

	/*
	Error 6:
	Check whether the instruction name is one of the nine 
	legal instruction names listed in the string array opName
	*/
	class UnknownInstructionException :public MyException
	{
	public:
		UnknownInstructionException(std::string);
	};

	/*
	Error 7:
	Check whether the number of creatures listed in the world file
	exceeds the maximal number of creatures MAXCREATURES.
	*/
	class TooManyCreatureException :public MyException
	{
	public:
		TooManyCreatureException();
	};

	/*
	Error 8:
	Check whether each creature in the world file belongs to 
	one of the species listed in the species summary file.
	*/
	class UnknownSpeciesException :public MyException
	{
	public:
		UnknownSpeciesException(std::string);
	};

	/*
	Error 9:
	Check whether the direction string for each creature in the world file 
	is one of the strings in the array directName
	*/
	class UnknownDirectionException :public MyException
	{
	public:
		UnknownDirectionException(std::string);
	};

	/*
	Error 10:
	Check whether the grid height given by the world file is legal.
	*/
	class IllegalHeightException :public MyException
	{
	public:
		IllegalHeightException();
	};

	/*
	Error 11:
	Check whether the grid width given by the world file is legal.
	*/
	class IllegalWidthException :public MyException
	{
	public:
		IllegalWidthException();
	};

	/*
	Error 12:
	Check whether each creature is inside the boundary of the grid.
	*/
	class OutsideBoundaryException :public MyException
	{
	public:
		OutsideBoundaryException(Creature*);
	};

	/*
	Error 13:
	Check whether each square in the grid is occupied by at most one creature.
	*/
	class OverlapCreatureException :public MyException
	{
	public:
		OverlapCreatureException(Creature*, Creature*);
	};

}