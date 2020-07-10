/**
 * \file Aquarium.cpp
 *
 * \author Amtullah Naalwala
 */

#include <algorithm>

#include "pch.h"
#include "Aquarium.h"

#include "FishBeta.h"
#include "FishClown.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
 */
CAquarium::CAquarium()
{
    mBackground = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/background1.png"));
    if (mBackground->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/background1.png");
    }

   
}

/** Draw the aquarium
* \param graphics The GDI+ graphics context to draw on
*/
void CAquarium::OnDraw(Gdiplus::Graphics* graphics)
{
    graphics->DrawImage(mBackground.get(), 0, 0,
        mBackground->GetWidth(), mBackground->GetHeight());

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 16);

    SolidBrush green(Color(0, 64, 0));
    graphics->DrawString(L"Under the Sea!", -1, &font, PointF(2, 2), &green);

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/**
 * Add an item to the aquarium
 * \param item New item to add
 */
void CAquarium::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/** Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**
 * Moves item to the end of list mItems
 * \param item the item selected to be moved
 */
void CAquarium::MoveToEnd(shared_ptr<CItem> item)
{
    
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
        mItems.push_back(item);
    }
}


/**
 * Checks the proximity of the gillman to the fish
 * \param gillman an pointer to an item 
 * \returns the location value of the gillman
 */
double CAquarium::GillmanDistanceCheck(CGillman*gillman)
{
    //location X and location Y is the position of the fish
    // GillmanX and GillmanY is the location of the Gillman

    double nearestDistance = 1000;
    for (auto item : mItems)
    {
        // comparing the fish location to the gillman 
        //(Smart pointer to regular pointer)
        // If the fish gets near the gillman, the gillman is afraid
        // If the fish backs away from the gillman its not afraid anymore

        if (item.get() == gillman) {
            continue;
        }
        // Distance in the X and Y directions
        double dx = item->GetX() - gillman->GetX();
        double dy = item->GetY() - gillman->GetY();

        //determining how far away we are
        double distance = sqrt(dx * dx + dy * dy);

        // if the fish is within proximity then you return true because the gillman is afraid
        if (distance < nearestDistance) {
            nearestDistance = distance;
        }
        else {
            continue;
        }
        return nearestDistance;
        


    }


}

