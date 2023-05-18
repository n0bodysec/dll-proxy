#pragma once

#include "../framework.h"

class Proxy
{
public:
	static inline HMODULE hModule = nullptr;
	static inline HMODULE proxyDll = nullptr;
	static inline bool isUnloading = false;

	static bool Attach(LPVOID lpParam);
	static bool Detach(bool free);
};