//
// Created by liu on 17-6-29.
//

#include "simulation.h"
using namespace p3;

Species::Species(const std::string &name)
{
    this->name = name;
    this->programSize = 0;
}

inline std::string Species::getOptionName(const opcode_t &op)
{
    return opName[op];
}

inline bool Species::isEndOption(const opcode_t &opcode)
{
    return opcode <= INFECT;
}

inline const instruction_t& Species::getInstruction(const int &programID) const
{
    return this->program[programID];
}

void Species::addInstruction(const std::string &op, const int &address)
{
    if (this->programSize >= MAXPROGRAM)
    {
        throw TooManyInstructionException(this->name);
    }
    for (auto opcode_i = HOP; opcode_i < length(opName); opcode_i++)
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