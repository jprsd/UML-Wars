/**
 * \file IsPowerAllGoodVisitor.cpp
 *
 * \author Reid Shinabarker
 */

#include "pch.h"
#include "IsPowerAllGoodVisitor.h"

 /** \brief Visit a CPowerAllGood object
 * \param allgood AllGood power item we are visiting */
void CIsPowerAllGoodVisitor::VisitPowerAllGood(CPowerAllGood* allgood)
{
	mIsPowerAllGood = true;
}
