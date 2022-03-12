#include "piece.hxx"
#include <ge211.hxx>
#include <iostream>
#include <vector>


Piece::Piece(Piece_type type, std::vector<Piece::Position>& pos,
             std::vector<Piece::Position>& actual_pos)
        :
        type_(type),
        pos_(pos),
        actual_pos_(actual_pos)


{}

ge211::geometry::Posn<int>
Piece::get_top_left(Piece p)
{
    return top_left_;
}

ge211::geometry::Posn<int>
Piece::move_top_left(Piece::Position move)
{

    ge211::geometry::Posn<int> new_tl = ge211::geometry::Posn<int>(0, 0);
    new_tl.x = top_left_.x + move.x;
    new_tl.y = top_left_.y + move.y;
    return (new_tl);
}





std::vector<ge211::geometry::Posn<int>>
Piece::get_body() const
{
    return pos_;
}

Piece_type
Piece::get_name() const
{
    return type_;
}

std::vector<Piece::Position>
Piece::get_actual_body() const
{
    return actual_pos_;
}



Piece create_piece(Piece_type type)
{

    if (type == Piece_type::square) {

        std::vector<ge211::Posn<int>>
                pos =
                {{0, 0},
                 {1, 0},
                 {0, 1},
                 {1, 1}};
        std::vector<ge211::Posn<int>>
        actual_pos ={
                {4,0},
                 {5, 0},
                 {4, 1},
                 {5, 1}};

        return Piece(type, pos,actual_pos);

    }
    else if (type == Piece_type::line) {
        std::vector<Piece::Position>
                pos =
                {{0, 1},
                 {1, 1},
                 {2, 1},
                 {3, 1}};
        std::vector<Piece::Position>
                actual_pos =
                {{4, 0},
                 {5, 0},
                 {6, 0},
                 {7, 0}};
        return Piece(type, pos,actual_pos);

    }
    else if (type == Piece_type::t_flipped) {
        std::vector<Piece::Position>
                pos =
                {{1,0},
                 {0, 1},
                 {1, 1},
                 {2, 1}};
        std::vector<Piece::Position>
        actual_pos =
                {{5,0},
                 {4, 1},
                 {5, 1},
                 {6, 1}};

        return Piece(type, pos,actual_pos);

    }
    else if (type == Piece_type::z) {

        std::vector<Piece::Position>
                pos =
                {{0, 0},
                 {1, 0},
                 {1, 1},
                 {2, 1}};
        std::vector<Piece::Position>
                actual_pos =
                {{4, 0},
                 {5, 0},
                 {5, 1},
                 {6, 1}};

        return Piece(type, pos,actual_pos);

    }
    else if (type == Piece_type::L_shape) {
        std::vector<Piece::Position>
                pos =
                {{2, 0},
                 {0, 1},
                 {1, 1},
                 {2, 1}};
        std::vector<Piece::Position>
                actual_pos =
                {{6, 0},
                 {4, 1},
                 {5, 1},
                 {6, 1}};
        return Piece(type, pos,actual_pos);
    }
    std::vector<Piece::Position>
            pos =
            {{0, 0},
             {0, 0},
             {0, 0},
             {0, 0}};
    std::vector<Piece::Position>
            actual_pos =
            {{0, 0},
             {0, 0},
             {0, 0},
             {0, 0}};
    return Piece(type, pos,actual_pos);
}



Piece_type random_piece()
{
    ge211::Random_source<int> number(1, 5);
    int random = number.next_between(1,5);

    if (random == 1){
        return Piece_type::L_shape;
    }
    else if (random == 2){
        return Piece_type::line;
    }
    else if (random == 3){
        return Piece_type::z;
    }
    else if (random == 4){
        return Piece_type::square;
    }
    else {
        return Piece_type::t_flipped;
    }
}
void
Piece::rotate_piece()
{

    if (get_name() == Piece_type::line) {

        /*for (int i = 0; i < 4; i++) {
            Piece::Position diff = ge211::geometry::Posn<int>(copy_p.get_body()
                                                              [i].x - get_body()[i].x, copy_p.get_body()[i].y - p
                    .get_body()[i].y);
            copy_p.pos_[i] = {p.pos_[i].y, p.pos_[i].x};

            copy_p.actual_pos_[i] = {p.get_actual_body()[i].x + diff.x,
                                           p.get_actual_body()[i].y + diff.y};

        }*/
    } else {

        for (int i = 0; i < 4; i++) {
            int intial_x = pos_[i].x;
            int intial_y = pos_[i].y;
            int real_intial_x = actual_pos_[i].x;
            int real_intial_y = actual_pos_[i].y;
            pos_[i] = {2 - intial_y, intial_x};
            Piece::Position diff = ge211::geometry::Posn<int>(pos_[i].x -
                                                              intial_x,
                                                              pos_[i].y -
                                                              intial_y);
            actual_pos_[i] = {actual_pos_[i].x + diff.x, actual_pos_[i].y +
                                                         diff.y};

        }

    }
}

