#include "proxy/dllproxy.h"

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD ulReasonForCall, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);

	if (ulReasonForCall == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Proxy::Attach), hModule, 0, nullptr);

	else if (ulReasonForCall == DLL_PROCESS_DETACH)
		Proxy::Detach(false);

	return TRUE;
}
