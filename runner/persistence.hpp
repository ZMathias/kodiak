#pragma once
#include "globals.hpp"

constexpr std::wstring_view expectedInstallPath = L"F:\\prj\\kodiak\\x64\\Debug\\kodiak.exe";

void HidePayload(const std::wstring_view&);

std::wstring GetInstallPath();