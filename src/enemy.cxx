// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "missile.hxx"
#include "geometry.hxx"


// the enemy's initial position will depend on pos, which will be determined by the model
Enemy::Enemy(Geometry const& geometry, ge211::Position const& pos)
        : dimensions_  (geometry.ship_dims)
        , velocity_ (geometry.enemy_velocity)
        , top_left_   (pos.down_by())
        , live_     (true)
{ }

bool Enemy::hits_bottom(Geometry const& geometry) const
{
    return (top_left_.down_by(dimensions_) > geometry.scene_dims.height);
}

bool Enemy::hits_side(Geometry const& geometry) const
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
    // is there an easier way?
    bool a = (missile.top_right().x < center_.x - radius_
              || center_.x + radius_ < missile.top_left().x);
    bool b = (missile.bottom_left().y < center_.y - radius_
              || center_.y + radius_ < missile.top_left().y);
    return !(a||b);
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

bool Missile::destroy_missile(std::vector<Missile>& missiles) const
{
    for(int i=0; i< missiles.size(); i++){
        if (hits_missile(missiles[i])) {
            std::swap(missiles[i], missiles.back());
            missiles.pop_back();
            return true;
        }
    }
    return false;
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


