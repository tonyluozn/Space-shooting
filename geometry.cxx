// YOU SHOULD NOT CHANGE THIS FILE.

#include "geometry.hxx"

// This is the default (and only) constructor for `Geometry`. It determines
// all the default values of all the member variables.
Geometry::Geometry() noexcept
        : ship_dims     {   20, 10 }
        , missile_radius {10}
        , missile_velocity0 {0,7}
        , enemy_velocity {0,3}
        , enemy_dims {15,15}
        , bottom_margin {30}
        , scene_dims     { 512, 738}
        , missile_launch_y {100}
{ }

ge211::Position Geometry::ship_top_left0() const noexcept
{
    return { scene_dims.width / 2,
             scene_dims.height - bottom_margin - ship_dims.height };
}
