/**
 * \file ChildView.cpp
 *
 * \author Amtullah Naalwala
 */

// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Step2.h"
#include "ChildView.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishClown.h"
#include "FishDory.h"
#include "DoubleBufferDC.h"

#include<memory>
#include "Gillman.h"


using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/// Any item we are currently dragging
std::shared_ptr<CItem> mGrabbedItem;

// CChildView

/**
 * Constructor
 */
CChildView::CChildView()
{
}


/**
 * Destruction
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
//    ON_WM_ERASEBKGND()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_ADDFISH_CLOWNFISH, &CChildView::OnAddfishClownfish)
    ON_COMMAND(ID_ADDFISH_DORYFISH, &CChildView::OnAddfishDoryfish)
    ON_COMMAND(ID_ADDFISH_GILLMAN, &CChildView::OnAddfishGillman)
END_MESSAGE_MAP()



// CChildView message handlers



/** This function is called before the window is created.
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

/** This function is called to draw in the window
 * 
 * This function is called in response to a drawing message
 * Whenever we need to redraw the window on the screen.
 * It is responsible for painting the window from scratch.
 */
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this); // device context for painting
    CDoubleBufferDC dc(&paintDC); // device context for painting

    Graphics graphics(dc.m_hDC); // Create GDI+ graphics context
    
    mAquarium.OnDraw(&graphics);
}

/**
 * Add fish/beta menu option hander
 */
void CChildView::OnAddfishBetafish()
{
    
    // allocates a new object of type CFishBeta and passes it to the aquarium
    // make_shared creates an object of the proper type and return a shared_ptr object
    auto fish = make_shared<CFishBeta>(&mAquarium);
    fish->SetLocation(InitialX, InitialY);
    mAquarium.Add(fish);
    Invalidate();
}

/**
 * Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    mGrabbedItem = mAquarium.HitTest(point.x, point.y);
    if (mGrabbedItem != nullptr)
    {
        // We have selected an item
        // Move it to the end of the list of items
        mAquarium.MoveToEnd(mGrabbedItem);
    }
}

/**
 * Called when the left mouse button is released
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    OnMouseMove(nFlags, point);
}

/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to 
        // move it while the left button is down.
        if (nFlags & MK_LBUTTON)
        {
            mGrabbedItem->SetLocation(point.x, point.y);
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Invalidate();
    }
}

/** Erase the background
 * 
 * This is disabled to eliminate the clicker
 * \param pDC Device Context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: Add your message handler code here and/or call default

    return FALSE;
}

/**
 * Add fish handler for clown fish
 * Adds a clown fish to the aquarium
 */
void CChildView::OnAddfishClownfish()
{
    // allocates a new object of type CFishBeta and passes it to the aquarium
    // make_shared creates an object of the proper type and return a shared_ptr object
    auto fish = make_shared<CFishClown>(&mAquarium);
    fish->SetLocation(InitialX, InitialY);
    mAquarium.Add(fish);
    Invalidate();
}

/** Add fish handler for dory fish
 *  Adds dory fish to the aquarium
 */
void CChildView::OnAddfishDoryfish()
{
    // allocates a new object of type CFishBeta and passes it to the aquarium
    // make_shared creates an object of the proper type and return a shared_ptr object
    auto fish = make_shared<CFishDory>(&mAquarium);
    fish->SetLocation(InitialX, InitialY);
    mAquarium.Add(fish);
    Invalidate();
}


/** Add fish handler for the Gillman
 * Adds a gillman to the aquarium
 */
void CChildView::OnAddfishGillman()
{
    // allocates a new object of type CFishBeta and passes it to the aquarium
    // make_shared creates an object of the proper type and return a shared_ptr object
    auto fish = make_shared<CGillman>(&mAquarium);
    fish->SetLocation(InitialX, InitialY);
    mAquarium.Add(fish);
    Invalidate();
}
