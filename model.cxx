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
//    enemies_.push_back(Enemy(geometry_,{100,100}));
//    enemies_.push_back(Enemy(geometry_,{200,100}));
//    enemies_.push_back(Enemy(geometry_,{300,100}));
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
        if(e.top_left_.y < 30 &&e.top_left_.x< en.top_left_.x+7 &&e.top_left_.x > en.top_left_.x-7)
        {
            return false;
        }
    }
    return true;
}

void Model::generate_enemy(){
    Enemy new_enemy = Enemy(geometry_, {rand() % 384 + 64, 0});
    while(check_enemy(new_enemy)){
        new_enemy = Enemy(geometry_, {rand() % 384 + 64, 0});
    }
    enemies_.push_back(new_enemy);

}


void Model::enemy_fire(Enemy& enemy){
    Missile m0 = Missile(geometry_, true,
            {enemy.top_left_.x+ enemy.dimensions_.width/2 ,
             enemy.top_left_.y + 30});
    Missile m1 = Missile(geometry_, true,
            {enemy.top_left_.x + enemy.dimensions_.width/2 + 20,
             enemy.top_left_.y + 10});
    m1.velocity_.width += (4 + rand()%3);
    Missile m2 = Missile(geometry_, true,
            {enemy.top_left_.x + enemy.dimensions_.width/2 - 20,
             enemy.top_left_.y + 10});
    m2.velocity_.width -= (4 + rand()%3);
    Missile m3 = Missile(geometry_, true,
            {enemy.top_left_.x + enemy.dimensions_.width/2 + 35,
             enemy.top_left_.y - 10 });
    m3.velocity_.width += (4 +rand()%3);
    Missile m4 = Missile(geometry_, true,
            {enemy.top_left_.x + enemy.dimensions_.width/2 - 35 ,
             enemy.top_left_.y - 10 });
    m4.velocity_.width -= (4 + rand()%3);
    missiles_.push_back(m0);
    missiles_.push_back(m1);
    missiles_.push_back(m2);
    missiles_.push_back(m3);
    missiles_.push_back(m4);
}

void Model::update(int& s) {
    if (ship_live) {
        //std::cout<<missiles_.size()<<" remains as missile
        // , "<<enemies_.size()<<" remains as enemy \n";
        seconds_travelled = timer_.elapsed_time().seconds();
        for(int i = 0; i<missiles_.size(); i++){
            std::vector<Missile> left_;
            for(int j = i+1; j<missiles_.size(); j++){
                left_.push_back(missiles_[j]);
            }
            if (missiles_[i].next().hits_ship(ship_)){
                ship_live = false;
                missiles_.clear();
                enemies_.clear();
                return;
            }
            if (missiles_[i].is_enemy &&
            missiles_[i].next().hits_bottom(geometry_)){
                missiles_[i].live_ = false;

            }  else if (!missiles_[i].is_enemy &&
            missiles_[i].next().hits_top(geometry_)){
                missiles_[i].live_ = false;

            }  else if (missiles_[i].next().hits_side(geometry_)){
                missiles_[i].live_ = false;

            }  else if (missiles_[i].next().hits_missile(left_) == 2){
                missiles_[i].live_ = false;

            } else if (missiles_[i].next().hits_missile(left_) == 1){
                missiles_[i].missile_bounce_();
            } else if (!missiles_[i].is_enemy &&
            missiles_[i].next().hits_enemy(enemies_)){
                missiles_[i].live_ = false;
                std::cout <<"hits enemy \n";
            }
        }
        std::vector<Missile>update_ms;

        for(Missile &m : missiles_){
            if(m.live_) update_ms.push_back(m);
        }
        missiles_.clear();
        for(Missile & update : update_ms){
            missiles_.push_back(update);
        } if (!missiles_.empty()) {
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
                std::cout <<"enemy hits ship \n";

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
        } if (!enemies_.empty()) {
            for (Enemy &e: enemies_) {
                e = e.next();
            }
        }
        if (rand() % 100 < 6) {
            generate_enemy();
            std::cout<<"sends enemy \n";
        }
        s = s+1;
        if (s == 2) {
            ship_launch_missile();
        }
    }
}



// Private helper


// Returns the ship to the starting position
void Model::reset_ship_()
{

}

// return time that has passed since the game started.
const std::string & Model::get_time_() const
{
    return std::to_string(seconds_travelled);
}



