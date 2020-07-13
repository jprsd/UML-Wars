/**
 * \file PowerAllGood.cpp
 *
 * \author Jaideep Prasad
 */

#include "pch.h"

#include <string>
#include "Game.h"
#include "PowerAllGood.h"
#include "IsBadUMLVisitor.h"

using namespace std;

/// Image name for the powerup
const wstring PowerAllGoodImageName = L"poweritem/AllGood.png";

/**
 * All Good power item constructor
 * \param position Position vector of item
 * \param velocity Velocity vector of item
 * \param game The game pointer
 */
CPowerAllGood::CPowerAllGood(CVector position, CVector velocity, CGame* game) :
	CPowerItem(position, velocity, game, PowerAllGoodImageName)
{

}

/**
* Sets the effect on the items
*/
void CPowerAllGood::Effect()
{
	CGame* game = GetGame();
	CIsBadUMLVisitor umlVisitor;

	for (auto item : *game)
	{
		item->Accept(&umlVisitor);
		if (umlVisitor.IsBadUML())
		{
			item->Effect();
			umlVisitor.Reset();
		}

	}

	CPowerItem::Effect();
}
