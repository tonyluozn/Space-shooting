
#pragma once

#include "model.hxx"
#include <ge211.hxx>

extern ge211::Color const ship_color, missile_color, enemy_color,
ship_missile_color;

struct Ui : ge211::Abstract_game
{

    explicit Ui(Model&);

    ge211::Dimensions initial_window_dimensions() const override;

    void draw(ge211::Sprite_set&) override;

    void on_key(ge211::Key) override;


    void on_mouse_move(ge211::Position) override;

    void on_frame(double dt) override;


    Model& model_;


    ge211::Rectangle_sprite    const
            ship_sprite_    {model_.get_geometry().ship_dims, ship_color};


    ge211::Rectangle_sprite const
            enemy_sprite_  {model_.get_geometry().enemy_dims, enemy_color};


    ge211::Circle_sprite const
            missile_sprite_   {model_.get_geometry().missile_radius,
                               missile_color};

    ge211::Text_sprite time_sprite_
            {"0", ge211::Font("sans.ttf", 24)};

    ge211::Circle_sprite const
            ship_missile_sprite_
            {model_.get_geometry().missile_radius, ship_missile_color };
};
