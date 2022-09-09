#pragma once
#include <vector>
#include <memory>

#include <command_parser/command_types.h>
#include <command_parser/icommand.h>

class CommandParser
{
public:
	CommandParser() = default;
	CommandParser(const CommandParser&) = default;
	CommandParser(CommandParser&&) = default;

	CommandParser& operator=(const CommandParser&) = default;
	CommandParser& operator=(CommandParser&&) = default;

	static std::unique_ptr<ICommand> parse_commands(const std::vector<std::wstring>& command_args);
};