#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

namespace details
{
	template <typename It>
	It remove_multi_whitespace(It it, It end_it)
	{
		return unique(it, end_it, [](const auto& a, const auto& b) {
			return iswspace(a) && iswspace(b);
			});
	}

	template <typename InIt, typename OutIt, typename T, typename F>
	InIt split(InIt it, InIt end_it, OutIt out_it, T split_val, F bin_func)
	{
		while (it != end_it) {
			auto slice_end(find(it, end_it, split_val));
			*out_it++ = bin_func(it, slice_end);
			if (slice_end == end_it) { return end_it; }
			it = next(slice_end);
		}
		return it;
	}
}

inline vector<wstring> convert(int argc, const wchar_t* argv[])
{
	if (argc <= 0)
		throw runtime_error{"argc <= 0, argc = " + to_string(argc)};

	vector<wstring> args{};

	args.reserve(argc);

	for(int i = 0; i < argc; ++i)
		args.emplace_back(argv[i]);

	return args;
}

inline vector<wstring> convert(const wstring& cmdLine)
{
	auto string_maker([](auto it_beg, auto it_end) {
		return wstring(it_beg, it_end);
	});

	auto filteredLine = cmdLine;
	filteredLine.erase(details::remove_multi_whitespace(begin(filteredLine), end(filteredLine)));

	vector<wstring> args;
	wistringstream wiss{ filteredLine};
	wstring arg;
	while (wiss >> quoted(arg, L'\"', L'%'))
	{
		args.push_back(arg);
	}

	return args;
}