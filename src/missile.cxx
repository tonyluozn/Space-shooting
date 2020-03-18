// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "missile.hxx"
#include "geometry.hxx"
#include "enemy.hxx"
#include "iostream"


//block can be either ship or enemy, and the initial
// position of the missile will depend on that
Missile::Missile(Geometry const& geometry, bool enemy,
        ge211::Position const& pos)
        : radius_   (geometry.missile_radius)
        , is_enemy  (enemy)
        , live_ (true)
{
    // if the missile is from enemy, the missile's initial position
    // will be below the enemy, going downward
    // if the missile is from ship, the missile's initial position
    // will be above the ship, going upward
    if(enemy){
        center_ = pos;
        velocity_ = geometry.missile_velocity0;
    } else {
        center_ = pos;
        velocity_ = geometry.missile_velocity0 * (-1);
    }

}

ge211::Position Missile::top_left() const
{
    return center_.left_by(radius_).up_by(radius_);
}

bool Missile::hits_top(Geometry const& geometry) const {
    return (center_.up_by(radius_).y < 0);
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

int Missile::hits_missile(std::vector<Missile>& list, const int& index)
{
    int flag = 0;
    std::vector<Missile> left;
    for(int i = index+1; i< list.size(); i++){
        left.push_back(list[i]);
    }
    for(Missile& obj : left){
        Missile next = obj.next();
        int dist = (next.center_.x - center_.x)*(next.center_.x - center_.x) +
                   (next.center_.y - center_.y) * (next.center_.y - center_.y);
        if(dist < 4*radius_*radius_){
            if(*this != obj.next()){
                if(is_enemy && obj.is_enemy){
                    obj.missile_bounce_();
                    if(flag !=2) flag = 3; //bounce
                } else if (is_enemy || obj.is_enemy){
                    obj.live_ = false;
                    flag = 2; //delete
                }
            }
        }
    }
    //left.push_back(*this);
   for(int c =0; c<left.size(); c++){
       list[index+1+c] = left[c];
   }
    return flag;
}

bool Missile::hits_enemy(std::vector<Enemy>& list){
    bool flag = false;
    for(Enemy& obj : list) {
        double e_x = obj.top_left_.right_by(obj.dimensions_.width/2).
                down_by(obj.dimensions_.width/2).x;
        double e_y = obj.top_left_.right_by(obj.dimensions_.width/2).
                down_by(obj.dimensions_.width/2).y;
        double dist = (center_.x - e_x) * (center_.x - e_x) +
                (center_.y - e_y) * (center_.y - e_y);
        double d = (radius_ + (obj.dimensions_.width/2))*
                (radius_ + (obj.dimensions_.width/2));
        if (dist < d) {
            obj.live_ = false;
            flag = true;
        }
    }
    return flag;
}

bool Missile::hits_ship(Block const& ship) const
{
    bool a = (ship.top_right().x < center_.x - radius_
              || center_.x + radius_ < ship.top_left().x);
    bool b = (ship.bottom_left().y < center_.y - radius_
              || center_.y + radius_ < ship.top_left().y);
    return !(a||b);
}

void Missile::missile_bounce_(){
    velocity_.width = velocity_.width * (-1);
    if (velocity_.width > 0 && velocity_.width < 12) {
        velocity_.width += 2;
    }
    if (velocity_.width < 0 && velocity_.width > -12) {
        velocity_.width -= 2;
    }
}

bool operator==(Missile const& b1, Missile const& b2)
{
    return (b1.radius_ == b2.radius_
            && b1.center_ == b2.center_
            && b1.velocity_ == b2.velocity_
    );
}

bool operator!=(Missile const& b1, Missile const& b2)
{
    return !(b1 == b2);
}

