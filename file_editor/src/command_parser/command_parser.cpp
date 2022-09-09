#include "command_parser/command_parser.h"

#include <iostream>
#include <string>
#include <stdexcept>

#include <command_parser/command_types.h>
#include <command_parser/command_exceptions.h>

#include <commands/help_command.h>
#include <commands/exit_command.h>
#include <commands/read_command.h>

using namespace std;

namespace
{
	constexpr pair<const wchar_t*, CommandType> possibleTypes[]
	{
		{L"create", CommandType::Create},
		{L"edit", CommandType::Edit},
		{L"read", CommandType::Read},
		{L"help", CommandType::Help},
		{L"exit", CommandType::Exit},
	};
}

unique_ptr<ICommand> CommandParser::parse_commands(const vector<wstring>& args)
{
	if (args.empty())
		throw runtime_error{__FILE__ _STRINGIZE(__LINE__) " empty args"};

	const auto& argsCommand{ args.front() };

	const auto commandType{ find_if(begin(possibleTypes), end(possibleTypes), [&argsCommand](const auto& pair) {
		return pair.first == argsCommand;
	})};

	if(commandType == end(possibleTypes))
		throw WrongCommandError{argsCommand};

	switch (commandType->second)
	{
		case CommandType::Create:
		{
			return nullptr;
		}
		case CommandType::Edit: 
		{
			return nullptr;
		}
		case CommandType::Read: 
		{
			return unique_ptr<ReadCommand>{new ReadCommand(begin(args) + 1, end(args))};
		}
		case CommandType::Help: 
		{
			return unique_ptr<HelpCommand>{new HelpCommand(begin(args) + 1, end(args))};
		}
		case CommandType::Exit: 
		{
			return unique_ptr<ExitCommand>{new ExitCommand(begin(args) + 1, end(args))};
		}
	default:
		break;
	}

	return nullptr;
}