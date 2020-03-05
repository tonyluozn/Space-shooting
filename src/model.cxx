
#include "model.hxx"

Model::Model(Geometry const& geometry)
        : ship_live (false)
        , seconds_travelled (0)
        , geometry_ (geometry)

{


}

// Freebie.
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





