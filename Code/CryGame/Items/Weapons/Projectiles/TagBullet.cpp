// -------------------------------------------------------------------------
// Crytek Source File.
// Copyright (C) Crytek GmbH, 2001-2008.
// -------------------------------------------------------------------------
#include "CryGame/StdAfx.h"
#include "TagBullet.h"
#include "CryGame/Game.h"
#include "CryGame/GameRules.h"
#include "CryGame/HUD/HUD.h"
#include "CryCommon/CryEntitySystem/IEntitySystem.h"

CTagBullet::CTagBullet(void)
{
}

CTagBullet::~CTagBullet(void)
{
}

void CTagBullet::HandleEvent(const SGameObjectEvent &event)
{
	if (m_destroying)
		return;

	CProjectile::HandleEvent(event);

	if (event.event == eGFE_OnCollision)
	{
		EventPhysCollision *pCollision = reinterpret_cast<EventPhysCollision *>(event.ptr);
		if (!pCollision)
			return;

		IEntity *pTarget = pCollision->iForeignData[1]==PHYS_FOREIGN_ID_ENTITY ? (IEntity*)pCollision->pForeignData[1]:0;
		if (pTarget)
		{
			EntityId targetId = pTarget->GetId();

			SimpleHitInfo info(m_ownerId, targetId, m_weaponId, 0); // 0=tag,1=tac
			info.remote=IsRemote();

			g_pGame->GetGameRules()->ClientSimpleHit(info);
		}

		Destroy();
	}
}
