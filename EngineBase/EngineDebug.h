#pragma once
#include <assert.h>

#define BASE_DLL

#ifdef _DEBUG
#define MSGASSERT(VALUE)	{																\
							std::string ErrorText = VALUE;									\
							MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK);	\
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
	BASE_API void LeakCheck();
}

