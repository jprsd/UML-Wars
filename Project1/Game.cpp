/**
 * \file Game.cpp
 *
 * \author Akhil Alluri
 * \author Jaideep Prasad
 * \author Isaac Mayers
 */

#include "pch.h"
#include <memory>
#include <vector>
#include "Game.h"
#include "Item.h"
#include "XmlNode.h"
#include "HaroldPen.h"
#include "MakePenActiveVisitor.h"
#include "IsHaroldPenVisitor.h"
#include "PowerAllBad.h"
#include "PowerAllGood.h"
#include "PowerAllGone.h"
#include "PowerRapidFire.h"
#include "IsHaroldPenVisitor.h"
#include "IsUMLItemVisitor.h"
#include "IsBadUMLVisitor.h"
#include "HaroldPen.h"
#include "UML.h"


using namespace Gdiplus;
using namespace std;
using namespace xmlnode;

/// Half Pi radians
const double AngleOffset = 3.14159 / 2.0;

/// Pen position value to ensure proper position on screen
const double PenOffset1 = 61.29437;

/// Pen position value to ensure proper position on screen
const double PenOffset2 = 1000.0;

/// Pen position value to ensure proper position on screen
const double PenOffset3 = 95.0;


/// Pen angle offset value to ensure proper position on screen
const double PenAngleOffset = (3.1415926535f) * 3 / 4;

///	2 seconds in seconds
const double TwoSeconds = 2.0;


/**
* Draw the game area
* \param graphics The GDI+ graphics context to draw on
* \param width Width of the client window
* \param height Height of the client window
*/
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height) {
	// Fill the background with black
	SolidBrush brush(Color::White);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = width / 2.0f;
	mYOffset = 0;
	if (height > Height * mScale) {
		mYOffset = (float)((height - Height * mScale) / 2);
	}

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	
	for (auto item : mItems) {
		item->Draw(graphics, item->GetPosition());
	}

	// From here on you are drawing virtual pixels
	mPlayer.Draw(graphics, 0, Height);

	// ScoreBoard must ALWAYS be drawn last (on top of everything)
	mScoreBoard.Draw(graphics);


}

/**
 * Fire the player's pen when mouse left is pressed
 * \param x Mouse point x location
 * \param y Mouse point y location
 */
void CGame::OnLButtonDown(double x, double y)
{
	// First convert screen pixels to virutal pixels
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;
	
	// pen firing

	// Determine and set the new angle
	double angle = (atan2(Height - oY, oX) - AngleOffset);

	shared_ptr<CItem> currentPen;
	CMakePenActiveVisitor changer(-angle);
	CIsHaroldPenVisitor visitPen;
	for (auto item : mItems)
	{
		item->Accept(&visitPen);
		if (visitPen.IsHaroldPen() && visitPen.IsAttached())
		{
			item->Accept(&changer);
			visitPen.Reset();
			break;
		}

	}
	
	
}

/**
 * Updates game status
 * \param elapsedTime Time since last game tick
 */
void CGame::Update(double elapsedTime)
{
	CIsHaroldPenVisitor visitPen;
	CIsUMLItemVisitor umlVisitor;

	CVector penPosition;
	CVector penDimensions;

	CVector itemPosition;
	CVector itemDimensions;

	vector<shared_ptr<CItem> > outOfBounds;
	vector<shared_ptr<CItem> > deletedUMLs;

	for (auto item : mItems)
	{
		item->Accept(&umlVisitor);
		if (umlVisitor.IsUML() && umlVisitor.IsDelted())
		{
			deletedUMLs.push_back(item);
		}
		umlVisitor.Reset();
	}

	for (auto uml : deletedUMLs)
	{
		RemoveItem(uml);
	}

	for (auto item : mItems)
	{
		item->Update(elapsedTime);
		item->Accept(&visitPen);
		item->Accept(&umlVisitor);

		itemPosition = item->GetPosition();
		itemDimensions = item->GetDimensions();

		if (itemPosition.X() - itemDimensions.X() > Width / 2.0 ||
			itemPosition.X() + itemDimensions.X() < -Width / 2.0 ||
			itemPosition.Y() - itemDimensions.Y() > Height)
		{
			if (umlVisitor.IsUML())
			{
				outOfBounds.push_back(item);
			}
			else if (!visitPen.IsHaroldPen())
			{
				item->SetLocation(CVector(-1000, -1000));
				item->SetVelocity(CVector(0, 0));
			}
		}
		visitPen.Reset();
		umlVisitor.Reset();
	}

	CIsBadUMLVisitor badUmlVisitor;
	for (auto uml : outOfBounds)
	{
		uml->Accept(&badUmlVisitor);
		if (badUmlVisitor.IsBadUML()) IncrementScore(0);
		RemoveItem(uml);
		badUmlVisitor.Reset();
	}
	outOfBounds.clear();

	CHaroldPen* pen = nullptr;
	for (auto item : mItems)
	{
		item->Accept(&visitPen);
		if (visitPen.IsHaroldPen())
		{
			penPosition = item->GetPosition();
			penDimensions = item->GetDimensions();
			visitPen.Reset();
			pen = visitPen.GetPen();
			break;
		}
	}
	Rect penRect((INT)(penPosition.X() - penDimensions.X() / 2),
		(INT)(penPosition.Y() - penDimensions.X() / 2),
		(INT)penDimensions.X(), (INT)penDimensions.Y());

	for (auto item : mItems)
	{
		item->Accept(&visitPen);
		if (visitPen.IsHaroldPen())
		{
			visitPen.Reset();
			continue;
		}

		itemPosition = item->GetPosition();
		itemDimensions = item->GetDimensions();
		Rect itemRect((INT)(itemPosition.X() - itemDimensions.X() / 2),
			(INT)(itemPosition.Y() - itemDimensions.Y() / 2),
			(INT)itemDimensions.X(), (INT)itemDimensions.Y());

		if (!(pen->GetAttachedState()) && penRect.IntersectsWith(itemRect))
		{
			item->Effect();
			pen->Effect();
			break;
		}
	}

	// add a UML Item if it has been enough time.
	mUMLTimeDelta += elapsedTime;
	if (mUMLTimeDelta >= TwoSeconds)
	{
		mUMLTimeDelta = 0;
		mEmitter.AddUML();
	}


}

