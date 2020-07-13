/**
 * \file ScoreBoard.cpp
 *
 * \author Jaideep Prasad
 */

#include "pch.h"
#include <string>
#include "ScoreBoard.h"

using namespace std;
using namespace Gdiplus;

/**
 * Score board constructor
 */
CScoreBoard::CScoreBoard()
{
}


/**
 * Score board destructor
 */
CScoreBoard::~CScoreBoard()
{
}

/**
 * Draws the scores to the window screen
 * \param graphics Graphics Object
 */
void CScoreBoard::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 26);
	SolidBrush black(Color(0, 0, 0));
	graphics->DrawString(to_wstring(mCorrect).c_str(), -1, &font, PointF(-575, 50), &black);
	graphics->DrawString(L"Correct", -1, &font, PointF(-650, 100), &black);
	graphics->DrawString(to_wstring(mMissed).c_str(), -1, &font, PointF(-25, 50), &black);
	graphics->DrawString(L"Missed", -1, &font, PointF(-100, 100), &black);
	graphics->DrawString(to_wstring(mUnfair).c_str(), -1, &font, PointF(500, 50), &black);
	graphics->DrawString(L"Unfair", -1, &font, PointF(450, 100), &black);
}
