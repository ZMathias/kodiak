// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com#pragma once
#pragma once
#include "globals.hpp"

void HidePayload(const std::wstring_view&);

inline constexpr std::wstring_view expectedInstallPath = L"F:\\prj\\kodiak\\x64\\Debug\\kodiak.exe";

std::wstring GetInstallPath();