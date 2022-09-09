#include "commands/read_command.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <codecvt>

#include <utils/file_utils.h>

#include <nlohmann/json.hpp>
#include <tinyxml2/tinyxml2.h>

using namespace std;
using namespace filesystem;

namespace
{
	constexpr uintmax_t KB = 1024;
	constexpr uintmax_t MB = 1024 * KB;
	constexpr uintmax_t GB = 1024 * MB;

	constexpr uintmax_t operator""_GB(const uintmax_t bytes)
	{
		return bytes * GB;
	}

	constexpr uintmax_t operator""_MB(const uintmax_t bytes)
	{
		return bytes * MB;
	}

	constexpr uintmax_t operator""_KB(const uintmax_t bytes)
	{
		return bytes * KB;
	}

	struct HumanReadable {
		std::uintmax_t size{};

		operator wstring()
		{
			int i{};
			double mantissa = size;

			for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}

			mantissa = std::ceil(mantissa * 10.) / 10.;

			wostringstream woss;

			woss << mantissa << L"BKMGTPE"[i];
			i == 0 ? woss : woss << L"B (" << size << L')';

			return woss.str();
		}

	private: friend
		std::wostream& operator<<(std::wostream& os, HumanReadable hr) {
		int i{};
		double mantissa = hr.size;

		for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}

		mantissa = std::ceil(mantissa * 10.) / 10.;

		os << mantissa << L"BKMGTPE"[i];
		return i == 0 ? os : os << L"B (" << hr.size << L')';
	}
	};

	wstring ask_input_wstring(const wstring& message)
	{
		wcout << message;

		wstring input;
		getline(wcin >> ws, input);

		return input;
	}

	void read_simple_file(path& file)
	{
		try
		{
			wcout << read_file(file) << L'\n';
		}
		catch (runtime_error& err)
		{
			throw UnexpectedError{ err.what() };
		}
	}

	void read_xml(path& file)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(file.c_str());
	}
}

ReadCommand::ReadCommand(vector<wstring>::const_iterator beg, vector<wstring>::const_iterator end)
{
	if (distance(beg,end) != 1)
		throw WrongArgumentsError{ L"Не верное количество аргументов", {beg, end} };

	m_targetFile = *beg;

	if (!exists(m_targetFile))
		throw WrongArgumentsError{ L"Файла не существует", {beg, end} };


	error_code err;
	m_targetFile = canonical(*beg, err);

	if (err) //Если кто-то успел изменить имя файла
		throw WrongArgumentsError{ L"Имя файла было изменено", {beg, end} };

	uintmax_t fileSize;
	if (fileSize = file_size(m_targetFile, err); err)
		throw WrongArgumentsError{ L"Файла не существует", {beg, end} };

	if (fileSize > 2_GB)
		throw UnexpectedError{ wstring{L"Файл слишком большой - "} + static_cast<wstring>(HumanReadable{fileSize}) };
}

vector<Arg> ReadCommand::get_command_args()
{
	return { {m_targetFile.wstring(), CommandContextType::FilePath} };
}

void ReadCommand::exec()
{
	auto fileExt{ m_targetFile.extension() };

	if (fileExt == ".json")
	{

	}
	else if (fileExt == ".xml")
	{

	}
	else
	{
		read_simple_file(m_targetFile);
	}
}