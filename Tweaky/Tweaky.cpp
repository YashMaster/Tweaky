#include "stdafx.h"
#include "Windows.h"
#include "Taskbar.h"
#include "VolumeHandler.h"
#include "BrightnessHandler.h"

int main(int argc, char *argv[], wchar_t *envp[])
{
	printf("argv[0] = %s\n", argv[0]);
	printf("argv[1] = %s\n", argv[1]);

	if (strcmp(argv[1], "-full") == 0)
	{
		VolumeHandler::StaticIncrement(100);
	}
	if (strcmp(argv[1], "-mute") == 0)
	{
		VolumeHandler::StaticIncrement(-100);
	}
	if (strcmp(argv[1], "-increment") == 0)
	{
		VolumeHandler::StaticIncrement(10);
	}
	if (strcmp(argv[1], "-decrement") == 0)
	{
		VolumeHandler::StaticIncrement(-10);
	}
	//getchar();
    return 0;
}

