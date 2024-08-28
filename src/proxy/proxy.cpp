#include "proxy.h"
#include "definitions.h"
#include "../entrypoint.h"
#include <string>

extern "C" FARPROC p[ALLFUNC_COUNT] = { nullptr };

bool LoadProxy()
{
	if (char path[MAX_PATH]; GetSystemDirectoryA(path, MAX_PATH) != 0)
	{
		const std::string fullPath = path + std::string("\\") + std::string(DLL_NAME);
		Proxy::ProxyDll = LoadLibraryA(fullPath.c_str());

		if (!Proxy::ProxyDll)
		{
#ifdef _DEBUG
			const std::string message = "Unable to load " + fullPath;
			MessageBoxA(nullptr, message.c_str(), "dll proxy", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif
			return false;
		}

#define REGISTER(num, name, ordinal) p[num] = GetProcAddress(Proxy::ProxyDll, #name); // MAKEINTRESOURCEA(ordinal) for unnamed
		ALLFUNC(REGISTER)
#undef REGISTER

		return true;
	}

	return false;
}

DWORD WINAPI Proxy::Attach(const LPVOID lpParam)
{
	HModule = static_cast<HMODULE>(lpParam);

	if (!LoadProxy()) return false;

#ifdef _DEBUG
	MessageBoxA(nullptr, "It's working!", "dll proxy", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
#endif

	// load app entrypoint
	return EntryPoint::Init(lpParam);
}

bool Proxy::Detach(const bool free)
{
	if (!ProxyDll) return false;

	IsUnloading = true;

	if (free) FreeLibraryAndExitThread(HModule, 0);
	return true;
}

#define DEF_STUB(num, name, ordinal) extern "C" __declspec(naked) void _##name() { p[num](); }
ALLFUNC(DEF_STUB)
#undef DEF_STUB
