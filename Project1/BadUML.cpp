/**
 * \file BadUML.cpp
 *
 * \author Jaideep Prasad
 * \author Isaac Mayers
 */

#include "pch.h"
#include "BadUML.h"
#include "Game.h"

using namespace Gdiplus;

/// Display Time
const double OneSecond = 1;

CBadUML::CBadUML(std::shared_ptr<CUMLAttribute> name, 
	std::vector<std::shared_ptr<CUMLAttribute>> attributes, 
	std::vector<std::shared_ptr<CUMLAttribute>> operations,
	std::wstring error, 
	CVector position, CVector velocity, CGame* game) :
	CUML::CUML(name, attributes, operations, position, velocity, game)
{
	mError = error;
}

/**
* Draws Bad UML
* \param graphics Graphics Objects
* \param position Center Position of UML object
*/
void CBadUML::Draw(Gdiplus::Graphics* graphics, CVector position)
{
	CUML::Draw(graphics, position);
	if (mHit)
	{
		if (mTimeDisplayed <= OneSecond)
		{
			RectF size;
			FontFamily fontFamily(L"Arial");
			Gdiplus::Font font(&fontFamily, 20, FontStyleBold);
			PointF origin((REAL)mDisplayLocation.X(), (REAL)mDisplayLocation.Y());
			SolidBrush green(Color(0, 255, 0));
			graphics->MeasureString(GetMessageOnHit().c_str(), -1, &font, origin, &size);
			origin.X -= (REAL)((double)size.Width / 2.0);
			graphics->DrawString(GetMessageOnHit().c_str(), -1, &font, origin, &green);
		}
		else
		{
			mDeleted = true;
		}
	}
}

/**
* Applies the effect of hitting a bad uml
*/
void CBadUML::Effect()
{
	if (!mHit)
	{
		mHit = true;
		CUML::Effect();
		GetGame()->IncrementScore(1);
	}
}
