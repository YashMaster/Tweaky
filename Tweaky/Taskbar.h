#pragma once
#include <stdio.h>
#include <Windows.h>
#include "Mouse.h"
#include "Keyboard.h"

namespace Taskbar
{

	HWND GetShowDesktopButtonHwnd()
	{
		HWND hwnd = NULL;
		HWND parent = FindWindow(L"Shell_TrayWnd", NULL);
		HWND child = FindWindowEx(parent, NULL, L"TrayNotifyWnd", NULL);
		hwnd = FindWindowEx(child, NULL, L"TrayShowDesktopButtonWClass", NULL);
		return hwnd;
	}

	bool HideShowDesktopButton()
	{
		HWND hwnd = GetShowDesktopButtonHwnd();
		bool ret = (bool)ShowWindow(hwnd, 0);
		return ret;
	}

	HWND GetClockHwnd()
	{
		HWND hwnd = NULL;
		HWND parent = FindWindow(L"Shell_TrayWnd", NULL);
		HWND child = FindWindowEx(parent, NULL, L"TrayNotifyWnd", NULL);
		hwnd = FindWindowEx(child, NULL, L"TrayClockWClass", NULL);
		return hwnd;
	}

	bool ShowCalendar()
	{
		bool ret = false;
		HWND hwnd = GetClockHwnd();
		POINT ogLocation = Mouse::GetLocation();
		Mouse::Action(hwnd, MOUSE_CLICK);
		Mouse::SetLocation(ogLocation);
		return ret;
	}

	bool HideCalendar()
	{
		wchar_t classname[MAX_PATH];
		HWND fgw = GetForegroundWindow();
		GetClassName(fgw, classname, MAX_PATH);
		if (wcscmp(L"Windows.UI.Core.CoreWindow", classname) == 0)
			SendShortcut(L"{VK_ESCAPE}");
		return true;
	}

	bool ToggleCalendar()
	{
		wchar_t classname[MAX_PATH];
		HWND fgw = GetForegroundWindow();
		GetClassName(fgw, classname, MAX_PATH);
		if (wcscmp(L"Windows.UI.Core.CoreWindow", classname) == 0)
			SendShortcut(L"{VK_ESCAPE}");
		else
			ShowCalendar();

		return true;
	}



	//This didn't work :(
	bool ShowCalendar2()
	{
		bool ret = false;
		HWND hwnd = GetClockHwnd();
		printf("clockhwnd  = %d\n", hwnd);

		Sleep(1000);
		ret = SendMessage(hwnd, WM_USER + 104, 0x02, 0x00);
		Sleep(1000);
		ret = SendMessage(hwnd, WM_USER + 103, 0x01, 0x00);
		Sleep(1000);
		ret = SendMessage(hwnd, WM_USER + 104, 0x03, 0x00);
		Sleep(1000);
		ret = SendMessage(hwnd, WM_USER + 102, 0x01, 0x00);
		return ret;
	}

}