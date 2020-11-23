//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Draws the normal TF2 or HL2 HUD.
//
//=============================================================================
#include "cbase.h"
#include "clientmode_hlnormal.h"
#include "vgui_int.h"
#include "hud.h"
#include <vgui/IInput.h>
#include <vgui/IPanel.h>
#include <vgui/ISurface.h>
#include <vgui_controls/AnimationController.h>
#include "iinput.h"
#include "ienginevgui.h"
#include "firefightreloaded/fr_storemenu.h"
#include "firefightreloaded/fr_storemenu_ammo.h"
#include "firefightreloaded/fr_storemenu_supplies.h"
#include "firefightreloaded/fr_storemenu_weapons.h"
#include "firefightreloaded/fr_moddingmenu.h"
#include "firefightreloaded/fr_moddingmenu_mapping.h"
#include "firefightreloaded/fr_moddingmenu_mapping_mapadd.h"
#include "firefightreloaded/fr_moddingmenu_mapping_noding.h"
#include "firefightreloaded/fr_moddingmenu_weapons.h"
#include "firefightreloaded/ui/frclientscoreboard.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern bool g_bRollingCredits;

ConVar fov_desired( "fov_desired", "75", FCVAR_ARCHIVE | FCVAR_USERINFO, "Sets the base field-of-view.");

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
vgui::HScheme g_hVGuiCombineScheme = 0;


// Instance the singleton and expose the interface to it.
IClientMode *GetClientModeNormal()
{
	static ClientModeHLNormal g_ClientModeNormal;
	return &g_ClientModeNormal;
}


//-----------------------------------------------------------------------------
// Purpose: this is the viewport that contains all the hud elements
//-----------------------------------------------------------------------------
class CHudViewport : public CBaseViewport
{
private:
	DECLARE_CLASS_SIMPLE( CHudViewport, CBaseViewport );

protected:
	virtual void ApplySchemeSettings( vgui::IScheme *pScheme )
	{
		BaseClass::ApplySchemeSettings( pScheme );

		gHUD.InitColors( pScheme );

		SetPaintBackgroundEnabled( false );
	}

	virtual void CreateDefaultPanels( void ) { /* don't create any panels yet*/ };
	virtual IViewPortPanel *CreatePanelByName(const char *szPanelName);
};

IViewPortPanel* CHudViewport::CreatePanelByName(const char *szPanelName)
{
	IViewPortPanel* newpanel = NULL;

	if (Q_strcmp(PANEL_BUY, szPanelName) == 0)
	{
		newpanel = new CFRStoreMenu(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_BUY_WEAPONS, szPanelName) == 0)
	{
		newpanel = new CFRStoreMenuWeapons(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_BUY_SUPPLIES, szPanelName) == 0)
	{
		newpanel = new CFRStoreMenuSupplies(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_BUY_AMMO, szPanelName) == 0)
	{
		newpanel = new CFRStoreMenuAmmo(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_MODDING_MAIN, szPanelName) == 0)
	{
		newpanel = new CFRModdingMenu(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_MODDING_MAPPING, szPanelName) == 0)
	{
		newpanel = new CFRModdingMenu_Mapping(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_MODDING_MAPADD, szPanelName) == 0)
	{
		newpanel = new CFRModdingMenu_Mapping_Mapadd(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_MODDING_NODING, szPanelName) == 0)
	{
		newpanel = new CFRModdingMenu_Mapping_Noding(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_MODDING_WEAPONS, szPanelName) == 0)
	{
		newpanel = new CFRModdingMenu_Weapons(this);
		return newpanel;
	}
	else if (Q_strcmp(PANEL_SCOREBOARD, szPanelName) == 0)
	{
		newpanel = new CFRClientScoreBoardDialog(this);
		return newpanel;
	}

	return BaseClass::CreatePanelByName(szPanelName);
}


//-----------------------------------------------------------------------------
// ClientModeHLNormal implementation
//-----------------------------------------------------------------------------
ClientModeHLNormal::ClientModeHLNormal()
{
	m_pViewport = new CHudViewport();
	m_pViewport->Start( gameuifuncs, gameeventmanager );
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
ClientModeHLNormal::~ClientModeHLNormal()
{
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ClientModeHLNormal::Init()
{
	BaseClass::Init();

	// Load up the combine control panel scheme
	g_hVGuiCombineScheme = vgui::scheme()->LoadSchemeFromFileEx( enginevgui->GetPanel( PANEL_CLIENTDLL ), IsXbox() ? "resource/ClientScheme.res" : "resource/CombinePanelScheme.res", "CombineScheme" );
	if (!g_hVGuiCombineScheme)
	{
		Warning( "Couldn't load combine panel scheme!\n" );
	}
}

bool ClientModeHLNormal::ShouldDrawCrosshair( void )
{
	return ( g_bRollingCredits == false );
}



