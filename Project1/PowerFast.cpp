/**
 * \file PowerFast.cpp
 *
 * \author Isaac Mayers
 * \author Jaideep Prasad
 */

#include "pch.h"

#include <string>
#include "Game.h"
#include "PowerFast.h"
#include "IsHaroldPenVisitor.h"

using namespace std;

/// Image name for the powerup
const wstring PowerFastImageName = L"poweritem/FastFall.png";

/// Time limit of 20 seconds
const double TimeLimit = 20;

/**
 * All Fast power item constructor
 * \param position Position vector of item
 * \param velocity Velocity vector of item
 * \param game The game pointer
 */
CPowerFast::CPowerFast(CVector position, CVector velocity, CGame* game) :
	CPowerItem(position, velocity, game, PowerFastImageName)
{

}

/**
* Sets the effect on the items
*/
void CPowerFast::Effect()
{
	CGame* game = GetGame();
	CIsHaroldPenVisitor isPenVisior;
	for (auto item : *game)
	{
		item->Accept(&isPenVisior);
		if (isPenVisior.IsHaroldPen())
		{
			isPenVisior.Reset();
			continue;
		}
		item->SetVelocityMultiplier(2.5);
	}
	mIsActive = true;
	CPowerItem::Effect();
}

/**
* Updates the position and checkes to see if the pen hits
* \param elapsedTime time since the last update
*/
void CPowerFast::Update(double elapsedTime)
{
	if (mIsActive)
	{
		mTimeActive += elapsedTime;
		if (mTimeActive < TimeLimit)
		{
			Effect();
		}
		else
		{
			CGame* game = GetGame();
			CIsHaroldPenVisitor isPenVisior;
			for (auto item : *game)
			{
				item->Accept(&isPenVisior);
				if (isPenVisior.IsHaroldPen())
				{
					isPenVisior.Reset();
					continue;
				}
				item->SetVelocityMultiplier();
			}
			mIsActive = false;
			mTimeActive = 0;
		}
	}
	CPowerItem::Update(elapsedTime);
}
