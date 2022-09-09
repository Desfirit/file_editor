#pragma once
#include <string>
#include <fstream>
#include <locale>

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

namespace win
{
	#include <Windows.h>
}

namespace detail
{
	std::wstring ConvertUtf8ToWide(const std::string& str)
	{
		int count = win::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
		std::wstring wstr(count, 0);
		win::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
		return wstr;
	}

	std::string ConvertWideToUtf8(const std::wstring& wstr)
	{
		int count = win::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
		std::string str(count, 0);
		win::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
		return str;
	}
}

#define MGER

wstring read_file(const wstring& path)
{

#ifdef MGER

	std::ifstream fileStream{ path };

	auto buf{ fileStream.rdbuf() };

	string str(istreambuf_iterator{ buf }, {});

	return detail::ConvertUtf8ToWide(str);

#else
	wifstream fileStream{ path };

	locale locale(fileStream.getloc(), new std::codecvt_utf8<wchar_t>);

	//locale locale(fileStream.getloc(), new std::codecvt<wchar_t, char, mbstate_t>);

	const auto LocalName = locale.name();
	
	fileStream.imbue(locale);

	auto buf{ fileStream.rdbuf() };

	wstring res{ istreambuf_iterator<wchar_t>{ buf }, {} };
	return res;

#endif //  MGER
}

void write_file(const wstring& path, const wstring& data)
{
	ofstream fileStream{ path };

	auto utf8Str{ detail::ConvertWideToUtf8(data) };

	fileStream.write(utf8Str.c_str(), utf8Str.size() + 1);
}

#undef MGER