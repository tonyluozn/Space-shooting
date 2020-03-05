// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "enemy.hxx"
#include "geometry.hxx"


// the enemy's initial position will depend on pos, which will be determined by the model
Enemy::Enemy(Geometry const& geometry, ge211::Position const& pos)
        : dimensions_  (geometry.ship_dims)
        , velocity_ (geometry.enemy_velocity)
        , top_left_   (pos)
        , live_     (true)
{ }

bool Enemy::hits_bottom(Geometry const& geometry) const
{
    return (top_left_.down_by(geometry.enemy_dims.height).y > geometry.scene_dims.height);
}


Enemy Enemy::next() const
{
    Enemy result (*this);
    result.top_left_.x += velocity_.width;
    result.top_left_.y += velocity_.height;
    return result;
}

bool Enemy::hits_ship(Block const& ship) const
{

}

bool operator==(Enemy const& b1, Enemy const& b2)
{
    return (b1.dimensions_ == b2.dimensions_
            && b1.top_left_ == b2.top_left_
            && b1.velocity_ == b2.velocity_
            && b1.live_ == b2.live_);
}

bool operator!=(Enemy const& b1, Enemy const& b2)
{
    return !(b1 == b2);
}


