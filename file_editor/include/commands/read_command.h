#pragma once
#include <vector>
#include <string>
#include <filesystem>

#include <command_parser/icommand.h>
#include <command_parser/command_types.h>
#include <command_parser/command_exceptions.h>

class ReadCommand final : public ICommand
{
public:
	ReadCommand(std::vector<std::wstring>::const_iterator beg, std::vector<std::wstring>::const_iterator end);

	~ReadCommand() override = default;

private:
	// ICommand
	CommandType get_command_type() override
	{
		return CommandType::Read;
	}

	std::vector<Arg> get_command_args() override;

	void exec() override;

private:

	filesystem::path m_targetFile;
};