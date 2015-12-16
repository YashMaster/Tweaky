#include "stdafx.h"
#include "Windows.h"
#include "Taskbar.h"
#include "VolumeHandler.h"
#include "BrightnessHandler.h"

int main()
{
	Sleep(1000);
	BrightnessHandler::Increment(1000);
	getchar();
    return 0;
}

