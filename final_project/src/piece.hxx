#pragma once
#include <ge211.hxx>
#include <vector>
#include <iostream>

enum class Piece_type
{
    square, //good
    t_flipped, //good
    z,
    line, //good
    L_shape,
    neither
};

class Piece{

public:

    //declaring position as ge211::posn<int>
    using Position = ge211::Posn<int>;
    using Dimensions = ge211::Dims<int>;

    //return the top left (middle posn at the board)
    Position get_top_left (Piece p) ;
    //return the piece type
    Piece_type get_name() const;

    // a vector of the current positions of piece blocks
    std::vector<Position> get_body() const;
    std::vector<Position> get_actual_body() const;

    //constructor for a piece that has specific type and on_board
    // position
    Piece(Piece_type, std::vector<Position>&);

    int piece_intial_x_coord () const
    {return get_body()[0].x;}

    int piece_intial_y_coord () const
    {return get_body()[0].y;}

private:
    enum Piece_type type_;
    Position top_left_ = {4,0};
    std::vector<Position> actual_pos_;
    std::vector<Position> pos_;

};

Piece_type random_piece();

Piece create_piece(Piece_type type);

Piece rotate_piece(Piece p);
