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
    explicit Model(Geometry const& geometry = Geometry());

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

public:
    //
    //Public functions
    //

    //Return the Ship object
    ge211::Rectangle get_ship () const ;

    //Return all missiles's state
    std::vector < Missile > const & get_missiles () const ;

    //Return all enemies' state
    std::vector < Enemy > const & get_enemies () const ;

    // Updates the model state for one time step
    void update();

    // move the x-coordinate of the spaceship to x
    void move_ship(int x);

    // set the live of the ship to true
    void launch_ship();



private:
    //
    // Helper functions
    //

    // Determines whether the ship collides with the missile
    bool ship_hit_() const;

    // Returns a pointer to a hit enemy, or nullptr if none.
    Enemy* find_hit_Enemy_ () const ;

    // Removes the indicated enemy.
    void destroy_hit_Enemy_ ( Enemy &);

    // Removes the hit missiles. (different colors)
    void find_destroy_hit_Missile_ ();

    //return true when the given enemy need to launch five missiles (when they reach a certain y-coordinate on the screen)
    bool enemy_launch_missile(Enemy &);

    // Returns the ship to the starting position
    void reset_ship_();

    // return time that has passed since the game started.
    int get_time_();


    // Test access3
    friend struct Test_access ;

};

