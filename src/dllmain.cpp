#include "entrypoint.h"
#include "framework.h"
#include "proxy/proxy.h"

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD ulReasonForCall, [[maybe_unused]] LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);

	if (ulReasonForCall == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, Proxy::Attach, hModule, 0, nullptr);

	else if (ulReasonForCall == DLL_PROCESS_DETACH)
		EntryPoint::Unload(false);

	return TRUE;
}
