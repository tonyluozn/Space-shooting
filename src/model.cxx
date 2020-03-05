#include "model.hxx"

Model::Model(Geometry const& geometry)
        : ship_live (false)
        ,ship_ (ge211::Rectangle{})
        , seconds_travelled (0)
        , geometry_ (geometry)
        , missiles_ ({})
        , enemies_ ({})

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


void Model::launch_ship()
{
    ship_live = true;
}


void Model::move_ship(int x)
{
    ship_.x = x;
    if(!ship_live){

    }
}

void Model::update()
{
    // TODO: your code here
    if(ship_live) {


    }
}



// Private helper

// Determines whether the ship collides with the missile
bool Model::ship_hit_() const
{

}

// Returns a pointer to a hit enemy, or nullptr if none.
void Model::find_destroy_hit_Enemy_ ()
{

}

// Removes the hit missiles. (different colors)
void Model::find_destroy_hit_Missile_ ()
{

}

//return true when the given enemy need to launch five missiles (when they reach a certain y-coordinate on the screen)
bool Model::enemy_launch_missile(Enemy &)
{

}

// Returns the ship to the starting position
void Model::reset_ship_()
{

}

// return time that has passed since the game started.
int Model::get_time_()
{

}



