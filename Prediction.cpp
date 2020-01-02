#include "Prediction.h"

static char* cMoveData = nullptr;

void CPredictionSystem::EnginePrediction(CUserCmd* pCmd)
{
	if (!G_MoveHelper || !pCmd || !g_Globals->local)
		return;

	CMoveData C_MoveData;

	//Let's back things up for later use
	iFlagsBackup = *g_Globals->local->GetFlags();
	iButtonsBackup = pCmd->buttons;

	//Set m_pCurrentCommand to cmd. We'll set this to nullptr later.
	g_Globals->local->SetCurrentCommand(pCmd);

	//Let's get some signatures now
	if (!m_pPredictionRandomSeed || !m_pSetPredictionPlayer)
	{
		m_pPredictionRandomSeed = *reinterpret_cast<int**>(FindPatternIDA((client_dll), "A3 ? ? ? ? 66 0F 6E 86") + 1);
		m_pSetPredictionPlayer = *reinterpret_cast<int**>(FindPatternIDA((client_dll), "89 35 ? ? ? ? F3 0F 10 48 20") + 2);
	}

	//We don't want to be calling this every tick, bad for framerate.
	//Thanks, zbe and Heep
	if (!cMoveData)
		cMoveData = (char*)(calloc(1, sizeof(CMoveData)));

	//Let's set it up so that it predicts ourselves
	G_MoveHelper->SetHost(g_Globals->local);
	*m_pPredictionRandomSeed = MD5_PseudoRandom(pCmd->command_number) & 0x7FFFFFFF;
	*m_pSetPredictionPlayer = uintptr_t(g_Globals->local);

	//Let's set some global variables
	G_Globals->curtime = g_Globals->local->GetTickBase() * G_Globals->intervalPerTick;
	G_Globals->frametime = G_Globals->intervalPerTick;


	pCmd->buttons |= *reinterpret_cast< uint8_t* >(uintptr_t(g_Globals->local) + 0x3310);

	//This is for flashlights in older Source games, Thanks, friendly for the info
	if (pCmd->impulse)
		*reinterpret_cast< uint8_t* >(uintptr_t(g_Globals->local) + 0x31EC) = pCmd->impulse;

	//Here we're doing CBasePlayer::UpdateButtonState
	C_MoveData.m_nButtons = pCmd->buttons;
	int buttonsChanged = pCmd->buttons ^ *reinterpret_cast<int*>(uintptr_t(g_Globals->local) + 0x31E8);
	*reinterpret_cast<int*>(uintptr_t(g_Globals->local) + 0x31DC) = (uintptr_t(g_Globals->local) + 0x31E8);
	*reinterpret_cast<int*>(uintptr_t(g_Globals->local) + 0x31E8) = pCmd->buttons;
	*reinterpret_cast<int*>(uintptr_t(g_Globals->local) + 0x31E0) = pCmd->buttons & buttonsChanged;  //m_afButtonPressed ~ The changed ones still down are "pressed"
	*reinterpret_cast<int*>(uintptr_t(g_Globals->local) + 0x31E4) = buttonsChanged & ~pCmd->buttons; //m_afButtonReleased ~ The ones not down are "released"

	G_Movement->StartTrackPredictionErrors(g_Globals->local);

	iTickBaseBackup = g_Globals->local->GetTickBase();

	G_Prediction->SetupMove(g_Globals->local, pCmd, G_MoveHelper, reinterpret_cast< CMoveData* >(cMoveData));
	G_Movement->ProcessMovement(g_Globals->local, reinterpret_cast< CMoveData* >(cMoveData));
	G_Prediction->FinishMove(g_Globals->local, pCmd, reinterpret_cast< CMoveData* >(cMoveData));

	//Let's override our tickbase with the backed up tickbase
	g_Globals->local->GetTickBase() = iTickBaseBackup;

	G_Movement->FinishTrackPredictionErrors(g_Globals->local);

	//Let's nullify these here
	g_Globals->local->SetCurrentCommand(nullptr);
	*m_pPredictionRandomSeed = -1;
	*m_pSetPredictionPlayer = 0;
	G_MoveHelper->SetHost(0);

	//Last but not least, set these to their backups 
	*g_Globals->local->GetFlags() = iFlagsBackup;
	pCmd->buttons = iButtonsBackup;
}