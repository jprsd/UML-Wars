/**
 * \file IsPowerItemVisitor.cpp
 *
 * \author Isaac Mayers
 */

#include "pch.h"
#include "IsPowerItemVisitor.h"

 /** \brief Visit a CPowerItem object
 * \param poweritem Power item we are visiting */
 void CIsPowerItemVisitor::VisitPowerItem(CPowerItem* poweritem)
 {
 	mIsPowerItem = true;
 }
