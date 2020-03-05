// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "missile.hxx"
#include "geometry.hxx"


//block can be either ship or enemy, and the initial position of the missile will depend on that
Missile::Missile(Geometry const& geometry, bool enemy, Block const& block)
        : radius_   (geometry.missile_radius)
        , is_enemy  (enemy)
{
    // if the missile is from enemy, the missile's initial position will be below the enemy, going downward
    // if the missile is from ship, the missile's initial position will be above the ship, going upward
    if(enemy){
        center_ = block.bottom_left().right_by(block.width/2).down_by(1 + geometry.missile_radius);
        velocity_ = geometry.missile_velocity0;
    }else{
        center_ = block.top_left().right_by(block.width/2).up_by(1 + geometry.missile_radius);
        velocity_ = geometry.missile_velocity0 * (-1);
    }

}

ge211::Position Missile::top_left() const
{
    return center_.left_by(radius_).up_by(radius_);
}

bool Missile::hits_bottom(Geometry const& geometry) const
{
    return (center_.down_by(radius_).y > geometry.scene_dims.height);
}

bool Missile::hits_side(Geometry const& geometry) const
{
    bool a = center_.left_by(radius_).x < 0;
    bool b = center_.right_by(radius_).x > geometry.scene_dims.width;
    return ( a||b );
}

Missile Missile::next() const
{
    Missile result (*this);
    result.center_.x += velocity_.width;
    result.center_.y += velocity_.height;
    return result;
}

bool Missile::hits_missile(Missile const& missile) const
{

}

bool Missile::hits_ship(Block const& ship) const
{
    bool a = (ship.top_right().x < center_.x - radius_
              || center_.x + radius_ < ship.top_left().x);
    bool b = (ship.bottom_left().y < center_.y - radius_
              || center_.y + radius_ < ship.top_left().y);
    return !(a||b);
}

void missile_bounce_(Missile & missile){
    missile.velocity_.width *= -1;
}



bool operator==(Missile const& b1, Missile const& b2)
{
    return (b1.radius_ == b2.radius_
            && b1.center_ == b2.center_
            && b1.velocity_ == b2.velocity_
            && b1.live_ == b2.live_);
}

bool operator!=(Missile const& b1, Missile const& b2)
{
    return !(b1 == b2);
}


