#pragma once
#include <ge211.hxx>
#include <vector>
#include <iostream>

enum class Piece_type
{
    square,
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


    Piece(
            Piece_type type,
            std::vector<Piece::Position>& pos,
            std::vector<Piece::Position>& actual_pos);
    //return the top left (middle posn at the board)

    //return the piece type
    Piece_type get_name() const;

    // a vector of the current positions of piece blocks
    std::vector<Position> get_actual_body() const;

    //constructor for a piece that has specific type and on_board
    // position




    std::vector<Position> actual_pos_;
    std::vector<Position> pos_;
    double velocity;

private:
    enum Piece_type type_;


};

Piece_type random_piece();

Piece create_piece(Piece_type type);
