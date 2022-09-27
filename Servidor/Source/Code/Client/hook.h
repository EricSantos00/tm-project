#ifndef __HOOK_H__
#define __HOOK_H__

#include "singleton.h"
#include <Windows.h>
#include <new>
#include <string>

enum class eHookType
{
	// Inconditional Jump 
	JMP = 1, // 0xE9

	// Call
	CALL, // 0xE8

	JE, // 0xF 0x84
	JZ,
	JNZ, // 0xF 0x85
	JNE,

	// Signed Jumps
	JL, // 0xF 0x8C
	JGE, // 0xF 0x8D
	JLE, // 0xF 0x8E
	JG, // 0xF 0x8F

	// Unsigned Jumps
	JB, // 0xF 0x82
	JNB, // 0xF 0x83
	JBE, // 0xF 0x86
	JA // 0xF 0x87
};

class HookMgr : public Singleton<HookMgr>
{
public:
	void SetHook(const eHookType hType, unsigned int hSourceAddress, unsigned int hDestAddress, unsigned int hNopSize = 0)
	{
		DWORD protect = 0;

		auto instructionSize = [](const eHookType type)
		{
			unsigned int size = 0;
			switch (type)
			{
			case eHookType::JMP:
			case eHookType::CALL:
				size = 5;
				break;
			default:
				size = 6;
				break;
			}
			return size;
		}(hType);

		auto instruction = new (std::nothrow) unsigned char[instructionSize + hNopSize];

		if (instruction == nullptr)
			return;

		auto distance = ((hDestAddress - hSourceAddress) - instructionSize);

		unsigned int distanceOffset = 0;

		if (hType == eHookType::JMP || hType == eHookType::CALL)
			distanceOffset = 1;
		else
			distanceOffset = 2;

		switch (hType)
		{
		case eHookType::JMP:
			instruction[0] = 0xE9;
			break;
		case eHookType::CALL:
			instruction[0] = 0xE8;
			break;
		case eHookType::JE:
		case eHookType::JZ:
			instruction[0] = 0x0F;
			instruction[1] = 0x84;
			break;
		case eHookType::JNZ:
		case eHookType::JNE:
			instruction[0] = 0x0F;
			instruction[1] = 0x85;
			break;
		case eHookType::JL:
			instruction[0] = 0x0F;
			instruction[1] = 0x8C;
			break;
		case eHookType::JGE:
			instruction[0] = 0x0F;
			instruction[1] = 0x8D;
			break;
		case eHookType::JLE:
			instruction[0] = 0x0F;
			instruction[1] = 0x8E;
			break;
		case eHookType::JG:
			instruction[0] = 0x0F;
			instruction[1] = 0x8F;
			break;
		case eHookType::JB:
			instruction[0] = 0x0F;
			instruction[1] = 0x82;
			break;
		case eHookType::JNB:
			instruction[0] = 0x0F;
			instruction[1] = 0x83;
			break;
		case eHookType::JBE:
			instruction[0] = 0x0F;
			instruction[1] = 0x86;
			break;
		case eHookType::JA:
			instruction[0] = 0x0F;
			instruction[1] = 0x87;
			break;
		}

		*(unsigned int*)&instruction[distanceOffset] = distance;

		if (hNopSize > 0)
		{
			for (unsigned int i = 0; i < hNopSize; i++)
				instruction[i + instructionSize] = 0x90;
		}

		if (VirtualProtect(reinterpret_cast<void*>(hSourceAddress), instructionSize + hNopSize, PAGE_EXECUTE_READWRITE, &protect) == 0)
			return;

		memcpy(reinterpret_cast<void*>(hSourceAddress), instruction, instructionSize + hNopSize);

		if (VirtualProtect(reinterpret_cast<void*>(hSourceAddress), instructionSize + hNopSize, protect, &protect) == 0)
			return;

		FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<const void*>(hSourceAddress),
			instructionSize + hNopSize);

		delete[] instruction;
	}

	template<typename I>
	void SetValue(unsigned int hSourceAddress, I hValue)
	{
		DWORD protect = 0;
		if (VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), sizeof(I), PAGE_EXECUTE_READWRITE, &protect) == 0)
			return;

		*(I*)hSourceAddress = hValue;

		if (VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), sizeof(I), protect, &protect) == 0)
			return;
	}
	template<typename I>
	void SetValue(unsigned int hSourceAddress, I hValue, unsigned int hSize)
	{
		DWORD protect = 0;
		if (VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), hSize, PAGE_EXECUTE_READWRITE, &protect) == 0)
			return;

		*(I*)hSourceAddress = hValue;

		if (VirtualProtect(reinterpret_cast<LPVOID>(hSourceAddress), hSize, protect, &protect) == 0)
			return;
	}

	void fillWithNop(unsigned int hAddress, unsigned int hNopCount)
	{
		DWORD p = 0;
		if (VirtualProtect(reinterpret_cast<LPVOID>(hAddress), hNopCount, PAGE_EXECUTE_READWRITE, &p) == 0)
			return;

		for (unsigned int i = 0; i < hNopCount; i++)
			*(unsigned char*)(hAddress + i) = 0x90;

		if (VirtualProtect(reinterpret_cast<LPVOID>(hAddress), hNopCount, p, &p) == 0)
			return;
	}
	unsigned int GetPtr(const void* ptr)
	{
		return reinterpret_cast<unsigned int>(ptr);
	}
