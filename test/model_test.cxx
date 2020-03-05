#include "model.hxx"
#include <catch.hxx>


struct Test_access
{
    Model & model ;
    std::vector<Enemy> & enemies ()
    { return model.enemies_ ; }
    std::vector<Missile> & missiles ()
    { return model.missiles_ ; }
    Ship & ship ()
    { return model.ship_ ; }
    int time ()
    { return model.seconds_travelled ; }
};


TEST_CASE("launch ship")
{
    Model m;
    Test_access t{m};
    //assume scene width 400 for now

    CHECK(m.get_ship().top_left == 200 - ship_dims.width/2);
    CHECK(m.get_ship().y == ship_dims.height);
    CHECK(m.get_ship().live == false);
    m.launch_ship();
    CHECK(m.get_ship().live == true);

}
TEST_CASE("move ship")
{
    Model m;
    Test_access t{m};
    CHECK(m.get_ship().top_left == 200 - ship_dims.width/2);
    m.move_ship(100);
    CHECK(m.get_ship().x == 100);
}

TEST_CASE("missiles hit ship")
{
    Model m;
    Test_access t{m};
    m.launch_ship();
    CHECK_FALSE(m.get_ship().live);
    m.launch_ship();
    CHECK(m.get_ship().live);
    Missile obs = {t.ship().top_left,0,0, true};
    t.missiles().clear();
    t.missiles().push_back(obs);
    m.update();
    CHECK_FALSE(m.get_ship().live);
}

TEST_CASE("enemy hit ship"){
    Model m;
    Test_access t{m};
    CHECK_FALSE(m.get_ship().live);
    m.launch_ship();
    CHECK(m.get_ship().live);
    Enemy obs = {t.ship().top_left,1,1, true};
    t.missiles().clear();
    t.enemies().push_back(obs);
    m.update();
    CHECK_FALSE(m.get_ship().live);
}

TEST_CASE("missiles with same color collides")
{
    Model m;
    Test_access t{m};
    //When both missiles are from enemy
    Missile a = {{100,100},{1,1},true,true};
    Missile b = {{100,100},{-1,1},true,true};
    t.missiles().clear();
    t.missiles().push_back(a);
    t.missiles().push_back(b);
    m.update();
    CHECK(t.missiles()[0].speed.width == -1);
    CHECK(t.missiles()[1].speed.width == 1);

    //when both missiles are from spaceship  both are false
    a = {{100,100},{1,1},true,false};
    b = {{100,100},{-1,1},true,false};
    t.missiles().clear();
    t.missiles().push_back(a);
    t.missiles().push_back(b);
    m.update();
    CHECK(t.missiles()[0].speed.width == -1);
    CHECK(t.missiles()[1].speed.width == 1);

}

TEST_CASE("Missiles with different color collides")
{
    Model m;
    Test_access t{m};
    //one from enemy and one from spaceship
    Missile a = {{100,100},{1,1},true,true};
    Missile b = {{100,100},{-1,1},true,false};
    t.missiles().clear();
    t.missiles().push_back(a);
    t.missiles().push_back(b);
    m.update();
    //both missiles disappear
    CHECK(t.missiles().empty());
}