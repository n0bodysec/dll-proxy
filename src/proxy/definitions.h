#pragma once

#define DLL_NAME "version.dll"
#define ALLFUNC(FUNC) \
	FUNC(0x00, GetFileVersionInfoA, 1) \
	FUNC(0x01, GetFileVersionInfoByHandle, 2) \
	FUNC(0x02, GetFileVersionInfoExA, 3) \
	FUNC(0x03, GetFileVersionInfoExW, 4) \
	FUNC(0x04, GetFileVersionInfoSizeA, 5) \
	FUNC(0x05, GetFileVersionInfoSizeExA, 6) \
	FUNC(0x06, GetFileVersionInfoSizeExW, 7) \
	FUNC(0x07, GetFileVersionInfoSizeW, 8) \
	FUNC(0x08, GetFileVersionInfoW, 9) \
	FUNC(0x09, VerFindFileA, 10) \
	FUNC(0x0A, VerFindFileW, 11) \
	FUNC(0x0B, VerInstallFileA, 12) \
	FUNC(0x0C, VerInstallFileW, 13) \
	FUNC(0x0D, VerLanguageNameA, 14) \
	FUNC(0x0E, VerLanguageNameW, 15) \
	FUNC(0x0F, VerQueryValueA, 16) \
	FUNC(0x10, VerQueryValueW, 17) \

#define ALLFUNC_COUNT 0x11
#pragma endregion
