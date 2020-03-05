
#pragma once

#include <ge211.hxx>

struct Geometry
{
    // Constructs an instance with the default parameters.
    Geometry() noexcept;

    // The dimensions of the whole window:
    ge211::Dimensions scene_dims;

    // The dimensions of the ship (the square at the bottom):
    ge211::Dimensions ship_dims;

    // The dimensions of the enemy
    ge211::Dimensions enemy_dims;

    // The radius of the missile:
    int missile_radius;

    // The missile's  velocity {width, height}:
    ge211::Dimensions missile_velocity0;

    // The enemy's  velocity {width, height}:
    ge211::Dimensions enemy_velocity;

    // Number of pixels from bottom of screen to bottom of ship.
    int bottom_margin;

    // The initial position of the ship. This is a member function because
    // it's computed from the other properties.
    ge211::Position ship_top_left0() const noexcept;

};

