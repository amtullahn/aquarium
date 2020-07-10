/**
 * \file FishBeta.h
 *
 * \author Amtullah Naalwala
 *
 * Class implements a Dory fish
 */

#pragma once

#include <memory>

#include "Item.h"


 /**
  * Implements a Dory fish
  */
class CFishDory : public CItem
{
public:
    CFishDory(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishDory() = delete;

    /// Copy constructor (disabled)
    CFishDory(const CFishDory&) = delete;


    virtual void Draw(Gdiplus::Graphics* graphics) override;

    bool HitTest(int x, int y);

private:
    /// The image associated with the Dory Fish
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};


