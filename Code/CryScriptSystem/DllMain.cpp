#include "ScriptSystem.h"

// this garbage includes windows.h
#include "CryCommon/CryCore/platform_impl.h"

extern "C" DLL_EXPORT IScriptSystem *CreateScriptSystem(ISystem *pSystem, bool bStdLibs)
{
	ModuleInitISystem(pSystem);

	ScriptSystem *pScriptSystem = new ScriptSystem;
	pScriptSystem->Init();

	return pScriptSystem;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	return TRUE;
}
