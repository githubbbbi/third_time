#include "DxLib.h"
#include "System/System.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
				   _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	System *system = new System;
	system->Main();
	delete system;

	return 0;
}