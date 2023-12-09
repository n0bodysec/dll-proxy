#pragma once

class EntryPoint
{
public:
	static bool Init();
	static bool Unload(const bool free);

private:
	static void SetupConsole(const bool unload = false);
};