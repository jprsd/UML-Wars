/**
* \file ChildView.h
*
* \author Team Sarson
*
*  Class that implements the child window our program draws in.
*
* The window is a child of the main frame, which holds this
* window, the menu bar, and the status bar.
*/

#pragma once

#include "ScoreBoard.h"
#include "Game.h"


/// CChildView window

class CChildView : public CWnd
{
/// Construction
public:
	CChildView();

/// Attributes
public:

/// Operations
public:

/// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

/// Implementation
public:
	virtual ~CChildView();

	/// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	/// The object for our game
	CGame mGame;

	/// True until the first time we draw
	bool mFirstDraw = true;

	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0.0;       ///< Rate the timer updates


public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

