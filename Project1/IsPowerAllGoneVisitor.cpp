/**
 * \file IsPowerAllGoneVisitor.cpp
 *
 * \author Reid Shinabarker
 */

#include "pch.h"
#include "IsPowerAllGoneVisitor.h"

 /** \brief Visit a CPowerAllGone object
 * \param allgone AllGone power item we are visiting */
void CIsPowerAllGoneVisitor::VisitPowerAllGone(CPowerAllGone* allgone)
{
	mIsPowerAllGone = true;
}
