/*************************************************************************
  Crytek Source File.
  Copyright (C), Crytek Studios, 2001-2004.
 -------------------------------------------------------------------------
  $Id$
  $DateTime$
  
 -------------------------------------------------------------------------
  History:
  - 9:6:2004: Created by Filippo De Luca
  - 15:8:2005: Renamed CDrone to CObserver by Mikko Mononen

*************************************************************************/
#include "CryGame/StdAfx.h"
#include "CryGame/Game.h"
#include "Observer.h"
#include "CryCommon/CryGame/GameUtils.h"

#include "CryCommon/CryAction/IViewSystem.h"
#include "CryCommon/CryAction/IItemSystem.h"
#include "CryCommon/CryPhysics/IPhysics.h"
#include "CryCommon/CryAnimation/ICryAnimation.h"
#include "CryCommon/CryNetwork/ISerialize.h"
#include "CryCommon/CryRenderer/IRenderAuxGeom.h"
