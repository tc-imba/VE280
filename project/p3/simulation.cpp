#include <iostream>
#include <sstream>
#include <fstream>
#include "simulation.h"
namespace simulation
{
	template <class T>
	inline int length(T &a)
	{
		return sizeof(a) / sizeof(a[0]);
	}

	template <class T>
	inline T operator++(T &a, int)
	{
		auto old = a;
		a = T(a + 1);
		return old;
	}

	bool operator==(const point_t &a, const point_t &b)
	{
		return a.c == b.c && a.r == b.r;
	}

	Species::Species(const std::string name)
	{
		this->name = name;
		this->programSize = 0;
	}

	inline std::string Species::getOptionName(const opcode_t op)
	{
		return opName[op];
	}

	inline bool Species::isEndOption(const opcode_t opcode)
	{
		return opcode <= INFECT;
	}

	void Species::addInstruction(const std::string op, const int address)
	{
		if (this->programSize >= MAXPROGRAM)
		{
			throw TooManyInstructionException(this->name);
		}
		for (auto opcode_i = HOP;opcode_i < length(opName); opcode_i++)
		{
			if (op == opName[opcode_i])
			{
				this->program[this->programSize].op = opcode_i;
				if (!isEndOption(opcode_i))
				{
					this->program[this->programSize].address = address - 1;
				}
				this->programSize++;
				return;
			}
		}
		throw UnknownInstructionException(op);
	}

	inline std::string Species::getName() const
	{
		return this->name;
	}

	Creature::Creature(World* world, std::string name, std::string direction, int row, int column)
	{
		this->m_world = world;
		this->species = world->getSpecies(name);
		if (this->species == NULL)
		{
			throw UnknownSpeciesException(name);
		}

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
		if (!flag)
		{
			throw UnknownDirectionException(direction);
		}

		this->location.r = row;
		this->location.c = column;
		if (!isInside())
		{
			throw OutsideBoundaryException(this);
		}
		auto origin = this->getWorld()->getCreature(this->location);
		if (origin)
		{
			throw OverlapCreatureException(this, origin);
		}
	}

	inline std::string Creature::getDirectionName(const direction_t direct, bool shortFlag)
	{
		return shortFlag ? directShortName[direct] : directName[direct];
	}

	inline void Creature::changeSpecies(const Species* species)
	{
		this->species = (species_t*)species;
		this->programID = 0;
	}

	inline const Species* Creature::getSpecies() const
	{
		return (Species*)this->species;
	}

	inline direction_t Creature::getDirection() const
	{
		return this->direction;
	}

	inline const point_t & Creature::getLocation() const
	{
		return this->location;
	}

	inline const World * Creature::getWorld() const
	{
		return m_world;
	}

