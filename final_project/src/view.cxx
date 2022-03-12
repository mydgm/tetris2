#include "view.hxx"
using namespace ge211;


static int const score_font_size = 22;
Dims<int> const offset_window = {25, 0};
int const grid_size = 40;
View::View(Model const& model)
        : model_(model),
          board_tile{{36,36},
                     ge211::Color::white()}

{ }

void
View::draw(ge211::Sprite_set& set)
{
    //draw_score_(set);

    for (auto pos: model_.board()) {

        Position current_tile = board_to_screen(pos);

        set.add_sprite(board_tile, current_tile,0.5);
    }

    /* for (auto pos : model_.ghost().get_body())
     {
         set.add_sprite(ghost_cell, board_to_screen(pos), 1);
     }
     for (int row = 0; row <model_.board().dimensions().height; row++) {
         for (int col = 0; col < model_.board().dimensions().width; col++) {
             Position pos = {col,row};
             Piece_type type = model_.get_board().get_piece_type2(pos);
             if (type == Piece_type::T_shape) {
                 set.add_sprite(T_piece, board_to_screen(Position{col,row})
                         ,2);
             }
             else if (type == Piece_type::square) {
                 set.add_sprite(square_piece, board_to_screen(Position{col,
                                                                       row})
                         ,2);
             }
             else if (type == Piece_type::L_shapped) {
                 set.add_sprite(L_piece, board_to_screen(Position{col,row})
                         ,2);
             }
             else if (type == Piece_type::Z_shapped) {
                 set.add_sprite(Z_piece, board_to_screen(Position{col,row})
                         ,2);
             }
             else if (type == Piece_type::I_shaped) {
                 set.add_sprite(I_piece, board_to_screen(Position{col,row})
                         ,2);
             }
         }
     }*/

}

/*void
View::draw_score_(ge211::Sprite_set& set)
{
    if (model_.score() != previous_score_) {
        ge211::Text_sprite::Builder builder(score_font_);
        builder << model_.score();
        score_sprite_.reconfigure(builder);
    }
    set.add_sprite(score_, board_to_screen({10, 2}), 10);
    set.add_sprite(score_sprite_, board_to_screen({10, 3}), 10);
}*/

View::Dimensions View::initial_window_dimensions() const
{
    return grid_size * model_.board().dimensions() + offset_window * 3;
}

std::string View::initial_window_title() const
{
    return "Tetris";
}


View::Position
View::board_to_screen(Model::Position logical) const
{
    Position empty_one ={logical.x * grid_size,logical.y * grid_size};
    return empty_one;
}