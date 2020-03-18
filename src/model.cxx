#include "model.hxx"
#include "iostream"
Model::Model(Geometry const& geometry)
        : ship_live (false)
        , ship_ ({geometry_.ship_top_left0().x,
                  geometry_.ship_top_left0().y,
                  geometry_.ship_dims.width,
                  geometry_.ship_dims.height})
        , seconds_travelled (0)
        , geometry_ (geometry)
        , missiles_ ({})
        , enemies_ ({})
        , timer_ ()

{

}

// public function
//Return the Ship object
ge211::Rectangle Model::get_ship () const
{
    return ship_ ;
}

//Return all missiles's state
std::vector < Missile > const & Model::get_missiles () const
{
    return missiles_;
}
//Return all enemies' state
std::vector < Enemy > const & Model::get_enemies () const
{
    return enemies_;
}

Geometry Model::get_geometry() const
{
    return geometry_;
}

bool Model::get_live() const
{
    return ship_live;
}


void Model::launch_ship()
{
    ship_live = true;
    timer_ = ge211::Timer();
}

void Model::move_ship(int x)
{
    ship_.x = x;
    if(!ship_live){
        ge211::Rectangle new_ship = {geometry_.ship_top_left0().x,
                                     geometry_.ship_top_left0().y,
                                     geometry_.ship_dims.width,
                                     geometry_.ship_dims.height};
        ship_ = new_ship;
    }
}

void Model::ship_launch_missile() {
    Missile add = Missile(geometry_, false,
            {ship_.top_left().x + ship_.width / 2,
             ship_.top_left().y - 2 * geometry_.missile_radius});
    //add.velocity_.height +=1;
    missiles_.push_back(add);

}

bool Model::check_enemy(Enemy& en){
    for(Enemy& e: enemies_){
        int dist = (en.top_left_.x - e.top_left_.x) * (en.top_left_.x -
                   e.top_left_.x) +
                   (en.top_left_.y - e.top_left_.y) * (en.top_left_.y -
                   e.top_left_.y);
        if(dist < 7225)
        {
            return false;
        }
    }
    return true;
}

void Model::generate_enemy(){
    Enemy new_enemy = Enemy(geometry_, {rand() % 384 + 64, 0});
    while(!check_enemy(new_enemy)){
        return;
    }
    enemies_.push_back(new_enemy);
}
void Model::enemy_fire(Enemy& enemy){
    Missile m0 = Missile(geometry_, true,
                         {enemy.top_left_.x+ enemy.dimensions_.width/2 ,
                          enemy.top_left_.y + 35});
    if(rand()%10 > 5){
        m0.velocity_.width += (3 + rand()%2);
    } else {
        m0.velocity_.width -= (3 + rand()%2);
    }

    Missile m1 = Missile(geometry_, true,
                         {enemy.top_left_.x + enemy.dimensions_.width/2 + 10,
                          enemy.top_left_.y + 15});
    m1.velocity_.width += (3 + rand()%3);
    Missile m2 = Missile(geometry_, true,
                         {enemy.top_left_.x + enemy.dimensions_.width/2 - 10,
                          enemy.top_left_.y + 15});
    m2.velocity_.width -= (3 + rand()%3);
    Missile m3 = Missile(geometry_, true,
                         {enemy.top_left_.x + enemy.dimensions_.width/2 + 20,
                          enemy.top_left_.y - 5 });
    m3.velocity_.width += (5 +rand()%3);
    Missile m4 = Missile(geometry_, true,
                         {enemy.top_left_.x + enemy.dimensions_.width/2 - 20,
                          enemy.top_left_.y - 5 });
    m4.velocity_.width -= (5 + rand()%3);
    missiles_.push_back(m0);
    missiles_.push_back(m1);
    missiles_.push_back(m2);
    missiles_.push_back(m3);
    missiles_.push_back(m4);
}

void Model::update(int& s) {
    if (ship_live) {
        seconds_travelled = timer_.elapsed_time().seconds();
        for(int i = 0; i<missiles_.size(); i++){
            if (missiles_[i].next().hits_ship(ship_)){
                ship_live = false;
                missiles_.clear();
                enemies_.clear();
                return;
            }
            if (missiles_[i].is_enemy &&
            missiles_[i].next().hits_bottom(geometry_)){
                missiles_[i].live_ = false;

            }
            if (!missiles_[i].is_enemy &&
            missiles_[i].next().hits_top(geometry_)){
                missiles_[i].live_ = false;
            }
            if (missiles_[i].next().hits_side(geometry_)){
                missiles_[i].live_ = false;
            }
            int result = missiles_[i].next().hits_missile(missiles_, i);
            if ( result== 2){
                missiles_[i].live_ = false;
            }
            if (result == 3){
                missiles_[i].missile_bounce_();
            }
            if (!missiles_[i].is_enemy &&
                missiles_[i].next().hits_enemy(enemies_)){
                missiles_[i].live_ = false;
            }
        }
        std::vector<Missile>update_ms;

        for(Missile &m : missiles_){
            if(m.live_) update_ms.push_back(m);
        }
        missiles_.clear();
        for(Missile & update : update_ms){
            missiles_.push_back(update);
        }
        if (!missiles_.empty()) {
            for (Missile &m: missiles_) {
                m = m.next();
            }
        }
        for (Enemy &enemy : enemies_) {
            Enemy next = enemy.next();
            if (enemy.top_left_.y < geometry_.missile_launch_y &&
            next.top_left_.y > geometry_.missile_launch_y) {
                enemy_fire(enemy);
            }
            if (next.hits_ship(ship_)){
                enemies_.clear();
                missiles_.clear();
                ship_live = false;
                return;
            } if (next.hits_bottom(geometry_)) {
                enemy.live_ = false;

            }
        }
        std::vector<Enemy>update_es;
        for(Enemy &e : enemies_){
            if(e.live_) update_es.push_back(e);
        }
        enemies_.clear();
        for(Enemy & update : update_es){
            enemies_.push_back(update);
        }
        if (!enemies_.empty()) {
            for (Enemy &e: enemies_) {
                e = e.next();
            }
        }
        if (rand() % 100 < 10) {
            generate_enemy();
        }
        s = s+1;
        if (s == 2) {
            ship_launch_missile();
        }
    }
}

// return time that has passed since the game started.
int Model::get_time_() const
{
    return  seconds_travelled;
}



