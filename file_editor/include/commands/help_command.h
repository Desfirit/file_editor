#pragma once

#include <vector>

#include <command_parser/icommand.h>
#include <command_parser/command_types.h>

#include <utils/user_helpers.h>

class HelpCommand final : public ICommand
{
public:
	HelpCommand(std::vector<std::wstring>::const_iterator beg, std::vector<std::wstring>::const_iterator end)
	{
		if (beg != end)
		{
			throw WrongArgumentsError{ L"У команды help не должно быть аргументов", {beg, end} };
		}
	}

	~HelpCommand() override = default;

private:
	// ICommand
	CommandType get_command_type() override
	{
		return CommandType::Help;
	}

	std::vector<Arg> get_command_args() override
	{
		return {};
	}

	void exec() override
	{
		print_commands();
	}
};