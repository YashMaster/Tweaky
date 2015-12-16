#pragma once
#include "stdafx.h"
#include "C.h"
#include "Keyboard.h"

class VolumeHandler
{
private:
	//For SendInput Method
	static const int MaxVolume = 100;
	static const int MinVolume = 0;

	byte KeyCodeUp[2], KeyCodeDown[2];
	INPUT InputUp[2], InputDown[2];
	INPUT *FullInputUp, *FullInputDown;
	const wchar_t *VolumeUp = L"{VK_VOLUME_UP}";
	const wchar_t *VolumeDown = L"{VK_VOLUME_DOWN}";
	int Length;
	bool IsInitialized = false;

protected:
public:

	//There can only be one vol-andler!
	VolumeHandler() {}

	//Initializes stuff
	bool Init()
	{
		//This needs to be expanded to take up 100. 
		this->Length = StringToVirtualKeyArray(VolumeUp, KeyCodeUp);
		if (BuildStringInput(InputUp, KeyCodeUp, this->Length))
		{
			printf("VolumeHandler.Init().BuildShortcutInput() failed! \n");
			return false;
		}
		this->Length *= 2;

		//This needs to be expanded to take up 100. 
		this->Length = StringToVirtualKeyArray(VolumeDown, KeyCodeDown);
		if (BuildStringInput(InputDown, KeyCodeDown, this->Length))
		{
			printf("VolumeHandler.Init().BuildShortcutInput() failed! \n");
			return false;
		}
		this->Length *= 2;

		IsInitialized = true;
		return true;
	}

	//Increments or decrments the volume by the value specified by @delta
	bool Increment(int delta)
	{
		//If we weren't initialized properly, default to the static method
		if (IsInitialized == false)
			return VolumeHandler::StaticIncrement(delta);

		//Ensure delta is within [-MaxVolume, MaxVolume]
		if (delta > MaxVolume)
			delta = MaxVolume;
		else if (delta < -MaxVolume)
			delta = -MaxVolume;

		//If it's a positive delta... increase the volume
		if (delta > 0)
			SendInput(2, InputUp, sizeof(INPUT));
		else if (delta < 0) //decrease the volume... 
			SendInput(2, InputDown, sizeof(INPUT));
		else if (delta == 0) //Just show the slider in this case I guess...
			VolumeHandler::ShowSlider();

		return true;
	}

	//Increments or decrments the volume by the value specified by @delta
	static bool StaticIncrement(int delta)
	{
		//Ensure delta is within [-MaxVolume, MaxVolume]
		if (delta > MaxVolume)
			delta = MaxVolume;
		else if (delta < -MaxVolume)
			delta = -MaxVolume;

		//If it's a positive delta... increase the volume
		if (delta > 0)
			SendShortcut(L"{VK_VOLUME_UP}");
		else if (delta < 0) 
			SendShortcut(L"{VK_VOLUME_DOWN}");
		else if (delta == 0) //Just show the slider in this case I guess...
			VolumeHandler::ShowSlider();

		return true;
	}

	//Shows the slider. Returns true on success. Note: this has no effect on volume
	static bool ShowSlider()
	{
		HWND sliderHwnd = FindWindow(L"NativeHWNDHost", L"");
		
		CONTINUE_IF(sliderHwnd != NULL);
		CONTINUE_IF(PostMessage(sliderHwnd, RegisterWindowMessage(L"SHELLHOOK"), 0x0C, 0xA0000));

		return true;
	}
};