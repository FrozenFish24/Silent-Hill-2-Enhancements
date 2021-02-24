#pragma once

typedef enum _SH2VERSION {
	SH2V_UNKNOWN = 0,
	SH2V_10 = 1,
	SH2V_11 = 2,
	SH2V_DC = 3,
} SH2VERSION;

// Shared function declaration
DWORD GetRoomID();
DWORD GetCutsceneID();
float GetCutscenePos();
float GetJamesPosX();
float GetJamesPosY();
float GetJamesPosZ();
BYTE GetFlashLightRender();
BYTE GetChapterID();
DWORD GetSpecializedLight1();
DWORD GetSpecializedLight2();
BYTE GetFlashlightSwitch();
float GetFlashlightBrightnessRed();
float GetFlashlightBrightnessGreen();
float GetFlashlightBrightnessBlue();
DWORD GetOnScreen();
BYTE GetEventIndex();
BYTE GetMenuEvent();
DWORD GetTransitionState();
BYTE GetFullscreenImageEvent();
float GetInGameCameraPosY();
BYTE GetInventoryStatus();
DWORD GetLoadingScreen();

// Shared pointer function declaration
DWORD *GetRoomIDPointer();
DWORD *GetCutsceneIDPointer();
float *GetCutscenePosPointer();
float *GetJamesPosXPointer();
float *GetJamesPosYPointer();
float *GetJamesPosZPointer();
BYTE *GetFlashLightRenderPointer();
BYTE *GetChapterIDPointer();
DWORD *GetSpecializedLight1Pointer();
DWORD *GetSpecializedLight2Pointer();
BYTE *GetFlashlightSwitchPointer();
float *GetFlashlightBrightnessPointer();
DWORD *GetOnScreenPointer();
BYTE *GetEventIndexPointer();
BYTE *GetMenuEventPointer();
DWORD *GetTransitionStatePointer();
BYTE *GetFullscreenImageEventPointer();
float *GetInGameCameraPosYPointer();
BYTE *GetInventoryStatusPointer();
DWORD *GetLoadingScreenPointer();

// Function patch declaration
void CheckArgumentsForPID();
void RelaunchSilentHill2();
void CheckAdminAccess();
void RemoveVirtualStoreFiles();
void RemoveCompatibilityMode();
void SetDelayedStart();
void SetFullscreenImagesRes(DWORD Width, DWORD Height);
void SetResolutionList(DWORD Width, DWORD Height);
void SetResolutionPatch();
void SetRoom312Resolution(void *WidthAddress);
void SetWindowHandle(HWND WindowHandle);
void UnhookWindowHandle();
void ValidateBinary();

void Patch2TBHardDrive();
void PatchBestGraphics();
void PatchBinary();
void PatchCDCheck();
void PatchCatacombsMeatRoom();
void PatchCreatureVehicleSpawn();
HRESULT PatchCustomExeStr();
void PatchCustomFog();
void PatchCustomFonts();
void PatchControllerTweaks();
void PatchDrawDistance();
void PatchFlashlightClockPush();
void PatchFlashlightFlicker();
void PatchFogParameters();
void PatchFullscreenImages();
void PatchLockScreenPosition();
void PatchMainMenu();
void PatchMainMenuTitlePerLang();
void PatchPauseScreen();
void PatchPistonRoom();
void PatchPreventChainsawSpawn();
void PatchPS2Flashlight();
void PatchPS2NoiseFilter();
void PatchRedCrossInCutscene();
void PatchRoom312ShadowFix();
void PatchRoomLighting();
void PatchRowboatAnimation();
void PatchSaveBGImage();
void PatchSpeakerConfigLock();
void PatchSpecialFX();
void PatchSFXAddr();
void PatchTexAddr();
void PatchTownWestGateEvent();
void PatchTreeLighting();
void PatchXInputVibration();

void RunBloodSize();
void RunClosetCutscene();
void RunDynamicDrawDistance();
void RunFlashlightClockPush();
void RunFogSpeed();
void RunGameLoad();
void RunHangOnEsc();
void RunHospitalChase();
void RunHotelRoom312FogVolumeFix();
void RunHotelWater();
void RunInfiniteRumbleFix();
void RunInnerFlashlightGlow(DWORD Height);
void RunLightingTransition();
void RunRoomLighting();
void RunRotatingMannequin();
void RunSaveBGImage();
void RunShadowCutscene();
void RunSpecialFXScale(DWORD Height);
void RunTreeColor();

// Variable forward declaration
extern SH2VERSION GameVersion;
extern bool IsInFullscreenImage;
extern bool IsInBloomEffect;
extern bool IsInFakeFadeout;
extern DWORD *RoomIDAddr;
extern DWORD *CutsceneIDAddr;
extern float *CutscenePosAddr;
extern float *JamesPosXAddr;
extern float *JamesPosYAddr;
extern float *JamesPosZAddr;
extern BYTE *FlashLightRenderAddr;
extern BYTE *ChapterIDAddr;
extern DWORD *SpecializedLight1Addr;
extern DWORD *SpecializedLight2Addr;
extern BYTE *FlashlightSwitchAddr;
extern float *FlashlightBrightnessAddr;
extern DWORD *OnScreenAddr;				/* 0 = load screen
										4 = normal in-game
										5 = maps
										6 = inventory screen
										9 = save screen */

extern BYTE *EventIndexAddr;			/*1 = reload/re-enter into current room
										2 = main menu
										4 = in-game
										5 = map
										6 = inventory
										7 = options menu
										8 = bugged Xbox button config menu
										9 = save menu
										10/11 = pull up Game Results file
										12 = "COMING SOON!" splash screen
										13 = game over screen
										16 = PC pause menu*/

extern BYTE *MenuEventAddr;				/* 7 = main menu event index */

extern DWORD *TransitionStateAddr;		/* 1 = fades the game image to black
										2 = solid black screen
										3 = fades from black back to the in game screen */

extern BYTE *FullscreenImageEventAddr;
extern float *InGameCameraPosYAddr;
extern BYTE *InventoryStatusAddr;
extern DWORD *LoadingScreenAddr;

// Run code only once
#define RUNONCE() \
	{ \
		static bool RunOnce = true; \
		if (!RunOnce) \
		{ \
			return; \
		} \
		RunOnce = false; \
	} \

#define RUNCODEONCE(funct) \
	{ \
		static bool RunFixOnce = true; \
		if (RunFixOnce) \
		{ \
			funct; \
		} \
		RunFixOnce = false; \
	} \
