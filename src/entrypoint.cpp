#include "entrypoint.h"
#include "framework.h"
#include "proxy/proxy.h"
#include <iostream>

bool EntryPoint::Init()
{
	SetupConsole();

	return true;
}

bool EntryPoint::Unload(const bool free)
{
	SetupConsole(true);

	return Proxy::Detach(free);
}

void EntryPoint::SetupConsole(const bool unload)
{
	if (unload)
	{
		fclose(stdout);
		FreeConsole();
		return;
	}
	
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
}

