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
    int time ()
    { return model.seconds_travelled ; }
};

TEST_CASE("launch and play ship (shooting missiles)")
{
    int s = 0;
    Model m;
    Test_access t{m};
    CHECK(m.get_ship().top_left().x == m.get_geometry().
    scene_dims.width - m.get_geometry().scene_dims.width/2);
    CHECK(m.get_ship().top_left().y == m.get_geometry().
    scene_dims.height- m.get_geometry().bottom_margin -
    m.get_geometry().ship_dims.height );
    CHECK(m.get_live() == false);
    m.move_ship(100);
    //move_ship doesn't work when the ship is not alive
    CHECK(m.get_ship().top_left().x == m.get_geometry().scene_dims.width
    - m.get_geometry().scene_dims.width/2);
    m.launch_ship();
    CHECK(m.get_live() == true);
    m.move_ship(100);
    CHECK(m.get_ship().x == 100);
    // test ship shooting missiles
    s = 1;
    m.update(s);
    CHECK(t.missiles()[0] ==
    Missile(m.get_geometry(), false,
            {m.get_ship().top_left().x + m.get_ship().width / 2,
             m.get_ship().top_left().y - 2 *
             m.get_geometry().missile_radius}));
    s--;
    m.update(s);
    s--;
    m.update(s);
    s--;
    m.update(s);
    s--;
    m.update(s);
    // update five times at the launching time(s==1), launch five missiles.
    CHECK(t.missiles().size()==5);
    m.update(s);
    // update but s != 1, so missiles not launch.
    CHECK(t.missiles().size()==5);


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
    m.update(s);
    // ship is dead, the screen is all clear
    CHECK(t.missiles().empty());
    CHECK(t.enemies().empty());
    CHECK_FALSE(m.get_live());

    //Enemy missile hits right side
    Missile edge1 = {m.get_geometry(),true,{15,200}};
    edge1.velocity_.width = -20;
    t.missiles().push_back(edge1);
    //Player missile hits right side
    Missile edge2 = {m.get_geometry(),false,{15,200}};
    edge2.velocity_.width = -20;
    t.missiles().push_back(edge2);
    //Enemy missile hits left side
    Missile edge3 = {m.get_geometry(),true,
                     {m.get_geometry().scene_dims.width-15, 200}};
    edge3.velocity_.width = 20;
    t.missiles().push_back(edge3);
    //Player missile hits left side
    Missile edge4 = {m.get_geometry(),false,
                     {m.get_geometry().scene_dims.width-15, 200}};
    edge4.velocity_.width = 20;
    t.missiles().push_back(edge4);
    //Ship missile hits top
    Missile edge5 = {m.get_geometry(),false,
                     {200,15}};
    edge5.velocity_.height = -20;
    t.missiles().push_back(edge5);
    //Enemy missile hits bottom
    Missile edge6 = {m.get_geometry(),true,
                     {10, m.get_geometry().scene_dims.height-15}};
    edge6.velocity_.height = 20;
    t.missiles().push_back(edge6);
    m.launch_ship();

    t.enemies().clear();
    s = 0;
    CHECK(m.get_missiles().size()==6);
    m.update(s);
    CHECK(m.get_missiles().size()==0);

}

TEST_CASE("enemy fire missile and hit ship"){
    int s = 0;
    Model m;
    Test_access t{m};
    CHECK_FALSE(m.get_live());

    m.launch_ship();
    CHECK(m.get_live());

    // Enemy fires at a given height
    Enemy obs = {m.get_geometry(),{100, 99}};
    t.enemies().push_back(obs);
    CHECK(m.get_missiles().size() == 0);
    m.update(s);
    CHECK(m.get_missiles().size() == 5);

    //Enemy hits ship
    CHECK(m.get_live());
    t.enemies().clear();
    obs = {m.get_geometry(),{258, 695}};
    t.enemies().push_back(obs);
    CHECK(obs.hits_ship({256, 698}));
    CHECK(m.get_live());
    CHECK(m.get_missiles().size() == 5);
    m.update(s);
    CHECK(m.get_enemies().empty());
    CHECK(m.get_missiles().empty());
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
    a.velocity_.width = 17;
    b.velocity_.width = -17;
    CHECK(t.missiles().empty());
    t.missiles().push_back(a);
    t.missiles().push_back(b);
    m.update(s);
    CHECK(t.missiles()[0].velocity_.width < 0);
    CHECK(t.missiles()[1].velocity_.width > 0);
    CHECK(t.missiles()[0].velocity_.height ==
    m.get_geometry().missile_velocity0.height);
    CHECK(t.missiles()[1].velocity_.height ==
    m.get_geometry().missile_velocity0.height);

    //when both missiles are from spaceship both are false
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
    Missile a = {m.get_geometry(),false, {90,100}};
    Missile b = {m.get_geometry(), true, {90,75}};
    m.launch_ship();
    t.missiles().clear();
    t.missiles().push_back(a);
    t.missiles().push_back(b);
    m.update(s);
    //both missiles disappear
    CHECK(t.missiles().empty());
}