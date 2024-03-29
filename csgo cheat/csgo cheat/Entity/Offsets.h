#include "../Utils/Memory/Memory.h"
#include <Windows.h>

namespace Offset
{
	
	


	struct
	{
		DWORD Health = 0x32C;
		DWORD TeamID = 0x3BF;
		DWORD IsAlive = 0x7F4;
		DWORD PlayerPawn = 0x7EC;
		DWORD iszPlayerName = 0x640;
		DWORD EnemySensor = 0x13E4;
		DWORD GravityScale = 0x434;
	}Entity;

	struct
	{
		DWORD BulletServices = 0x16B8;
		DWORD TotalHit = 0x40;
		DWORD Pos = 0x1224;	// m_vOldOrigin
		DWORD MaxHealth = 0x328;
		DWORD CurrentHealth = 0x32C; // m_iHealth
		DWORD GameSceneNode = 0x310;
		DWORD BoneArray = 0x1E0;
		DWORD angEyeAngles = 0x1518;
		DWORD vecLastClipCameraPos = 0x1294;
		DWORD pClippingWeapon = 0x12B0;
		DWORD iShotsFired = 0x1420;
		DWORD flFlashDuration = 0x1470;
		DWORD aimPunchAngle = 0x171C;
		DWORD aimPunchCache = 0x1740;
		DWORD iIDEntIndex = 0x1544;
		DWORD iTeamNum = 0x3BF;
		DWORD CameraServices = 0x10E0; // m_pCameraServices
		DWORD iFovStart = 0x214;
		DWORD fFlags = 0x3C8;
		DWORD bSpottedByMask = 0x1638 + 0xC; // entitySpottedState + bSpottedByMask
	} Pawn;

	struct
	{
		DWORD RealTime = 0x00;
		DWORD FrameCount = 0x04;
		DWORD MaxClients = 0x10;
		DWORD IntervalPerTick = 0x14;
		DWORD CurrentTime = 0x2C;
		DWORD CurrentTime2 = 0x30;
		DWORD TickCount = 0x40;
		DWORD IntervalPerTick2 = 0x44;
		DWORD CurrentNetchan = 0x0048;
		DWORD CurrentMap = 0x0180;
		DWORD CurrentMapName = 0x0188;
	} GlobalVar;

	struct
	{
		DWORD m_hPawn = 0x60C;
		DWORD m_pObserverServices = 0x10C0;
		DWORD m_hObserverTarget = 0x44;
		DWORD m_hController = 0x123C;
	} PlayerController;

	struct
	{
		DWORD m_szName = 0xC18;
	} WeaponBaseData;

	struct
	{
		DWORD m_bBeingDefused = 0xEBC;
		DWORD m_flDefuseCountDown = 0xED0;
		DWORD m_nBombSite = 0xE84;
	} C4;

	struct // C_BaseCSGrenadeProjectile
	{
		DWORD nSmokeEffectTickBegin = 0x1108; // int32_t
		DWORD bDidSmokeEffect = 0x110C; // bool
		DWORD nRandomSeed = 0x1110; // int32_t
		DWORD vSmokeColor = 0x1114; // Vector
		DWORD vSmokeDetonationPos = 0x1120; // Vector
		DWORD VoxelFrameData = 0x1130; // CUtlVector<uint8_t>
		DWORD bSmokeVolumeDataReceived = 0x1148; // bool
		uintptr_t bSmokeEffectSpawned = 0x1149; // bool
	} SmokeGrenadeProjectile;

	

	
}
