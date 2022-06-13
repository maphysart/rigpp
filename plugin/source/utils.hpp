/*
uitls.hpp 
Functions used by other files. Make them inline to get rig of linker errors (duplicate symbols).
*/
#pragma	once

#include <string>
#include <chrono>

using namespace std;

inline bool endswith(const string& str, const string& suffix)
{
	return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

inline bool startswith(const string& str, const string& prefix)
{
	return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

inline string replaceString(string subject, const string& search, const string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

template <typename... Args>
inline string formatString(const char* format, Args... args)
{
	int nsize = snprintf(NULL, 0, format, args...) + 1;
	char* buffer = new char[nsize];
	snprintf(buffer, nsize, format, args...);
	string s(buffer);
	delete[] buffer;
	return s;
}