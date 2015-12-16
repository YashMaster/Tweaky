#pragma once
#include <thread>
#include <Windows.h>
#include "C.h"

//Used in the GetBrightness function
#pragma comment (lib, "PowrProf.lib")
#include "Powersetting.h"
#include "PowrProf.h"


namespace BrightnessHandler
{

	//Shows the slider. Returns true on success. Note: this has no effect on screen brightness. This is done statically at the cost of perf. 
	bool static ShowSlider()
	{
		HWND hwnd = FindWindow(L"NativeHWNDHost", L"");
		CONTINUE_IF(hwnd != NULL);
		CONTINUE_IF(PostMessage(hwnd, RegisterWindowMessage(L"SHELLHOOK"), 0x0037, 0));
		//CONTINUE_IF(ShowWindow(hwnd, SW_SHOW));
		return true;
	}

	//Gets the AC and DC brightness indexes for the current power configuration. Returns @DCIndex or @ACIndex, depending on power status.
	DWORD static GetBrightness()
	{
		DWORD ACIndex = 69;
		DWORD DCIndex = 96;

		GUID *pPwrGUID;
		GUID subGUID = GUID_VIDEO_SUBGROUP;
		GUID BriGUID = GUID_DEVICE_POWER_POLICY_VIDEO_BRIGHTNESS;

		PowerGetActiveScheme(NULL, &pPwrGUID);
		PowerReadACValueIndex(NULL, pPwrGUID, &subGUID, &BriGUID, &ACIndex);
		PowerReadDCValueIndex(NULL, pPwrGUID, &subGUID, &BriGUID, &DCIndex);

		//Get the power status
		SYSTEM_POWER_STATUS powerStatus;
		FAIL_IF(!GetSystemPowerStatus(&powerStatus));

		if (powerStatus.ACLineStatus)
			return ACIndex;

		return DCIndex;
	}

	//Sets brightness from [0, 100] using the PowerWriteACValueIndex() method. 
	bool static SetBrightness(int val)
	{
		GUID *pPwrGUID;
		GUID subGUID = GUID_VIDEO_SUBGROUP;
		GUID briGUID = GUID_DEVICE_POWER_POLICY_VIDEO_BRIGHTNESS;

		FAIL_IF((PowerGetActiveScheme(NULL, &pPwrGUID) != ERROR_SUCCESS));
		FAIL_IF(PowerWriteACValueIndex(NULL, pPwrGUID, &subGUID, &briGUID, val) != ERROR_SUCCESS);
		FAIL_IF(PowerWriteDCValueIndex(NULL, pPwrGUID, &subGUID, &briGUID, val) != ERROR_SUCCESS);
		//if (PowerApplySettingChanges != NULL) PowerApplySettingChanges(&subGUID, &briGUID);
		FAIL_IF(PowerSetActiveScheme(NULL, pPwrGUID) != ERROR_SUCCESS);

		return true;
	}

	//Increments the brightness by @increment. Negative values are supported. 
	bool static Increment(int increment)
	{
		//Show the slider
		BrightnessHandler::ShowSlider();

		//Gets the brightness. 
		DWORD Index;
		Index = BrightnessHandler::GetBrightness();

		//Exit quickly if this function will have no change in brightness. 
		if (increment == 0 ||
			Index == 100 && increment >= 0 ||
			Index == 0 && increment <= 0)
			return true;

		//Enforce the range on the Index
		if ((int)Index + increment >= 100)
			Index = 100;
		else if ((int)Index + increment <= 0)
			Index = 0;
		else
			Index += increment;

		//Set the brightness, and peace out. 
		BrightnessHandler::SetBrightness(Index);

		return true;
	}

};

