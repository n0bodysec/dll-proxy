#include "dllproxy.h"
#include "../entrypoint.h"
#include "definitions.h"
#include <string>

FARPROC p[ALLFUNC_COUNT] = { 0 };

bool LoadProxy()
{
	char buffer[MAX_PATH];
	if (GetSystemDirectoryA(buffer, MAX_PATH) != 0)
	{
		std::string fullPath = buffer + std::string(DLL_NAME);
		Proxy::proxyDll = LoadLibraryA(fullPath.c_str());

		if (!Proxy::proxyDll)
		{
#ifdef _DEBUG
			std::string message = "Unable to load " + fullPath;
			MessageBoxA(NULL, message.c_str(), "dll proxy", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif
			return false;
		}

#define REGISTER(num, name, ordinal) p[num] = GetProcAddress(Proxy::proxyDll, #name);
		ALLFUNC(REGISTER);
#undef REGISTER

		return true;
	}

	return false;
}

bool Proxy::Attach(LPVOID lpParam)
{
	Proxy::hModule = reinterpret_cast<HMODULE>(lpParam);

	if (!LoadProxy()) return false;

#ifdef _DEBUG
	MessageBoxA(NULL, "It's working!", "dll proxy", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
#endif

	// load app entrypoint
	EntryPoint::Init();

	return true;
}

bool Proxy::Detach(bool free)
{
	if (!Proxy::proxyDll) return false;

	Proxy::isUnloading = true;

	if (free) FreeLibraryAndExitThread(Proxy::hModule, 0);
	return true;
}

#ifdef _M_AMD64
#pragma warning (disable: 4081)
#define STRINGIFY(name) #name
#define EXPORT_FUNCTION comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
#define DEF_STUB(num, name, ordinal) \
	__declspec(dllexport) void WINAPI _##name() \
	{ \
		__pragma(STRINGIFY(EXPORT_FUNCTION)); \
		p[num](); \
	}
#else
#define DEF_STUB(num, name, ordinal) \
extern "C" __declspec(naked) void __stdcall _##name() \
{ \
	__asm \
	{ \
		jmp p[num * 4] \
	} \
};
#endif

ALLFUNC(DEF_STUB)
#undef DEF_STUB