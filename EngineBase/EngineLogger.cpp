#include "EnginePCH.h"
#include "EngineLogger.h"
#include <format>

EngineLogger::EngineLogger()
{
}

EngineLogger::~EngineLogger()
{
}

ENGINE_API void EngineLogger::StartLogger()
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

	std::cout << "Start Engine Logger Successful.\n";
}

ENGINE_API void EngineLogger::EndLogger()
{
	FreeConsole();
}

