#include "entrypoint.h"
#include "proxy/dllproxy.h"
#include <iostream>

bool EntryPoint::Init()
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	return true;
}

bool EntryPoint::Unload()
{
	fclose(stdout);
	FreeConsole();

	Proxy::Detach(true);

	return true;
}