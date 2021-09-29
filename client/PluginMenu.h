/*
	This is a SampVoice project file
	Developer: CyberMor <cyber.mor.2020@gmail.ru>

	See more here https://github.com/CyberMor/sampvoice

	Copyright (c) Daniel (CyberMor) 2020 All rights reserved
*/

#pragma once

#include <Windows.h>
#include <d3d9.h>

#include <imgui/imgui.h>
#include <util/Memory.hpp>
#include <util/Resource.h>
#include <util/AddressesBase.h>
#include <util/BlurEffect.h>
#include <util/Texture.h>
#include <util/Render.h>

class PluginMenu {
public:

	static constexpr const char* TitleText = "Voice chat postavke";

	static constexpr const char* Tab1_TitleText = "Opcenito";

	static constexpr const char* Tab1_Desc1_TitleText = "Zvuk";
	static constexpr const char* Tab1_Desc1_EnableSoundText = "Ukljuci zvuk";
	static constexpr const char* Tab1_Desc1_VolumeSoundText = "Glasnoca zvuka";

	static constexpr const char* Tab1_Desc2_TitleText = "Efekti";
	static constexpr const char* Tab1_Desc2_BalancerText = "Zagladivanje zvuka";
	static constexpr const char* Tab1_Desc2_FilterText = "Visokopropusni filtar";

	static constexpr const char* Tab1_Desc3_TitleText = "Ikona iznad igraca";
	static constexpr const char* Tab1_Desc3_SpeakerIconScaleText = "Skala";
	static constexpr const char* Tab1_Desc3_SpeakerIconOffsetXText = "X - Pozicija";
	static constexpr const char* Tab1_Desc3_SpeakerIconOffsetYText = "Y - Pozicija";

	static constexpr const char* Tab1_Desc4_TitleText = "Resetiraj";
	static constexpr const char* Tab1_Desc4_ConfigResetText = "Resetiraj sve postavke";

	static constexpr const char* Tab2_TitleText = "Mikrofon";

	static constexpr const char* Tab2_Desc1_TitleText = "Uredaj";
	static constexpr const char* Tab2_Desc1_EnableMicroText = "Uljuci mikrofon";
	static constexpr const char* Tab2_Desc1_MicroVolumeText = "Glasnoca mikrofona";
	static constexpr const char* Tab2_Desc1_DeviceNameText = "Ulazni uredaj";
	static constexpr const char* Tab2_Desc1_CheckDeviceText = "Provjerite svoj uredaj";

	static constexpr const char* Tab2_Desc2_TitleText = "Ikona mikrofona";
	static constexpr const char* Tab2_Desc2_MicroIconScaleText = "Skala";
	static constexpr const char* Tab2_Desc2_MicroIconPositionXText = "X - Pozicija";
	static constexpr const char* Tab2_Desc2_MicroIconPositionYText = "Y - Pozicija";
	static constexpr const char* Tab2_Desc2_MicroIconMoveText = "Odaberi lokaciju";

	static constexpr const char* Tab2_Desc3_MicroNotFoundText = "Nema dostupnih mikrofona";

	static constexpr const char* Tab3_TitleText = "Block lista";

	static constexpr const char* Tab3_Desc1_TitleText = "Filtar";
	static constexpr const char* Tab3_Desc1_InputPlaceholderText = "Unesite igracev ID ili nick";

	static constexpr const char* Tab3_Desc2_PlayerListText = "Igraci na serveru";

	static constexpr const char* Tab3_Desc3_BlackListText = "Blokirani igraci";

	static constexpr float	BaseMenuWidth = 0.6f * Render::BaseWidth;
	static constexpr float	BaseMenuHeight = 0.7f * Render::BaseHeight;

	static constexpr float	BaseMenuPaddingX = 20.f;
	static constexpr float	BaseMenuPaddingY = 10.f;
	static constexpr float	BaseMenuFramePaddingX = 10.f;
	static constexpr float	BaseMenuFramePaddingY = 0.5f;

	static constexpr float	BaseMenuItemSpacingX = 20.f;
	static constexpr float	BaseMenuItemSpacingY = 2.f;
	static constexpr float	BaseMenuItemInnerSpacingX = 10.f;
	static constexpr float	BaseMenuItemInnerSpacingY = 10.f;

	static constexpr float	BaseMenuRounding = 10.f;

	static constexpr float	BaseFontTitleSize = 20.f;
	static constexpr float	BaseFontTabSize = 14.f;
	static constexpr float	BaseFontDescSize = 12.f;
	static constexpr float	BaseFontSize = 10.f;

	static constexpr int	TabsCount = 3;
	static constexpr float	BaseTabPadding = 4.f;
	static constexpr float	BaseTabWidth = (BaseMenuWidth - (2 * BaseMenuPaddingX + (TabsCount - 1) * BaseTabPadding)) / TabsCount;
	static constexpr float	BaseTabHeight = BaseTabWidth / 6.f;

	static constexpr float	BlurLevelIncrement = 5.f;
	static constexpr float	BlurLevelDecrement = -5.f;

private:

	static bool initStatus;
	static bool showStatus;

	static float blurLevel;
	static float blurLevelDeviation;
	static BlurEffectPtr blurEffect;

	static TexturePtr tLogo;

	static ImFont* pTitleFont;
	static ImFont* pTabFont;
	static ImFont* pDescFont;
	static ImFont* pDefFont;

	static Memory::PatchPtr openChatFuncPatch;
	static Memory::PatchPtr openScoreboardFuncPatch;
	static Memory::PatchPtr switchModeFuncPatch;

	static int prevChatMode;

	// Configs
	// ------------------------------------------------------------------------------------------

	static bool soundEnable;
	static int soundVolume;
	static bool soundBalancer;
	static bool soundFilter;

	static float speakerIconScale;
	static int speakerIconOffsetX;
	static int speakerIconOffsetY;

	static bool microEnable;
	static int microVolume;
	static int deviceIndex;

	static float microIconScale;
	static int microIconPositionX;
	static int microIconPositionY;
	static D3DCOLOR microIconColor;
	static float microIconAngle;

	// Internal options
	// ------------------------------------------------------------------------------------------

	static int iSelectedMenu;
	static bool bCheckDevice;
	static bool bMicroMovement;
	static char nBuffer[64];

	// ------------------------------------------------------------------------------------------

	static void SyncOptions();

public:

	static bool Init(
		IDirect3DDevice9* pDevice,
		D3DPRESENT_PARAMETERS* pParameters,
		const AddressesBase& addrBase,
		const Resource& rShader,
		const Resource& rLogo,
		const Resource& rFont
	);

	static void Render();
	static void Update();

	static bool Show();
	static bool IsShowed();
	static void Hide();

	static LRESULT OnWndMessage(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam
	);

	static void Free();

};
