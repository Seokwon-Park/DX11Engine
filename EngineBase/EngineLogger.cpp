#include "EnginePCH.h"
#include "EngineLogger.h"
#include <format>

EngineLogger::EngineLogger()
{
}

EngineLogger::~EngineLogger()
{
}

BASE_API void EngineLogger::StartLogger()
{
	AllocConsole();
	FILE* PtrCin= nullptr;
	FILE* PtrCout = nullptr;
	FILE* PtrErr= nullptr;
	errno_t Err;

	Err = freopen_s(&PtrCout, "CONOUT$", "w", stdout);
	if (PtrCout != stdout)
	{
		fclose(PtrErr);
	}
	Err = freopen_s(&PtrCin, "CONIN$", "r", stdin);
	if (PtrCin != stdin)
	{
		fclose(PtrCin);
	}
	Err = freopen_s(&PtrErr, "CONERR$", "w", stderr);
	if (PtrErr != stderr)
	{
		fclose(PtrErr);
	}

	HWND hwnd = ::GetConsoleWindow();
	if (hwnd != NULL)
	{
		HMENU hMenu = ::GetSystemMenu(hwnd, FALSE);
		if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}

	std::cout << "Start Engine Logger Successful.\n";
}

BASE_API void EngineLogger::EndLogger()
{
	FreeConsole();
}

