
#include "piece.hxx"
#include <ge211.hxx>
#include <vector>


Piece::Piece(Piece_type type, std::vector<Piece::Position>& pos,
             std::vector<Piece::Position>& actual_pos)
        :
        actual_pos_(actual_pos),
        pos_(pos),
        type_(type)

{}

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

