#pragma once

#include <ge211.hxx>
#include <vector>
#include "enemy.hxx"
#include "missile.hxx"

//
// Model constants:
//

// the y-coordinate at which enemy will emit five missiles
const int enemy_launch_missile_y = 0;

//
// Model Classes:
//


// The whole state of the game
//
class Model
{
    //
    // Private data members
    //

    Geometry const     geometry_;
    //The Enemies
    std::vector<Enemy> enemies_;

    //The missiles
    std::vector<Missile> missiles_;

    //The spaceship
    ge211::Rectangle ship_;

    // live
    bool ship_live;

    // time travelled
    int seconds_travelled;
    ge211::Timer timer_;
public:
    //
    //Public functions
    //
    Model(Geometry const& geometry = Geometry());
    //Return the Ship object
    ge211::Rectangle get_ship () const ;

    //Return all missiles's state
    std::vector < Missile > const & get_missiles () const ;

    //Return all enemies' state
    std::vector < Enemy > const & get_enemies () const ;

    bool get_live() const;

    Geometry get_geometry() const ;

    // Updates the model state for one time step
    void update(int&);

    void enemy_fire(Enemy&);
    // move the x-coordinate of the spaceship to x
    void move_ship(int x);

    void ship_launch_missile();

    bool check_enemy(Enemy&);

    void generate_enemy();

    // set the live of the ship to true
    void launch_ship();


    // return time that has passed since the game started.
    const std::string & get_time_() const ;

private:
    //
    // Helper functions
    //

    // Determines whether the ship collides with the missile
    bool ship_hit_() const;


    // Returns the ship to the starting position
    void reset_ship_();



    // Test access3
    friend struct Test_access ;

};

