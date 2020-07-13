/**
 * \file MakePenActiveVisitor.cpp
 *
 * \author team Sarson
 */

#include "pch.h"
#include "MakePenActiveVisitor.h"

using namespace std;

/**
 * Unattaches the pen and starts its movement
 * \param HaroldPen Pen being used
 */
void CMakePenActiveVisitor::VisitHaroldPen(CHaroldPen* HaroldPen)
{
	HaroldPen->UnAttach();
	HaroldPen->SetVelocity(CVector(1000.0f * sin(mAngle), -1000.5f * cos(mAngle)));
}