void CGame::Accept(CItemVisitor* visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}
}

/**
 * Determines and updates the orientation of the player in the game field
 * \param x Mouse x location
 * \param y Mouse y location
 */
void CGame::RotatePlayer(double x, double y)
{
	// First convert screen pixels to virutal pixels
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;
	// Determine and set the new angle
	double angle = atan2(Height - oY, oX) - AngleOffset;
	mPlayer.SetAngle(angle);
}

/**
 * Determines and updates the position and orientation of the pen in the game field
 * \param x Mouse x location
 * \param y Mouse y location
 */
void CGame::RotatePen(double x, double y)
{
	// First convert screen pixels to virutal pixels
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;
	// Determine and set the new angle
	double angle = (atan2(Height - oY, oX) - AngleOffset) + PenAngleOffset;
	CVector pos(PenOffset1 * sin(angle), PenOffset1 * cos(angle) + (float)(PenOffset2 - PenOffset3));
	
	CIsHaroldPenVisitor visitPen;
	for (auto item : mItems)
	{
		item->Accept(&visitPen);
		if (visitPen.IsHaroldPen())
		{
			if (visitPen.IsAttached())
			{
				item->SetLocation(pos);
			}
			item->SetAngle(angle);
			visitPen.Reset();
			break;
		}
	}
}

/**
 * Adds an item to the item list
 * \param item Item to add
 */
void CGame::AddItem(shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/**
 * Removes an item from the item list
 * \param item Item to remove
 */
void CGame::RemoveItem(std::shared_ptr<CItem> item)
{
	for (auto iter = mItems.begin(); iter != mItems.end(); iter++)
	{
		if (*iter == item)
		{
			mItems.erase(iter);
			break;
		}
	}
}

/**
 * Removes an item from the item list via pointer (in cases for using "this" pointer)
 * \param item Pointer to item to remove
 */
void CGame::RemoveThisItem(CItem* item)
{
	for (auto sharedPtr : mItems)
	{
		if (sharedPtr.get() == item)
		{
			RemoveItem(sharedPtr);
			break;
		}
	}
}

/**
 * Updates the scoreboard by incrementing a score category.
 * \param category Type of score to increment. -1: unfair, 0: missed, 1: correct 
 */
void CGame::IncrementScore(int category)
{
	switch (category)
	{
	case 0:
		mScoreBoard.IncrementMissed();
		break;
	case 1:
		mScoreBoard.IncrementCorrect();
		break;
	default:
		mScoreBoard.IncrementUnfair();
		break;
	}
}

/**
 * Decrements the unfair score
 */
void CGame::DecrementUnfairScore()
{
	mScoreBoard.DecrementUnfair();
}

/**
 * Constructor loads UML data file
 */
CGame::CGame() : mEmitter(this)
{
	std::wstring filename = L"uml.xml";
	mEmitter.Load(filename);

	shared_ptr<CHaroldPen> hPen = make_shared<CHaroldPen>(CVector(29.0f, 1000.0 - 154.0f), CVector(0.0f, 0.0f), this);
	AddItem(hPen);
}


/**
 * Destructor
 */
CGame::~CGame() 
{
	mItems.clear();
}
