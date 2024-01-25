#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <string_view>
#include <thread>
#include <vector>
#include <atlconv.h>

class Memory
{
private:
	char TargetName[20] = "Counter-Strike 2";
	HWND TargetHwnd;
public:
	DWORD PID;
	uint64_t Client_DLL;
	uint64_t Server_DLL;
	HANDLE pHandle;

	bool Init();
	uintptr_t GetModuleBase(const std::string moduleName);


	template <typename ReadType>

	bool ReadMemory(DWORD64 Address, ReadType& Value, int Size)
	{


		if (ReadProcessMemory(pHandle, reinterpret_cast<LPCVOID>(Address), &Value, Size, 0))
			return true;
		return false;
	}

	template <typename ReadType>
	bool ReadMemory(DWORD64 Address, ReadType& Value)
	{


		if (ReadProcessMemory(pHandle, reinterpret_cast<LPCVOID>(Address), &Value, sizeof(ReadType), 0))
			return true;
		return false;
	}
	template <typename ReadType>

	bool WriteMemory(DWORD64 Address, ReadType& Value, int Size)
	{


		if (WriteProcessMemory(pHandle, reinterpret_cast<LPCVOID>(Address), &Value, Size, 0))
			return true;
		return false;
	}

	template <typename ReadType>
	bool WriteMemory(DWORD64 Address, ReadType& Value)
	{


		if (WriteProcessMemory(pHandle, reinterpret_cast<LPVOID>(Address), &Value, sizeof(ReadType), 0))
			return true;
		return false;
	}

	
};
inline Memory m;
