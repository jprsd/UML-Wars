/**
 * \file IsPowerAllBadVisitor.cpp
 *
 * \author Reid Shinabarker
 */

#include "pch.h"
#include "IsPowerAllBadVisitor.h"

 /** \brief Visit a CPowerAllBad object
 * \param allbad AllBad power item we are visiting */
void CIsPowerAllBadVisitor::VisitPowerAllBad(CPowerAllBad* allbad)
{
	mIsPowerAllBad = true;
}
