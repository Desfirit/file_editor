#pragma once

#include <iostream>
#include <string>

using namespace std;

inline void print_commands()
{
	wcout << L"create [type=txt] <file_name>\n";
	wcout << L"\t[type] - json, xml, txt\n";

	wcout << L"edit <file_name>\n";

	wcout << L"read <file_name>\n";

	wcout << L"zip [pack <file_name>...<file_name>] ! [unpack <archive_path>]\n";

	wcout << L"exit\n";

	wcout << L"help\n";
}

inline void print_menu()
{
	wcout << L"��������� ��� �������������� � �������\n\n";

	wcout << L"����������: \n";

	print_commands();
}

inline wstring ask_command(const wstring& ask)
{
	wcout << ask;
	wstring input;
	getline(wcin >> ws, input);
	return input;
}