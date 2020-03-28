#include "model.hxx"
#include <catch.hxx>
#include "iostream"


struct Test_access
{
    Model & model ;
    std::vector<Enemy> & enemies ()
    { return model.enemies_ ; }
    std::vector<Missile> & missiles ()
    { return model.missiles_ ; }
    //Ship & ship ()
    //{ return model.ship_ ; }
    int time ()
    { return model.seconds_travelled ; }
};


TEST_CASE("launch and play ship")
{
    int s = 0;
    Model m;
    Test_access t{m};
    //assume scene width 400 for now

    CHECK(m.get_ship().top_left().x == m.get_geometry().scene_dims.width - m.get_geometry().scene_dims.width/2);
    //std::cout << m.get_ship().top_left().x << "  " << m.get_ship().top_left().y;
    CHECK(m.get_ship().top_left().y == m.get_geometry().scene_dims.height- m.get_geometry().bottom_margin - m.get_geometry().ship_dims.height );
    CHECK_FALSE(m.get_live());
    m.move_ship(100);
    //move_ship doesn't work when the ship is not alive
    CHECK(m.get_ship().top_left().x == m.get_geometry().scene_dims.width - m.get_geometry().scene_dims.width/2);
    m.launch_ship();
    CHECK(m.get_live());
    m.move_ship(100);
    CHECK(m.get_ship().x == 100);
    m.ship_launch_missile();


}

TEST_CASE("missiles hit ship")
{
    int s = 0;
    Model m;
    Test_access t{m};
    m.launch_ship();
    CHECK(m.get_live());
    // ship at (256, 698)
    Missile obs = {m.get_geometry(),true,{10,10}};
    t.missiles().clear();
    t.missiles().push_back(obs);
    m.update(s);
    CHECK(m.get_live());
    t.missiles().clear();
    obs = {m.get_geometry(),true,{256,690}};
    t.missiles().push_back(obs);
    CHECK(m.get_live());
    //std::cout<<"before update, it is" <<t.missiles()[0].top_left().x<<","<<t.missiles()[0].top_left().y;

    m.update(s);
    CHECK(t.missiles().empty());
    // after update, the enemy's missile hit the ship
    CHECK_FALSE(m.get_live());


}

TEST_CASE("enemy hit ship"){
    int s = 0;
    Model m;
    Test_access t{m};
    CHECK_FALSE(m.get_live());
    m.launch_ship();
    CHECK(m.get_live());
    Enemy obs = {m.get_geometry(),{100, 100}};
    t.enemies().push_back(obs);
    m.update(s);
    CHECK(m.get_live());
    t.enemies().clear();
    obs = {m.get_geometry(),{258, 695}};
    t.enemies().push_back(obs);
    CHECK(obs.hits_ship({256, 698}));
    CHECK(m.get_live());
    m.update(s);
    CHECK(m.get_enemies().empty());
    CHECK_FALSE(m.get_live());

}

TEST_CASE("missiles with same color collides")
{
    int s = 0;
    Model m;
    Test_access t{m};
    m.launch_ship();
    //When both missiles are from enemy
    Missile a = {m.get_geometry(), true, {85,100}};
    Missile b = {m.get_geometry(), true, {115,100}};
    Missile e = {m.get_geometry(), true, {100,115}};
    a.velocity_.width = 17;
    b.velocity_.width = -17;
    e.velocity_.height = 20;
    CHECK(t.missiles().empty());
    //t.missiles().clear();
    t.missiles().push_back(a);
    t.missiles().push_back(b);
    t.missiles().push_back(e);
    CHECK(t.missiles().size() == 3);
    std::cout<<"before update, it is" <<t.missiles()[0].top_left().x<<","<<t.missiles()[0].top_left().y<<" and "<< t.missiles()[1].top_left().x<<","<<t.missiles()[1].top_left().y;
    m.update(s);
    std::cout<<"after update, it is" <<t.missiles()[0].top_left().x<<","<<t.missiles()[0].top_left().y<<" and "<< t.missiles()[1].top_left().x<<","<<t.missiles()[1].top_left().y;
    CHECK(t.missiles()[0].velocity_.width < 0);
    CHECK(t.missiles()[1].velocity_.width > 0);

    //when both missiles are from spaceship  both are false
    Missile c = {m.get_geometry(),false,{85,200}};
    Missile d = {m.get_geometry(),false,{115,200}};
    c.velocity_.width = 17;
    d.velocity_.width = -17;
    t.missiles().clear();
    t.missiles().push_back(c);
    t.missiles().push_back(d);
    m.update(s);
    CHECK(t.missiles()[0].velocity_.width == 17);
    CHECK(t.missiles()[1].velocity_.width == -17);

}

TEST_CASE("Missiles with different color collides")
{
    int s = 0;
    Model m;
    Test_access t{m};
    //one from enemy and one from spaceship
    Missile a = {m.get_geometry(),true, {100,100}};
    Missile b = {m.get_geometry(),true, {100,100}};
    t.missiles().clear();
    t.missiles().push_back(a);
    t.missiles().push_back(b);
    m.update(s);
    //both missiles disappear
    CHECK_FALSE(t.missiles().empty());
}