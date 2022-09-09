#pragma once

#include <command_parser/icommand.h>
#include <command_parser/command_types.h>
#include <command_parser/command_exceptions.h>

class ExitCommand final : public ICommand
{
public:
	ExitCommand(std::vector<std::wstring>::const_iterator beg, std::vector<std::wstring>::const_iterator end)
	{
		if (beg != end)
		{
			throw WrongArgumentsError{ L"� ������� exit �� ������ ���� ����������", {beg, end} };
		}
	}

	~ExitCommand() override = default;

private:
	// ICommand
	CommandType get_command_type() override
	{
		return CommandType::Exit;
	}

	std::vector<Arg> get_command_args() override
	{
		return {};
	}

	void exec() override
	{
		wcout << L"���������� ���������...\n";
		exit(EXIT_SUCCESS);
	}
};