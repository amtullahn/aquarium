/**
 * \file Item.cpp
 *
 * \author Amtullah Naalwala
 */


#include "pch.h"
#include "Item.h"
#include "Aquarium.h"
//using namespace CItem;

 /** Constructor
 * \param aquarium The aquarium this item is a member of
 */
CItem::CItem(CAquarium* aquarium) : mAquarium(aquarium)
{
}


/**
 * Destructor
 */
CItem::~CItem()
{
}

