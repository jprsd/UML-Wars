/**
 * \file IsHaroldPenVisitor.h
 *
 * \author David Hefty
 *
 * Item visitor to determine if an Item is a HaroldPen
 */

#pragma once
#include "ItemVisitor.h"
#include "HaroldPen.h"

 /** visitor class for makeing a pen item active */
class CMakePenActiveVisitor :
	public CItemVisitor
{
public:
	/// Constructor
	/// \param angle Angle to shoot the pen at
	CMakePenActiveVisitor(double angle) : mAngle(angle)
	{}

	virtual void VisitHaroldPen(CHaroldPen* HaroldPen) override;

private:
	/// angle to shoot the pen at
	double mAngle;
};


