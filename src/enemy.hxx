
#pragma once

#include "geometry.hxx"
#include <ge211.hxx>
using Block = ge211::Rectangle;

struct Enemy
{
    ///
    /// CONSTRUCTOR
    ///

    Enemy(Geometry const&, ge211::Position const&);

    ///
    /// MEMBER FUNCTIONS
    ///

    Enemy next() const;


    bool hits_bottom(Geometry const&) const;

    bool hits_ship(Block const&) const;

    ///
    /// MEMBER VARIABLES
    ///
    ge211::Dimensions dimensions_;

    // The velocity of the enemy in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the top_left of the enemy.
    ge211::Position  top_left_;

    // Whether the missile exists
    bool              live_;
};

bool operator==(Enemy const&, Enemy const&);
bool operator!=(Enemy const&, Enemy const&);

