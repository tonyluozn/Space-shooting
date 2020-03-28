// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ui.hxx"
///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
ge211::Color const ship_color    {255, 127, 127};
ge211::Color const missile_color  {255, 0, 0};
ge211::Color const enemy_color   {100, 100, 100};
ge211::Color const ship_missile_color   {0, 100, 0};
int s = 1;
///
/// VIEW FUNCTIONS
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Ui::Ui(Model& model)
        : model_(model)
{ }

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.get_geometry().scene_dims;
}

void Ui::draw(ge211::Sprite_set& sprites) {
    // TODO: your code here
    sprites.add_sprite(ship_sprite_, model_.get_ship().top_left());

    if (!model_.get_missiles().empty()) {
        for (Missile shot: model_.get_missiles()) {
            if (shot.is_enemy) {
                sprites.add_sprite(missile_sprite_, shot.top_left());
            } else {
                sprites.add_sprite(ship_missile_sprite_, shot.top_left());
            }
        }
    }
    if (!model_.get_enemies().empty()) {
        for (Enemy enemy: model_.get_enemies()) {
            sprites.add_sprite(enemy_sprite_, enemy.top_left_);
        }
    }

    time_sprite_.reconfigure(ge211::Text_sprite::Builder(sans)<<model_.get_time_());
    sprites.add_sprite(time_sprite_, {480,10});
}



///
/// CONTROLLER FUNCTIONS
///

void Ui::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();

    // TODO: your code here
    if (key == ge211::Key::code(' ')) {
        if(!model_.get_live()) {
            model_.launch_ship();
        }
    }
}

void Ui::on_frame(double d)
{
    s++;
    model_.update(s);
    if(s>=35){
        s=0;
    }
}


void Ui::on_mouse_move(ge211::Position position)
{
    // TODO: your code he
    model_.move_ship(position.x);
}

