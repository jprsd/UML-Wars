/**
 * \file PowerAllGone.cpp
 *
 * \author Jaideep Prasad
 */

#include "pch.h"

#include <string>
#include "Game.h"
#include "PowerAllGone.h"
#include "IsUMLItemVisitor.h"
#include "IsBadUMLVisitor.h"

using namespace std;

/// Image name for the powerup
const wstring PowerAllGoneImageName = L"poweritem/Nuke.png";

/**
 * All Gone (nuke) power item constructor
 * \param position Position vector of item
 * \param velocity Velocity vector of item
 * \param game The game pointer
 */
CPowerAllGone::CPowerAllGone(CVector position, CVector velocity, CGame* game) :
	CPowerItem(position, velocity, game, PowerAllGoneImageName)
{

}

/**
* Sets the effect on the items
*/
void CPowerAllGone::Effect()
{
	CGame* game = GetGame();
	CIsUMLItemVisitor umlVisitor;

	for (auto item : *game)
	{
		item->Accept(&umlVisitor);
		if (umlVisitor.IsUML())
		{
			item->Effect();
			umlVisitor.Reset();
		}
		
	}

	CPowerItem::Effect();
}
