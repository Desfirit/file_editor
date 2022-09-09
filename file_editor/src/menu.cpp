#include "Menu.h"

#include <iostream>
#include <iomanip>

#include <utils/command_line_utils.h>
#include <utils/user_helpers.h>

#include <command_parser/command_parser.h>
#include <command_parser/command_exceptions.h>

using namespace std;
using namespace file_editor;

Menu::Menu(const std::vector<std::wstring>& args) : m_args{ args } {}
Menu::Menu(const std::vector<std::wstring>&& args) : m_args{ args } {}

int Menu::exec()
{
	print_menu();

	while (true)
	{
		const auto commandLine{ ask_command(L"Введите команду: ") };

		try
		{
			auto args{ convert(commandLine) };

			unique_ptr<ICommand> command{ CommandParser::parse_commands(args) };

			if (!command)
			{
				wcerr << __FILE__ _STRINGIZE(__LINE__) L" zero pointer\n";
				wcout << L"Завершение программы...\n";
				break;
			}
			if (command->get_command_type() == CommandType::Exit)
				break;

			command->exec();
		}
		catch (const WrongCommandError& err)
		{
			wcout << L"Команды " << quoted(err.whatEx()) << L" нет" << '\n';
		}
		catch (const WrongArgumentsError& err)
		{
			wcout << err.whatEx() << '\n';
		}
		catch(const UnexpectedError& err)
		{
			wcout << err.whatEx() << '\n';
		}
		catch (const std::runtime_error& ex)
		{
			wcout << ex.what() << '\n';
			break; //exit programm
		}
	}
	return 0;
}