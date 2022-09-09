#pragma once
#include <vector>
#include <string>

#include <command_parser/command_types.h>

typedef std::pair<std::wstring, CommandContextType> Arg;

struct __declspec(novtable) ICommand
{
	virtual ~ICommand() = default;

	virtual CommandType get_command_type() = 0;
	virtual std::vector<Arg> get_command_args() = 0;

	virtual void exec() = 0;
};