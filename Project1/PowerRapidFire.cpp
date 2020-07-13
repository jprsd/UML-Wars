/**
 * \file PowerRapidFire.cpp
 *
 * \author Jaideep Prasad
 */

#include "pch.h"

#include <string>
#include "Game.h"
#include "PowerRapidFire.h"
#include "IsHaroldPenVisitor.h"

using namespace std;

/// Image name for the powerup
const wstring PowerRapidFireImageName = L"poweritem/RapidFire.png";

/// Time limit of 15 seconds
const double TimeLimit = 15;

/**
 * Rapid Fire power item constructor
 * \param position Position vector of item
 * \param velocity Velocity vector of item
 * \param game The game pointer
 */
CPowerRapidFire::CPowerRapidFire(CVector position, CVector velocity, CGame* game) :
	CPowerItem(position, velocity, game, PowerRapidFireImageName)
{

}

/**
* Sets the effect on the items
*/
void CPowerRapidFire::Effect()
{
	CGame* game = GetGame();
	CIsHaroldPenVisitor isPenVisior;
	for (auto item : *game)
	{
		item->Accept(&isPenVisior);
		if (isPenVisior.IsHaroldPen())
		{
			isPenVisior.GetPen()->SetVelocityMultiplier(2.5);
			break;
		}
	}
	mIsActive = true;
	CPowerItem::Effect();
}

/**
* Updates the position and checkes to see if the pen hits
* \param elapsedTime time since the last update
*/
void CPowerRapidFire::Update(double elapsedTime)
{
	if (mIsActive)
	{
		mTimeActive += elapsedTime;
		if (mTimeActive >= TimeLimit)
		{
			CGame* game = GetGame();
			CIsHaroldPenVisitor isPenVisior;
			for (auto item : *game)
			{
				item->Accept(&isPenVisior);
				if (isPenVisior.IsHaroldPen())
				{
					isPenVisior.GetPen()->SetVelocityMultiplier();
					break;
				}
			}
			mIsActive = false;
			mTimeActive = 0;
		}
	}
	CPowerItem::Update(elapsedTime);
}
