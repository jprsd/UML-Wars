/**
 * \file IsPowerFastVisitor.cpp
 *
 * \author Reid Shinabarker
 */

#include "pch.h"
#include "PowerFast.h"
#include "IsPowerFastVisitor.h"

 /** \brief Visit a CPowerFast object
 * \param fast Fast power item we are visiting */
void CIsPowerFastVisitor::VisitPowerFast(CPowerFast* fast)
{
	mIsPowerFast = true;
	mIsActive = fast->IsActive();
}
