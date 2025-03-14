#include "Library/DLL.h"
#include "Library/WinAPI.h"

#include "Patch.h"

using WinAPI::RVA;
using WinAPI::FillNOP;
using WinAPI::FillMem;

///////////////
// CryAction //
///////////////

/**
 * @brief Allows connecting to DX10 servers with game running in DX9 mode.
 */
void Patch::AllowDX9ImmersiveMultiplayer(const DLL & CryAction)
{
	void *pCryAction = CryAction.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCryAction, 0x2B394D), 0x1E);
	FillNOP(RVA(pCryAction, 0x2B6860), 0x1A);
#else
	FillNOP(RVA(pCryAction, 0x1D698A), 0x1A);
	FillNOP(RVA(pCryAction, 0x1D89FC), 0x15);
#endif
}

/**
 * @brief Disables useless "times out" log messages from the Break Replicator.
 */
void Patch::DisableBreakLog(const DLL & CryAction)
{
	void *pCryAction = CryAction.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCryAction, 0x2D183F), 0x5);
#else
	FillNOP(RVA(pCryAction, 0x1E987D), 0x5);
#endif
}

////////////////
// CryNetwork //
////////////////

/**
 * @brief Allows connecting to Internet servers without GameSpy account.
 */
void Patch::FixInternetConnect(const DLL & CryNetwork)
{
	void *pCryNetwork = CryNetwork.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCryNetwork, 0x189896), 0x18);
#else
	FillNOP(RVA(pCryNetwork, 0x3FB7C), 0xD);
#endif
}

/**
 * @brief Unlocks advantages of pre-ordered version for everyone.
 * This is both server-side and client-side patch.
 */
void Patch::EnablePreordered(const DLL & CryNetwork)
{
	const uint8_t code[] = {
#ifdef BUILD_64BIT
		0xC6, 0x83, 0x70, 0xFA, 0x00, 0x00, 0x01  // mov byte ptr ds:[rbx+0xFA70], 0x1
#else
		0xC6, 0x83, 0xC8, 0xF3, 0x00, 0x00, 0x01  // mov byte ptr ds:[ebx+0xF3C8], 0x1
#endif
	};

	void *pCryNetwork = CryNetwork.GetHandle();

#ifdef BUILD_64BIT
	FillMem(RVA(pCryNetwork, 0x17C377), code, sizeof code);
#else
	FillMem(RVA(pCryNetwork, 0x43188), code, sizeof code);
#endif
}

/**
 * @brief Prevents server from kicking players with the same CD key.
 * This is server-side patch.
 */
void Patch::AllowSameCDKeys(const DLL & CryNetwork)
{
	void *pCryNetwork = CryNetwork.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCryNetwork, 0xE0328), 0x47);
#else
	FillNOP(RVA(pCryNetwork, 0x606A5), 0x4);
#endif
}

///////////////
// CrySystem //
///////////////

/**
 * @brief Disables the SecuROM crap in 64-bit CrySystem.
 * It does nothing in 32-bit build.
 */
void Patch::RemoveSecuROM(const DLL & CrySystem)
{
	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCrySystem, 0x470B9), 0x16);
#endif
}

/**
 * @brief Makes DX9 mode the default.
 * It's still possible to use the "-dx10" command line parameter to run the game in DX10 mode.
 */
void Patch::MakeDX9Default(const DLL & CrySystem)
{
	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCrySystem, 0x46719), 0x1F);
#else
	FillNOP(RVA(pCrySystem, 0x59D86), 0x5);
#endif
}

/**
 * @brief Allows Very High settings in DX9 mode.
 */
void Patch::AllowDX9VeryHighSpec(const DLL & CrySystem)
{
	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCrySystem, 0x4674C), 0x54);
#else
	FillNOP(RVA(pCrySystem, 0x59DA8), 0x4B);
#endif
}

/**
 * @brief Allows running multiple instances of Crysis at once.
 * Note that the first check if any instance is already running is normally done in launcher.
 */
void Patch::AllowMultipleInstances(const DLL & CrySystem)
{
	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCrySystem, 0x42BFF), 0x68);
#else
	FillNOP(RVA(pCrySystem, 0x5794F), 0x58);
#endif
}

/**
 * @brief Prevents the engine from installing its own broken unhandled exceptions handler.
 */
void Patch::UnhandledExceptions(const DLL & CrySystem)
{
	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCrySystem, 0x22946), 0x6);
	FillNOP(RVA(pCrySystem, 0x22952), 0x7);
	FillNOP(RVA(pCrySystem, 0x467A5), 0x16);
#else
	FillNOP(RVA(pCrySystem, 0x17D67), 0x5);
	FillNOP(RVA(pCrySystem, 0x17D72), 0xC);
	FillNOP(RVA(pCrySystem, 0x59DF8), 0x13);
#endif
}

/**
 * @brief Disables use of 3DNow! instructions.
 * This patch correctly fixes the well-known crash of 32-bit Crysis on modern AMD processors.
 */
void Patch::Disable3DNow(const DLL & CrySystem)
{
	// default CPU feature flags without CPUF_3DNOW
	const uint8_t flags = 0x18;

	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillMem(RVA(pCrySystem, 0xA0FF), &flags, sizeof flags);
#else
	FillMem(RVA(pCrySystem, 0x93E2), &flags, sizeof flags);
#endif
}

/**
 * @brief Disables useless "IO Error=" log messages from the Stream Engine.
 */
void Patch::DisableIOErrorLog(const DLL & CrySystem)
{
	void *pCrySystem = CrySystem.GetHandle();

#ifdef BUILD_64BIT
	FillNOP(RVA(pCrySystem, 0x7B23C), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B5E4), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B62C), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B65E), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B692), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B6DF), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B724), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B76A), 0x5);
	FillNOP(RVA(pCrySystem, 0x7B982), 0x5);
	FillNOP(RVA(pCrySystem, 0x7BAE1), 0x5);
	FillNOP(RVA(pCrySystem, 0x7BB98), 0x5);
	FillNOP(RVA(pCrySystem, 0x7BCDA), 0x5);
	FillNOP(RVA(pCrySystem, 0x7C51D), 0x5);
#else
	FillNOP(RVA(pCrySystem, 0x780CB), 0x5);
	FillNOP(RVA(pCrySystem, 0x781AF), 0x5);
	FillNOP(RVA(pCrySystem, 0x78490), 0x5);
	FillNOP(RVA(pCrySystem, 0x784CF), 0x5);
	FillNOP(RVA(pCrySystem, 0x7850D), 0x5);
	FillNOP(RVA(pCrySystem, 0x78549), 0x5);
	FillNOP(RVA(pCrySystem, 0x7859E), 0x5);
	FillNOP(RVA(pCrySystem, 0x785D6), 0x5);
	FillNOP(RVA(pCrySystem, 0x7861C), 0x5);
	FillNOP(RVA(pCrySystem, 0x78744), 0x5);
#endif
}
