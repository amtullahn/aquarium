/**
 * \file FishBeta.cpp
 *
 * \author Amtullah Naalwala
 */


#include "pch.h"
#include <string>
#include "Gillman.h"
#include "Aquarium.h"

using namespace std;
using namespace Gdiplus;

/// minimum distance from the Gillman
const double minProximity = 300;
/// Fish filename 
const wstring GillmanImageName = L"images/gillman.png";
const wstring GillmanAfraidImageName = L"images/gillman-afraid.png";


/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CGillman::CGillman(CAquarium* aquarium) : CItem(aquarium)
{
    mGillman = unique_ptr<Bitmap>(Bitmap::FromFile(GillmanImageName.c_str()));

    if (mGillman->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += GillmanImageName;
        AfxMessageBox(msg.c_str());

 
    }

    mGillmanAfraid = unique_ptr<Bitmap>(Bitmap::FromFile(GillmanAfraidImageName.c_str()));
    if (mGillmanAfraid->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += GillmanAfraidImageName;
        AfxMessageBox(msg.c_str());
    }
}

/**
 * Draw our fish
 * \param graphics The graphics context to draw on
 */
void CGillman::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mGillman->GetWidth();
    double hit = mGillman->GetHeight();
    
    //Getter to obtain the location of the gillman
    double dist = GetAquarium()->GillmanDistanceCheck(this);

    // if the fish is near the gillman, we draw the image of the gillman being afraid
    if (dist <= minProximity) 
    {
        graphics->DrawImage(mGillmanAfraid.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mGillman->GetWidth(), (float)mGillman->GetHeight());
    }
    // if the fish goes away from the gillman, draw the unafraid gillman 
    else
    {
        graphics->DrawImage(mGillman.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mGillman->GetWidth(), (float)mGillman->GetHeight());
    }
}

/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CGillman::HitTest(int x, int y)
{
    double wid = mGillman->GetWidth();
    double hit = mGillman->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mGillman->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mGillman->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}