	std::string Creature::serialize() const
	{
		std::stringstream ss;
		ss << this->getSpecies()->getName() << " ";
		ss << this->getDirectionName(this->getDirection()) << " ";
		ss << this->getLocation().r << " " <<this->getLocation().c;
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

	point_t Creature::getForwordLocation() const
	{
		auto p = this->getLocation();
		switch (this->getDirection())
		{
		case EAST:
			p.c++;break;
		case WEST:
			p.c--;break;
		case SOUTH:
			p.r++;break;
		case NORTH:
			p.r--;break;
		default:
			break;
		}
		return p;
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
		this->direction = direction_t(((((int)this->direction) - 1) + length(directName)) % length(directName));
		this->programID++;
	}

	void Creature::right()
	{
		this->direction = direction_t((((int)this->direction) + 1) % length(directName));
		this->programID++;
	}

	void Creature::infect()
	{
		auto p = this->getForwordLocation();

		auto target = this->getWorld()->getCreature(p);
		if (target != NULL)
		{
			if (target->getSpecies() != this->getSpecies())
			{
				target->changeSpecies(this->getSpecies());
			}
		}
		this->programID++;
	}

	void Creature::ifempty(int address)
	{
		auto p = this->getForwordLocation();
		if (isInside(p) && this->getWorld()->getCreature(p) == NULL)
		{
			this->go(address);
		}
		else
		{
			this->programID++;
		}
	}

	void Creature::ifwall(int address)
	{
		if (!isInside(this->getForwordLocation()))
		{
			this->go(address);
		}
		else
		{
			this->programID++;
		}
	}

	void Creature::ifsame(int address)
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

	void Creature::ifenemy(int address)
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

	void Creature::go(int address)
	{
		this->programID = address;
	}

	Grid::Grid()
	{
		for (auto i = 0;i < MAXHEIGHT;i++)
		{
			for (auto j = 0;j < MAXWIDTH;j++)
			{
				this->squares[i][j] = NULL;
			}
		}
	}

	inline bool Grid::isInside(const point_t& p) const
	{
		return p.c >= 0 && p.r >= 0 && p.c < this->width && p.r < this->height;
	}

	inline Creature* Grid::getCreature(const point_t& p) const
	{
		if (isInside(p))
		{
			return (Creature*)this->squares[p.r][p.c];
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
		for (auto i = 0;i < this->height;i++)
		{
			for (auto j = 0;j < this->width;j++)
			{
				Creature* creature = (Creature*)squares[i][j];
				if (creature == NULL)
				{
					str += "____";
				}
				else
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

	World::World()
	{
		this->numCreatures = this->numSpecies = 0;
		this->grid = Grid();
	}

	inline Grid* World::getGrid() const
	{
		return (Grid*)&this->grid;
	}

	inline Creature* World::getCreature(const point_t& p) const
	{
		return this->getGrid()->getCreature(p);
	}

	Species * World::getSpecies(const std::string name) const
	{
		for (auto i = 0;i < this->numSpecies;i++)
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

	void MyException::make()
	{
		for (int i = 1;i <= this->errNum;i++)
		{
			auto pos_1 = this->errStr[0].find('<');
			auto pos_2 = this->errStr[0].find('>');
			this->errStr[0].replace(pos_1, pos_2 - pos_1 + 1, this->errStr[i].c_str());
		}
	}

	inline const char* MyException::what() const noexcept
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

	IllegalHeightException::IllegalHeightException()
	{
		this->errStr[0] = "Error: The grid height is illegal!";
	}

	IllegalWidthException::IllegalWidthException()
	{
		this->errStr[0] = "Error: The grid width is illegal!";
	}

	OutsideBoundaryException::OutsideBoundaryException(Creature* creature)
	{
		this->errStr[0] = "Error: Creature (<CREATURE>) is out of bound!\n";
		this->errStr[0] += "The grid size is <HEIGHT>-by-<WIDTH>.";
		this->errStr[++errNum] = creature->serialize();
		auto grid = creature->getWorld()->getGrid();
		std::stringstream ss;
		ss << (grid->getHeight()) << " " << grid->getWidth();
		ss >> this->errStr[++errNum] >> this->errStr[++errNum];
		this->make();
	}

	OverlapCreatureException::OverlapCreatureException(Creature* newCreature, Creature* originCreature)
	{
		this->errStr[0] = "Error: Creature (<CREATURE1>) overlaps with creature (<CREATURE2>)!";
		this->errStr[++errNum] = newCreature->serialize();
		this->errStr[++errNum] = originCreature->serialize();
		this->make();
	}

	Controller::Controller(int argc, char * argv[])
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
				try
				{
					species->addInstruction(optionStr, optionAddress);
				}
				catch (...)
				{
					throw;
				}
			}
			speciesFile.close();
		}
		speciesSummary.close();
	}

	void Controller::readWorld(std::string worldPath)
	{
		std::ifstream worldFile(worldPath);
		if (!worldFile.is_open())
		{
			throw FailureFileException(worldPath);
		}
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
		this->world->grid.height = height;
		this->world->grid.width = width;
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
			try 
			{
				auto creature = new Creature(this->world, name, direction, row, column);
				this->world->m_creatures[this->world->numCreatures++] = creature;
				this->world->getGrid()->squares[row][column] = creature;
			}
			catch (...)
			{
				throw;
			}
		}
	}

	void Controller::creatureMove(Creature* creature)
	{
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
		}
		if (this->verbose)
		{
			std::cout << std::endl << "Instruction " << programID + 1 << ":";
		}
		if (Species::isEndOption(instruction.op))
		{
			std::cout << " " << Species::getOptionName(instruction.op);
		}
		else
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
		for (int i = 0;i < this->world->numCreatures;i++)
		{
			std::cout << "Creature ("<< this->world->m_creatures[i]->serialize() <<") takes action:";
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
		for (this->round = 0;this->round < this->round_max;this->round++)
		{
			this->simulateRound();
		}
	}

}