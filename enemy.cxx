// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "enemy.hxx"
#include "geometry.hxx"



// the enemy's initial position will depend on pos,
// which will be determined by the model
Enemy::Enemy(Geometry const& geometry, ge211::Position const& pos)
        : dimensions_  (geometry.enemy_dims)
        , velocity_ (geometry.enemy_velocity)
        , top_left_   (pos)
        , live_     (true)
{ }


bool Enemy::hits_bottom(Geometry const& geometry) const
{
    return (top_left_.down_by(dimensions_.height).y > geometry.scene_dims.height);
}

bool Enemy::hits_ship(Block const& ship) const
{
    int ship_x = ship.top_left().right_by(ship.dimensions().width/2).
            down_by(ship.dimensions().height/2).x;
    int ship_y = ship.top_left().right_by(ship.dimensions().width/2).
            down_by(ship.dimensions().height/2).y;
    int e_x = top_left_.down_by(dimensions_.height/2).
            right_by(dimensions_.width/2).x;
    int e_y = top_left_.down_by(dimensions_.height/2).
            right_by(dimensions_.width/2).y;
    int dist = (ship_x - e_x)*(ship_x - e_x) + (ship_y - e_y)*(ship_y - e_y);
    return dist < (ship.dimensions().width+dimensions_.width)*
    (ship.dimensions().width+dimensions_.width);
}



Enemy Enemy::next() const
{
    Enemy result (*this);
    result.top_left_.x += velocity_.width;
    result.top_left_.y += velocity_.height;
    return result;
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


