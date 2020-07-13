 /*
* File : UML.cpp
*
* author : Isaac Mayers
*
*/
#include "pch.h"
#include "UML.h"

using namespace Gdiplus;

CUML::CUML(std::shared_ptr<CUMLAttribute> name, 
	std::vector<std::shared_ptr<CUMLAttribute> > attributes, 
	std::vector<std::shared_ptr<CUMLAttribute> > operations, 
	CVector position, CVector velocity, CGame* game) :
	CItem(position, velocity, game) {
	mName = name;
	mAttributes = attributes;
	mOperations = operations;


}
/** Updates time elapsed for UML object
* \param elapsedTime Real Elapsed Time
*/

void CUML::Update(double elapsedTime)
{
	CItem::Update(elapsedTime);
	if (mHit && !mDeleted)
	{
		mTimeDisplayed += elapsedTime;
	}
}

/** Draws uml items
* \param graphics Graphics Object
* \param position Center position of UML object
*/
void CUML::Draw(Graphics* graphics, CVector position) 
{
	// Determine the box dimesions based on number of attributes and operations
	Pen pen(Color(0, 0, 0), 3);
	RectF size;
	SolidBrush black(Color(0, 0, 0));
	PointF origin(0.0f, 0.0f);
	double textHeight = 0;
	double textWidth = 0;
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font namefont(&fontFamily, 20, FontStyleBold, UnitPixel);
	Gdiplus::Font font(&fontFamily, 16, FontStyleRegular, UnitPixel);
	graphics->MeasureString(mName->GetAtt().c_str(), -1, &namefont, origin, &size);
	textHeight = (double)size.Height + 6;
	textWidth = (double)size.Width;
	for (auto att : mAttributes) 
	{
		graphics->MeasureString(att->GetAtt().c_str(), -1, &font, origin, &size);
		
			textHeight += (double)size.Height;
		
		if ((double)size.Width > textWidth) 
		{
			textWidth = (double)size.Width;
		}
	}
	if (mOperations.size() > 0)
	{
		textHeight += 3;
	}
	for (auto op : mOperations) 
	{
		graphics->MeasureString(op->GetAtt().c_str(), -1, &font, origin, &size);

		textHeight += (double)size.Height;

		if ((double)size.Width > textWidth) 
		{
			textWidth = (double)size.Width;
		}

	}
	SolidBrush sb(Gdiplus::Color(255, 255, 193));
	Rect box((int)(position.X() - textWidth / 2), (int)(position.Y() - textHeight / 2), (int)textWidth, (int)textHeight);
	
	if (mWidth < 0 || mHeight < 0)
	{
		mWidth = box.Width;
		mHeight = box.Height;
	}
	//draw box
	graphics->FillRectangle(&sb, box );
	PointF strloc((REAL)position.X(), (REAL)position.Y());
	strloc.Y -= (REAL)(textHeight / 2);
	graphics->MeasureString(mName->GetAtt().c_str(), -1, &namefont, strloc, &size);
	//if Name is longer or equal to box width print Name on left side of box
	if (box.Width <= (double)size.Width) 
	{
		strloc.X -= box.Width / 2;
	}
	else
	{
		strloc.X -= (REAL)((double)size.Width / 2.0);
	}
	//Draw Name
	graphics->DrawString(mName->GetAtt().c_str(), -1, &namefont, strloc, &black);
	if (box.Width > (double)size.Width)
	{
		strloc.X += (REAL)((double)size.Width / 2.0);
		strloc.X -= box.Width / 2;
	}
	strloc.Y += (REAL)((double)size.Height + 3);
	graphics->DrawLine(&pen, strloc.X, strloc.Y, (REAL)(strloc.X + textWidth), strloc.Y);
	strloc.Y += 3;
	for (auto att : mAttributes) 
	{
		graphics->MeasureString(att->GetAtt().c_str(), -1, &font, strloc, &size);
		//Draw Attributes
		graphics->DrawString(att->GetAtt().c_str(), -1, &font, strloc, &black);
		strloc.Y += (REAL)((double)size.Height);
	}
	if (mOperations.size() > 0 && mAttributes.size() > 0)
	{
		strloc.Y += 3;
		graphics->DrawLine(&pen, strloc.X, strloc.Y, (REAL)(strloc.X + textWidth), strloc.Y);
	}
	for (auto op : mOperations) 
	{
		graphics->MeasureString(op->GetAtt().c_str(), -1, &font, strloc, &size);
		//Draw Operations
		graphics->DrawString(op->GetAtt().c_str(), -1, &font, strloc, &black);
		strloc.Y += (REAL)((double)size.Height);
	}
}

