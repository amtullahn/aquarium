/**
 * \file FishClown.h
 *
 * \author Amtullah Naalwala
 *
 * Class implements a clown fish 
 */


#pragma once

#include <memory>
#include "Item.h"

/**
 * Implements a Clown Fish
 */
class CFishClown :
	public CItem
{
public:
    /// Default constructor (disabled)
    CFishClown() = delete;

    /// Copy constructor (disabled)
    CFishClown(const CFishClown&) = delete;
    
    CFishClown(CAquarium* aquarium);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    
    bool HitTest(int x, int y);

private:
    /// The image associated with the Clown fish
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

