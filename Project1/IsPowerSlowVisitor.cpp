/**
 * \file IsPowerSlowVisitor.cpp
 *
 * \author Reid Shinabarker
 */

#include "pch.h"
#include "PowerSlow.h"
#include "IsPowerSlowVisitor.h"

 /** \brief Visit a CPowerSlow object
 * \param slow Slow power item we are visiting */
void CIsPowerSlowVisitor::VisitPowerSlow(CPowerSlow* slow)
{
	mIsPowerSlow = true;
	mIsActive = slow->IsActive();
}
