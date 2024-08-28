#pragma once
#include "framework.h"

class EntryPoint
{
public:
	static bool Init(LPVOID lpParam);
	static bool Unload(bool free);

private:
	static void SetupConsole(bool unload = false);
};
