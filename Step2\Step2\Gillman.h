/**
 * \file FishBeta.h
 *
 * \author Amtullah Naalwala
 *
 * Class implements a Beta fish
 */

#pragma once

#include <memory>
#include "Item.h"

 /**
  * Implements a Beta fish
  */
class CGillman : public CItem
{
public:
    CGillman(CAquarium* aquarium);

    /// Default constructor (disabled)
    CGillman() = delete;

    /// Copy constructor (disabled)
    CGillman(const CGillman&) = delete;


    virtual void Draw(Gdiplus::Graphics* graphics) override;

    bool HitTest(int x, int y);


private:
    /// The image associated with the Gillman
    std::unique_ptr<Gdiplus::Bitmap> mGillman;

    /// The image associated with the Gillman who is afraid
    std::unique_ptr<Gdiplus::Bitmap> mGillmanAfraid;
};

