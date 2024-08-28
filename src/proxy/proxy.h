#pragma once
#include "../framework.h"

class Proxy
{
public:
	static inline HMODULE HModule = nullptr;
	static inline HMODULE ProxyDll = nullptr;
	static inline bool IsUnloading = false;

	static DWORD WINAPI Attach(LPVOID lpParam);
	static bool Detach(bool free);
};
