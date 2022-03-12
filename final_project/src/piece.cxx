#include "piece.hxx"
#include <ge211.hxx>
#include <iostream>
#include <vector>

Piece::Piece(Piece_type type, std::vector<Piece::Position>& pos)
        :
        type_(type),
        pos_(pos)

{}

ge211::geometry::Posn<int>
Piece::get_top_left(Piece p)
{
   return top_left_;
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


Piece create_piece(Piece_type type)
{

    if (type == Piece_type::square) {

        std::vector<ge211::Posn<int>>
                pos =
                {{0, 0},
                 {1, 0},
                 {0, 1},
                 {1, 1}};

        return Piece(type, pos);

    }
    else if (type == Piece_type::line) {
        std::vector<Piece::Position>
                pos =
                {{0, 1},
                 {1, 1},
                 {2, 1},
                 {3, 1}};
        return Piece(type, pos);

    }
    else if (type == Piece_type::t_flipped) {
        std::vector<Piece::Position>
                pos =
                {{1,1},
                 {0, 2},
                 {1, 2},
                 {1, 2}};

        return Piece(type, pos);

    }
    else if (type == Piece_type::z) {

        std::vector<Piece::Position>
                pos =
                {{0, 0},
                 {1, 0},
                 {1, 1},
                 {2, 1}};

        return Piece(type, pos);

    }
    else if (type == Piece_type::L_shape) {
        std::vector<Piece::Position>
                pos =
                {{2, 0},
                 {0, 1},
                 {1, 1},
                 {2, 1}};
        return Piece(type, pos);
    }
    std::vector<Piece::Position>
            pos =
            {{0, 0},
             {0, 0},
             {0, 0},
             {0, 0}};
    return Piece(type, pos);
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


Piece rotate_piece(Piece p)
{
    Piece copy_p = p;
    if (p.get_name() == Piece_type::line){
        int i = 0;
        for (auto pos : p.get_body() ) {
            copy_p.get_body()[i] = {pos.y, pos.x};
            Piece::Position diff = ge211::geometry::Posn<int>(copy_p.get_body()
                    [i].x - p.get_body()[i].x, copy_p.get_body()[i].y - p
                    .get_body()[i].y);
            copy_p.get_actual_body()[i] = {p.get_actual_body()[i].x + diff.x,
                                           p.get_actual_body()[i].y + diff.y};



            i++;

        }
    }
    else {
        int i  = 0;
        for (auto pos : p.get_body() ){
            copy_p.get_body()[i] = {2-pos.y, pos.x};
            Piece::Position diff = ge211::geometry::Posn<int>(copy_p.get_body()
                                                              [i].x - p.get_body()[i].x, copy_p.get_body()[i].y - p
                    .get_body()[i].y);
            copy_p.get_actual_body()[i] = {p.get_actual_body()[i].x + diff.x,
                                           p.get_actual_body()[i].y + diff.y};
            i++ ;

        }
    }


    return copy_p;
}
