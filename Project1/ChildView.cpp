/**
 * \file ChildView.cpp
 *
 * \author Reid Shinabarker
 * \author Jaideep Prasad
 */

#include "pch.h"
#include <sstream>
#include <iostream>

#include "framework.h"
#include "Project1.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"

using namespace std;
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Constructor
 */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}

/// \cond
/// This doxygen switch tells it to ignore this block of code
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()
/// \endcond



// CChildView message handlers


/**
* This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);    // Create GDI+ graphics context

	CRect rect;
	GetClientRect(&rect); //Determine window size automatically

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		 * Initialize the elapsed time system
		 */
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	 * Compute the elapsed time since the last draw
	 */
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	LARGE_INTEGER clockPerfomance;
	QueryPerformanceFrequency(&clockPerfomance);

	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mGame.Update(elapsed);

	mGame.OnDraw(&graphics, rect.Width(), rect.Height());

}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}


/**
 * Handle timer events
 * \param nIDEvent The timer event ID
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


/**
 * Game response to mouse left button press
 * \param nFlags Flags associated with this event
 * \param point Mouse point location
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGame.OnLButtonDown(point.x, point.y);
	CWnd::OnLButtonDown(nFlags, point);
}

/**
 * Game response to mouse movement
 * \param nFlags Flags associated with this event
 * \param point Mouse point location
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	mGame.RotatePlayer(point.x, point.y);
	mGame.RotatePen(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);
}
