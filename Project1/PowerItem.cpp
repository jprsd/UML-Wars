/**
 * \file PowerItem.cpp
 *
 * \author Isaac Mayers
 * \author Jaideep Prasad
 */

#include "pch.h"
#include <string>
#include <memory>
#include "PowerItem.h"

using namespace std;
using namespace Gdiplus;

/**
 * \brief Constructor for CPowerItem class
 *
 * \param position takes in a position in the form of a CVector
 * \param velocity takes in a velocity in the form of a CVector
 * \param game takes in the game pointer
 * \param PowerItemImageName takes the image name of the power item as a string
 */
CPowerItem::CPowerItem(CVector position, CVector velocity, CGame* game, std::wstring PowerItemImageName) :
	CItem(position, velocity, game)
{
	mPowerItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(PowerItemImageName.c_str()));
	if (mPowerItemImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += PowerItemImageName;
		AfxMessageBox(msg.c_str());
	}
}

/** Draw power item
* \param graphics Gdiplus graphics to draw
* \param position Position to draw
*/
void CPowerItem::Draw(Gdiplus::Graphics* graphics, CVector position)
{
	float wid = (float)mPowerItemImage->GetWidth();
	float hit = (float)mPowerItemImage->GetHeight();

	auto state = graphics->Save();
	graphics->TranslateTransform((float)position.X(), (float)position.Y());
	graphics->DrawImage(mPowerItemImage.get(), -wid / 2, -hit / 2,
		wid, hit);
	graphics->Restore(state);
}

/** Update Image
* \param elapsedTime Time since last update
*/
void CPowerItem::Update(double elapsedTime)
{
	CItem::Update(elapsedTime);
}