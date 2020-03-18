
#pragma once

#include "geometry.hxx"
#include <ge211.hxx>
#include "enemy.hxx"
using Block = ge211::Rectangle;

struct Missile
{
    ///
    /// CONSTRUCTOR
    ///

    Missile(Geometry const& , bool , ge211::Position const& );

    ///
    /// MEMBER FUNCTIONS
    ///

    ge211::Position top_left() const;

    Missile next() const;

    bool hits_top(Geometry const&) const;
    bool hits_bottom(Geometry const&) const;
    bool hits_side(Geometry const&) const;


    int hits_missile(std::vector<Missile>&, const int&);

    bool hits_enemy(std::vector<Enemy>&);

    bool hits_ship(Block const&) const;

    // reflect the given missile's horizontal velocity (same colors)
    void missile_bounce_();

    ///
    /// MEMBER VARIABLES
    ///

    // The radius of the missile.
    int               radius_;
    // The velocity of the missile in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the missile.
    ge211::Position center_ = {0,0};

    // whether the missile is by enemy or missile
    bool is_enemy;

    bool live_;
};

bool operator==(Missile const&, Missile const&);
bool operator!=(Missile const&, Missile const&);

