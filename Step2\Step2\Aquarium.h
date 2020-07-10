/**
 * \file Aquarium.h
 *
 * \author Amtullah Naalwala
 *
 * Class that represents an aquarium 
 */

#pragma once


#include <memory>
#include <vector>
#include "Gillman.h"

using namespace std; 
class CItem;

/**
 * Represents an aquarium
 */
class CAquarium
{
public:
    CAquarium();

    void OnDraw(Gdiplus::Graphics* graphics);

    /// Adds a fish the the aquarium
    void Add(std::shared_ptr<CItem> item);

    std::shared_ptr<CItem> HitTest(int x, int y);

    /// Moves grabbed items to the end of the items
    void MoveToEnd(shared_ptr<CItem> item);

    /// Value displaying location of Gillman
    double GillmanDistanceCheck(CGillman* gillman);

private:
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image to use

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<CItem> > mItems;
};
