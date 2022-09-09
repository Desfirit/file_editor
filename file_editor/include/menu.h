#pragma once

#include <vector>
#include <string>

namespace file_editor
{

class Menu final
{
public:
	Menu(const std::vector<std::wstring>& args);
	Menu(const std::vector<std::wstring>&& args);

	int exec();

private:
	const std::vector<std::wstring> m_args;
};

}