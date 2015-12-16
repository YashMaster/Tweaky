#pragma once
#include "Windows.h"
#include "stdint.h"

enum MouseFlagsEnum
{
	MOUSE_MOVE = 0x01,
	MOUSE_CLICK = 0x02,
	MOUSE_DOUBLE_CLICK = 0x04,
	MOUSE_RIGHT_CLICK = 0x08,
	MOUSE_DOUBLE_RIGHT_CLICK = 0x10,
	MOUSE_MIDDLE_CLICK = 0x20,
	MOUSE_DOUBLE_MIDDLE_CLICK = 0x40,
	MOUSE_WHEEL_UP = 0x80,
	MOUSE_WHEEL_DOWN = 0x100,
	MOUSE_WHEEL_LEFT = 0x200,
	MOUSE_WHEEL_RIGHT = 0x400,
};
typedef enum MouseFlagsEnum MouseFlags;

class Mouse
{
private:

	static POINT Convert(POINT inputMaxes, POINT outputMaxes, POINT input)
	{
		POINT output;

		double xRatio = ((double)outputMaxes.x) / ((double)inputMaxes.x);
		double yRatio = ((double)outputMaxes.y) / ((double)inputMaxes.y);

		output.x = LONG(((double)input.x) * xRatio);
		output.y = LONG(((double)input.y) * yRatio);

		//printf("Converting: [%d/%d, %d/%d] to [%d/%d, %d/%d]\n", input.x, inputMaxes.x, input.y, inputMaxes.y, output.x, outputMaxes.x, output.y, outputMaxes.y);
		//printf("Converting: [%d/%d(%.3f), %d/%d(%.3f)] to [%d/%d(%.3f), %d/%d(%.3f)]\n", input.x, inputMaxes.x, ((double) input.x / (double) inputMaxes.x), input.y, inputMaxes.y, ((double) input.y / (double) inputMaxes.y), output.x, outputMaxes.x, ((double) output.x / (double) outputMaxes.x), output.y, outputMaxes.y, ((double) output.y / (double) outputMaxes.y));

		return output;
	}

public:

	//The mouse input driver takes whack ass coordinates. Use this to get decent ones.
	static POINT ToMouseCoordinates(POINT maxes, POINT toConvert)
	{
		POINT mouseMaxes = { UINT16_MAX, UINT16_MAX };
		return Convert(maxes, mouseMaxes, toConvert);
	}

	//This function does all the heavy lifting
	static bool Action(POINT location, MouseFlags flags)
	{
		int i = 0;
		INPUT Input[16];
		Input[i].type = INPUT_MOUSE;
		Input[i].mi.dx = location.x;
		Input[i].mi.dy = location.y;
		Input[i].mi.time = 0;
		Input[i].mi.mouseData = 0;
		Input[i].mi.dwExtraInfo = 0;
		Input[i].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		i++;

		if (flags & MOUSE_CLICK)
		{
			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = 0;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;     //Clicks the mouse down.
			i++;

			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = 0;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_LEFTUP;       //Releases the mouse click.
			i++;
		}

		if (flags & MOUSE_RIGHT_CLICK)
		{
			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = 0;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;     //Clicks the mouse down.
			i++;

			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = 0;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_RIGHTUP;       //Releases the mouse click.
			i++;
		}

		if (flags & MOUSE_MIDDLE_CLICK)
		{
			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = 0;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;     //Clicks the mouse down.
			i++;

			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = 0;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;       //Releases the mouse click.
			i++;
		}

		if (flags & MOUSE_WHEEL_UP)
		{
			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = WHEEL_DELTA;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_WHEEL;
			i++;
		}

		if (flags & MOUSE_WHEEL_DOWN)
		{
			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = -WHEEL_DELTA;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_WHEEL;
			i++;
		}

		if (flags & MOUSE_WHEEL_LEFT)
		{
			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = -WHEEL_DELTA;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_HWHEEL;
			i++;
		}

		if (flags & MOUSE_WHEEL_RIGHT)
		{
			Input[i].type = INPUT_MOUSE;
			Input[i].mi.dx = location.x;
			Input[i].mi.dy = location.y;
			Input[i].mi.time = 0;
			Input[i].mi.mouseData = WHEEL_DELTA;
			Input[i].mi.dwExtraInfo = 0;
			Input[i].mi.dwFlags = MOUSEEVENTF_HWHEEL;
			i++;
		}

		SendInput(i, Input, sizeof(INPUT));
		return true;
	}

	static bool Action(HWND hwnd, MouseFlags flags)
	{
		RECT rect;
		POINT location;
		GetWindowRect(hwnd, &rect);
		location.x = (rect.left + rect.right) / 2;
		location.y = (rect.top + rect.bottom) / 2;
		POINT screenMaxes = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
		return Action(ToMouseCoordinates(screenMaxes, location), flags);
	}

	static bool Click(POINT location)
	{
		return Action(location, MOUSE_CLICK);
	}

	//Hides cursor somehow (currently by moving it off the screen)
	static bool Hide()
	{
		POINT cursorDest;
		cursorDest.x = UINT16_MAX;
		cursorDest.y = UINT16_MAX;
		return Mouse::Action(cursorDest, MOUSE_MOVE);
	}

	//Returns the location in whack-ass-mouse-coordinates
	static POINT GetLocation()
	{
		POINT pos;
		GetCursorPos(&pos);
		POINT screenMaxes = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
		POINT mouseMaxes = { UINT16_MAX, UINT16_MAX };
		return Convert(screenMaxes, mouseMaxes, pos);
	}

	//Sets location using whack-ass-mouse-coordinates
	static void SetLocation(POINT location)
	{
		Action(location, MOUSE_MOVE);
	}
};