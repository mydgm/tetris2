#include "view.hxx"
using namespace ge211;


static int const score_font_size = 22;
Dims<int> const offset_window = {25, 0};
int const grid_size = 40;
View::View(Model const& model)
        : model_(model),
          square_piece{{36,36}, ge211::Color::medium_red
                  ()},
          T_piece{{36,36}  ,ge211::Color(255,255,0)
          },
          L_piece{{36,36},ge211::Color::medium_blue()},
          Z_piece{{36,36},ge211::Color::medium_cyan()},
          I_piece{{36,36},ge211::Color::medium_green()},
          ghost_cell{{36,36}, ge211::Color(160,160,
                                           160)},
          board_tile{{36,36},
                     ge211::Color::white()}

{ }

void
View::draw(ge211::Sprite_set& set)
{
    //draw_score_(set);

    for (auto pos: model_.board()) {

        Position current_tile = board_to_screen(pos);

        set.add_sprite(board_tile, current_tile, 0);
    }

    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < 10; i++) {
            Piece_type pt = model_.board_.tboard[j][i];
            if (pt == Piece_type::t_flipped) {
                set.add_sprite(T_piece, board_to_screen({i, j}), 2);
            } else if (pt == Piece_type::square) {
                set.add_sprite(square_piece, board_to_screen({i, j}), 2);
            } else if (pt == Piece_type::L_shape) {
                set.add_sprite(L_piece, board_to_screen({i, j}), 2);
            } else if (pt == Piece_type::z) {
                set.add_sprite(Z_piece, board_to_screen({i, j}), 2);
            } else if (pt == Piece_type::line) {
                set.add_sprite(I_piece, board_to_screen({i, j}), 2);
            }
        }
    }
    for (Piece p: model_.past_pieces) {

        Piece_type pt = p.get_name();
        for (auto pos: p.get_actual_body()) {
            if (pt == Piece_type::t_flipped) {
                set.add_sprite(T_piece, board_to_screen(pos), 2);
            } else if (pt == Piece_type::square) {
                set.add_sprite(square_piece, board_to_screen(pos), 2);
            } else if (pt == Piece_type::L_shape) {
                set.add_sprite(L_piece, board_to_screen(pos), 2);
            } else if (pt == Piece_type::z) {
                set.add_sprite(Z_piece, board_to_screen(pos), 2);
            } else if (pt == Piece_type::line) {
                set.add_sprite(I_piece, board_to_screen(pos), 2);
            }
        }
    }
    Piece_type type = model_.active_piece_.get_name();
    for (auto pos1: model_.active_piece_.get_actual_body()) {
        if (type == Piece_type::t_flipped) {
            set.add_sprite(T_piece, board_to_screen(pos1), 2);
        } else if (type == Piece_type::square) {
            set.add_sprite(square_piece, board_to_screen(pos1), 2);
        } else if (type == Piece_type::L_shape) {
            set.add_sprite(L_piece, board_to_screen(pos1), 2);
        } else if (type == Piece_type::z) {
            set.add_sprite(Z_piece, board_to_screen(pos1), 2);
        } else if (type == Piece_type::line) {
            set.add_sprite(I_piece, board_to_screen(pos1), 2);
        }
        Piece_type type2 = model_.ghost_piece.get_name();
        for (auto pos2: model_.ghost_piece.get_actual_body()) {
            if (type2 == Piece_type::t_flipped) {
                set.add_sprite(ghost_cell, board_to_screen(pos2), 1);
            } else if (type2 == Piece_type::square) {
                set.add_sprite(ghost_cell, board_to_screen(pos2), 1);
            } else if (type2 == Piece_type::L_shape) {
                set.add_sprite(ghost_cell, board_to_screen(pos2), 1);
            } else if (type2 == Piece_type::z) {
                set.add_sprite(ghost_cell, board_to_screen(pos2), 1);
            } else if (type2 == Piece_type::line) {
                set.add_sprite(ghost_cell, board_to_screen(pos2), 1);
            }
        }

    }
}

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
