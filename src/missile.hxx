
#pragma once

#include "geometry.hxx"
#include <ge211.hxx>
using Block = ge211::Rectangle;

struct Missile
{
    ///
    /// CONSTRUCTOR
    ///

    Missile(Geometry const&);

    ///
    /// MEMBER FUNCTIONS
    ///

    ge211::Position top_left() const;

    Missile next() const;


    bool hits_bottom(Geometry const&) const;
    bool hits_side(Geometry const&) const;

    // Collision detection for blocks. Returns whether the circle's
    // bounding box intersects with the given block.
    //
    // Intersection between a circle and a rectangle is tricky, so we
    // will approximate it with the intersection of two rectangles.

    bool Missile::hits_missile(Missile const&) const;

    bool Missile::hits_ship(Block const&) const;

    bool destroy_missile(std::vector<Missile>& missiles) const;

    // reflect the given missile's horizontal velocity (same colors)
    void missile_bounce_(Missile &);

    ///
    /// MEMBER VARIABLES
    ///

    // The radius of the missile.
    int               radius_;
    // The velocity of the missile in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the missile.
    ge211::Position   center_;

    // Whether the missile exists
    bool              live_;

    // whether the missile is by enemy or missile
    bool is_enemy;
};

bool operator==(Missile const&, Missile const&);
bool operator!=(Missile const&, Missile const&);

