// YOU SHOULD NOT CHANGE THIS FILE.

#include "geometry.hxx"

// This is the default (and only) constructor for `Geometry`. It determines
// all the default values of all the member variables.
Geometry::Geometry() noexcept
        : ship_dims     {   10, 10 }
        , missile_radius {1}
        , missile_velocity0{0,1}
        , ship_dims {4,1}
        , enemy_velocity {0,1}
        , bottom_margin {10}
        , scene_dims     { 1024, 2000 }
{ }

ge211::Position Geometry::ship_top_left0() const noexcept
{
    return { scene_dims.width / 2,
             scene_dims.height - bottom_margin - ship_dims.height };
}
