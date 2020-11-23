//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef NPC_COMBINEE_H
#define NPC_COMBINEE_H
#ifdef _WIN32
#pragma once
#endif

#include "npc_combine.h"

//#include <vector>
//#include <iostream>

//ported bot funcs
#define SKILL_SHORT_RANGE 150.0f
#define SKILL_MID_RANGE 350.0f
#define SKILL_MAX_RANGE FLT_MAX

//=========================================================
//	>> CNPC_CombineS
//=========================================================
class CNPC_Player : public CNPC_Combine
{
	DECLARE_CLASS( CNPC_Player, CNPC_Combine );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

public: 

	CNPC_Player();
	~CNPC_Player(void);
	void		Spawn( void );
	void		Precache( void );
	void		GiveWeapon(const char* iszWeaponName);
	void		DeathSound( const CTakeDamageInfo &info );
	void		NPCThink( void );
	//ported bot funcs
	float		BotWeaponRangeDetermine(CBaseCombatWeapon* pActiveWeapon);
	CBaseCombatWeapon* GetNextBestWeaponBot(CBaseCombatWeapon* pCurrentWeapon);
	bool		SwitchToNextBestWeaponBot(CBaseCombatWeapon* pCurrent);
	//player emulation
	bool		Weapon_Switch(CBaseCombatWeapon* pWeapon);
	void		GiveWeapons(void);
	//void		GiveRandomModel(void);
	float		GetSequenceGroundSpeed(CStudioHdr* pStudioHdr, int iSequence);
	void		BuildScheduleTestBits( void );
	int			SelectSchedule ( void );
	float		GetHitgroupDamageMultiplier( int iHitGroup, const CTakeDamageInfo &info );
	void		Event_Killed( const CTakeDamageInfo &info );
	void		OnListened();
	Class_T		Classify(void);
	Activity	NPC_TranslateActivity(Activity eNewActivity);

	void		ClearAttackConditions( void );

	bool		IsLightDamage( const CTakeDamageInfo &info );
	bool		IsHeavyDamage( const CTakeDamageInfo &info );
	//std::vector<const char*>	AvailableModels;

private:
	float		m_flSoonestWeaponSwitch;
	/*
	int			nModelRandomRetries;
	int			nModelRandomMaxRetries = 10;
	*/
};

#endif // NPC_COMBINES_H
