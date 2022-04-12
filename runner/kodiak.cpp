// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "globals.hpp"
#include "persistence.hpp"
#include "communications.hpp"

bool isShowing{false};
std::stop_source stopSource{};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HHOOK SetKeyboardHook()
{
	HOOKPROC hookProc{};
    static HINSTANCE hHookDll{};
    //load keyboardproc dll
    hHookDll = LoadLibrary(L"extern-tools.dll");

    //get functions memory address
    hookProc = reinterpret_cast<HOOKPROC>(GetProcAddress(hHookDll, "KeyboardProc"));

    return SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, hHookDll, 0);
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    startTime = std::chrono::steady_clock::now();
    // Register the window class.
    constexpr wchar_t CLASS_NAME[]  = L" ";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                             
        CLASS_NAME,                    
        L" ",
        WS_BORDER,
        0, 0, 10, 10,
        nullptr,
        nullptr,
        hInstance,
        nullptr
        );

    if (hwnd == nullptr)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    CheckInstallation();

	std::jthread poll_thread(StartPolling, GetCurrentThreadId());
    stopSource = poll_thread.get_stop_source();

    const HHOOK hHook = SetKeyboardHook();

    RegisterHotKey(hwnd, 1, MOD_ALT | MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, VK_NUMLOCK);

    ShowWindow(hwnd, SW_HIDE);

    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hHook);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
		stopSource.request_stop();
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // Do paint here
            FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1)));

            EndPaint(hwnd, &ps);
        }
        return 0;
    case WM_HOTKEY:
	    {
		    PostQuitMessage(0);
			return 0;
	    }
    default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}