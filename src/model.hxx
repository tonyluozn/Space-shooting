#pragma once

#include <ge211.hxx>

//
// Model constants:
//
const int missile_radius;
const ge211::Dimensions ship_dims;
const ge211::Dimensions enemy_dims;
const ge211::Color enemy_missile_color;
const ge211::Color ship_missile_color;
// the y-coordinate at which enemy will emit five missiles
const int enemy_launch_missile_y;

//
// Model Classes:
//
// the position of the spaceship and whether it is alive. (if it is alive, then
// it can be moved by the mouse.
struct Ship
{
    ge211::Position top_left;
    bool live;
};

// The position of enemy, its speed,
// and whether it's still there.
struct Enemy
{
    //The top-left corner
    ge211::Position top_left;
    ge211::Dimensions speed;
    bool live;

};

// The position of missile, its speed,
// and whether it's still there.
struct Missile
{
    //The top-left corner
    ge211::Position center;
    ge211::Dimensions speed;
    bool live;
    //true when missile is emitted by enemy; false when missile is emitted by the spaceship
    bool is_enemy;
};

// The whole state of the game
//
class Model
{
    //
    // Private data members
    //

    //The Enemies
    std::vector<Enemy> enemies_;

    //The missiles
    std::vector<Missile> missiles_;

    //The spaceship
    Ship ship_;

    // time travelled
    int seconds_travelled;

public:
    //
    //Public functions
    //

    //Return the Ship object
    Ship get_ship () const ;

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