protected:
	friend class Singleton<HookMgr>;
	HookMgr() {}
	virtual ~HookMgr() {}
	HookMgr(const HookMgr&) = delete;
	HookMgr& operator=(const HookMgr&) = delete;

};

#endif // !__HOOK_H__

#ifndef __PE_HOOK_H__
#define __PE_HOOK_H__

#include <windows.h>
#include <stdio.h>

#define PTR2PTR(ptrInit) *(DWORD*)(*(DWORD*)ptrInit)

#define JE_NEAR_SIZE 6
#define JMP_NEAR_SIZE 5
#define JNZ_NEAR_SIZE 6
#define JGE_NEAR_SIZE 6
#define JG_NEAR_SIZE 6
#define CALL_NEAR_SIZE 5

#define DEF_STR(str, addr) strcpy((CHAR*)addr, (CONST CHAR*)str)

__inline void BuildIndirection(DWORD dwAddress, BYTE* opCode, DWORD opCodeSize, void* dwFuncAddr)
{
	DWORD
		dwOldProtect,
		dwInstructionSize = (opCodeSize + sizeof(DWORD)),
		dwDistance = (((DWORD)dwFuncAddr - dwAddress) - dwInstructionSize);

	BYTE
		* indirection = (BYTE*)malloc(opCodeSize + sizeof(DWORD));

	// Build OpCode Instruction
	fflush(stdin);
	memcpy((BYTE*)&indirection[0], opCode, opCodeSize);

	// Build Distance of Instruction
	memcpy((BYTE*)&indirection[opCodeSize], &dwDistance, sizeof(DWORD));

	// Write Instruction
	VirtualProtect((LPVOID)dwAddress, dwInstructionSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	memcpy((DWORD*)dwAddress, indirection, dwInstructionSize);

	VirtualProtect((LPVOID)dwAddress, dwInstructionSize, dwOldProtect, &dwOldProtect);
}

__inline void FillWithNop(DWORD dwAddress, DWORD dwSize)
{
	DWORD
		dwOldProtect;

	BYTE
		* nop = (BYTE*)malloc(dwSize);

	VirtualProtect((LPVOID)dwAddress, dwSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	for (DWORD i = 0; i < dwSize; i++)
		nop[i] = 0x90;

	memcpy((DWORD*)dwAddress, &nop[0], dwSize);

	VirtualProtect((LPVOID)dwAddress, dwSize, dwOldProtect, &dwOldProtect);
}

__inline void JMP_NEAR(DWORD dwAddress, void* dwFuncAddr)
{
	BYTE
		jmp = 0xE9;

	BuildIndirection(dwAddress, &jmp, 1, dwFuncAddr);
}

__inline void JMP_NEAR(DWORD dwAddress, void* dwFuncAddr, DWORD dwNopedSize)
{
	JMP_NEAR(dwAddress, dwFuncAddr);

	FillWithNop(dwAddress + JMP_NEAR_SIZE, dwNopedSize);
}

__inline void JGE_NEAR(DWORD dwAddress, void* dwFuncAddr)
{
	BYTE
		jge[2] = { 0x0F, 0x8D };

	BuildIndirection(dwAddress, jge, 2, dwFuncAddr);
}

__inline void JGE_NEAR(DWORD dwAddress, void* dwFuncAddr, DWORD dwNopedSize)
{
	JGE_NEAR(dwAddress, dwFuncAddr);

	FillWithNop(dwAddress + JGE_NEAR_SIZE, dwNopedSize);
}


__inline void JG_NEAR(DWORD dwAddress, void* dwFuncAddr)
{
	BYTE
		jg[2] = { 0x0F, 0x8F };

	BuildIndirection(dwAddress, jg, 2, dwFuncAddr);
}

__inline void JG_NEAR(DWORD dwAddress, void* dwFuncAddr, DWORD dwNopedSize)
{
	JGE_NEAR(dwAddress, dwFuncAddr);

	FillWithNop(dwAddress + JG_NEAR_SIZE, dwNopedSize);
}


__inline void JNZ_NEAR(DWORD dwAddress, void* dwFuncAddr)
{
	BYTE
		jnz[2] = { 0x0F, 0x85 };

	BuildIndirection(dwAddress, jnz, 2, dwFuncAddr);
}

__inline void JNZ_NEAR(DWORD dwAddress, void* dwFuncAddr, DWORD dwNopedSize)
{
	JNZ_NEAR(dwAddress, dwFuncAddr);

	FillWithNop(dwAddress + JNZ_NEAR_SIZE, dwNopedSize);
}

__inline void CALL_NEAR(DWORD dwAddress, void* dwFuncAddr)
{
	BYTE
		call = 0xE8;

	BuildIndirection(dwAddress, &call, 1, dwFuncAddr);
}

__inline void CALL_NEAR(DWORD dwAddress, void* dwFuncAddr, DWORD dwNopedSize)
{
	CALL_NEAR(dwAddress, dwFuncAddr);

	FillWithNop(dwAddress + CALL_NEAR_SIZE, dwNopedSize);
}

__inline void JE_NEAR(DWORD dwAddress, void* dwFuncAddr)
{
	BYTE
		je[2] = { 0x0F, 0x84 };

	BuildIndirection(dwAddress, je, 2, dwFuncAddr);
}

__inline void JE_NEAR(DWORD dwAddress, void* dwFuncAddr, DWORD dwNopedSize)
{
	JE_NEAR(dwAddress, dwFuncAddr);

	FillWithNop(dwAddress + JE_NEAR_SIZE, dwNopedSize);
}

#endif // __PE_HOOK_H__
