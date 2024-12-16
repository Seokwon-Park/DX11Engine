#pragma once
#include <assert.h>

#define ENGINE_DLL_BUILD

#ifdef _DEBUG
#define MSGASSERT(VALUE)	{																\
							std::string ErrorText = VALUE;									\
							MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK);	\
							assert(false);													\
							}

#define	DBGPRINT(VALUE)		{								\
							std::string ResultText = VALUE;	\
							ResultText += "\n";				\
							OutputDebugStringA(ResultText.c_str());\
							}
#else
#define MSGASSERT(VALUE)	((void)0)
#define	DBGPRINT(VALUE)		((void)0)
#endif

namespace UEngineDebug
{
	ENGINE_API void LeakCheck();
}

