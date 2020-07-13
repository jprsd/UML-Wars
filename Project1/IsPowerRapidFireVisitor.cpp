/**
 * \file IsPowerRapidFireVisitor.cpp
 *
 * \author Reid Shinabarker
 */

#include "pch.h"
#include "PowerRapidFire.h"
#include "IsPowerRapidFireVisitor.h"

 /** \brief Visit a CPowerRapidFire object
 * \param rapidfire RapidFire power item we are visiting */
void CIsPowerRapidFireVisitor::VisitPowerRapidFire(CPowerRapidFire* rapidfire)
{
	mIsPowerRapidFire = true;
	mIsActive = rapidfire->IsActive();
}
