#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace detail
{
	inline vector<string> wstring_to_string(const vector<wstring>& args)
	{
		vector<string> temp;
		temp.reserve(args.size());

		transform(begin(args), end(args), back_inserter(temp), [](auto wstr) {
			return string{ begin(wstr), end(wstr) };
		});

		return temp;
	}

	inline wstring concat_args(const vector<wstring>& args)
	{
		wostringstream oss;

		copy(begin(args), end(args), ostream_iterator<wstring, wchar_t>(oss, L", "));

		return oss.str();
	}
}

struct WrongArgumentsError final : public runtime_error
{
	explicit WrongArgumentsError(const wstring& message, const vector<wstring>& args) : runtime_error(string{ begin(message), end(message) }) 
	{
		const auto argsStr{ detail::concat_args(args) };

		wcscpy_s(m_mes, _countof(m_mes), (message + L", аргументы: " + argsStr).c_str());
	}

	const wchar_t* whatEx() const
	{
		return m_mes;
	}

private:

	wchar_t m_mes[_MAX_PATH];
};

struct WrongCommandError final : public runtime_error
{
	explicit WrongCommandError(const wstring& message) : runtime_error(string{begin(message), end(message)}) 
	{
		wcscpy_s(m_mes, _countof(m_mes), message.c_str());
	}

	const wchar_t* whatEx() const
	{
		return m_mes;
	}

private:

	wchar_t m_mes[_MAX_PATH];
};

struct UnexpectedError final : public runtime_error
{
	explicit UnexpectedError(const wstring& message) : runtime_error(string{ begin(message), end(message) })
	{
		wcscpy_s(m_mes, _countof(m_mes), message.c_str());
	}

	explicit UnexpectedError(const char* message) : runtime_error(message)
	{
		size_t readen;
		mbstowcs_s(&readen, m_mes, _countof(m_mes), message, strlen(message));
	}

	const wchar_t* whatEx() const
	{
		return m_mes;
	}

private:

	wchar_t m_mes[_MAX_PATH];
};