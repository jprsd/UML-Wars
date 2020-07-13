/**
 * \file ScoreBoard.h
 *
 * \author Jaideep Prasad
 *
 * Class for the game score board
 */

#pragma once

/**
 * Game score board class
 */
class CScoreBoard
{
public:
	CScoreBoard();

	/// Do not use copy constructor
	/// \param scoreBoard The other scoreboard
	CScoreBoard(const CScoreBoard& scoreBoard) = delete;

	virtual ~CScoreBoard();

	void Draw(Gdiplus::Graphics* graphics);

	/// Increases correct counter by 1.
	void IncrementCorrect() { mCorrect++; } 

	/// Increases missed counter by 1.
	void IncrementMissed() { mMissed++; }

	///Increases unfair counter by 1.
	void IncrementUnfair() { mUnfair++; }

	/// Decreases unfair counter by 1. Used for certain power-up effects.
	void DecrementUnfair() { mUnfair--; }

	/// Gets the correct hits score
	/// \returns int value for correct hits score
	int GetCorrect() const { return mCorrect; }

	/// Gets the missed score
	/// \returns int value for missed score
	int GetMissed() const { return mMissed; }

	/// Gets the unfair hits score
	/// \returns int value for unfair hits score
	int GetUnfair() const { return mUnfair; }

private:
	/// Number of hits on good UML objects by the player
	int mCorrect = 0;
	/// Number of good UML objects the player failed to hit
	int mMissed = 0;
	/// Number of hits on bad UML objects by the player
	int mUnfair = 0;
};

