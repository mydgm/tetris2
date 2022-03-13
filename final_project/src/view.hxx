#pragma once
#include "ge211.hxx"
#include "model.hxx"

class View
{
public:

    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    View::Position board_to_screen(Model::Position logical) const;

private:

    Model const& model_;

    // Draws the score.
    // void draw_score_(ge211::Sprite_set&);

    ge211::Rectangle_sprite const square_piece;
    ge211::Rectangle_sprite const T_piece;
    ge211::Rectangle_sprite const L_piece;
    ge211::Rectangle_sprite const Z_piece;
    ge211::Rectangle_sprite const I_piece;
    ge211::Rectangle_sprite const ghost_cell;

    ge211::Rectangle_sprite const board_tile;
    //std::size_t const previous_score_;  // currently rendered in score_sprite_
    //ge211::Font const score_font_;
    //ge211::Text_sprite  score_sprite_;
    //ge211::Text_sprite const score_;

};