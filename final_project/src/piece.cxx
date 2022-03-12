#include "piece.hxx"
#include <ge211.hxx>
#include <iostream>
#include <vector>

static const double initial_velocity = 8;

ge211::geometry::Posn<int> top_left_=  {4,0};

Piece::Piece(Piece_type type, std::vector<Piece::Position>& pos,
             std::vector<Piece::Position>& actual_pos)
        :velocity(initial_velocity),
         pos_(pos),
         type_(type),
        actual_pos_(actual_pos)
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

        std::vector<ge211::Posn<int>> actual_pos;

        actual_pos.push_back({top_left_});
        actual_pos.push_back({top_left_.x +1 , 0});
        actual_pos.push_back({top_left_.x, top_left_.y + 1});
        actual_pos.push_back({top_left_.x + 1, top_left_.y +1});

    }
    else if (type == Piece_type::line) {
        std::vector<Piece::Position>
                pos =
                {{0, 1},
                 {1, 1},
                 {2, 1},
                 {3, 1}};
        std::vector<Piece::Position> actual_pos;

        actual_pos.push_back({top_left_});
        actual_pos.push_back({top_left_.x + 1, top_left_.y});
        actual_pos.push_back({top_left_.x + 2, top_left_.y});
        actual_pos.push_back({top_left_.x + 3, top_left_.y});
        return Piece(type, pos,actual_pos);

    }

    else if (type == Piece_type::t_flipped) {
        std::vector<Piece::Position>
                pos =
                {{1,1},
                 {0, 2},
                 {1, 2},
                 {2, 2}};

        std::vector<Piece::Position> actual_pos;

        actual_pos.push_back({top_left_});
        actual_pos.push_back({top_left_.x + 1, top_left_.y + 1});
        actual_pos.push_back({top_left_.x , top_left_.y + 2});
        actual_pos.push_back({top_left_.x + 2, top_left_.y + 2});

        return Piece(type, pos,actual_pos);

    }
    else if (type == Piece_type::z) {

        std::vector<Piece::Position>
                pos =
                {{0, 0},
                 {1, 0},
                 {1, 1},
                 {2, 1}};
        std::vector<Piece::Position> actual_pos;
        actual_pos.push_back({top_left_});
        actual_pos.push_back({top_left_.x + 1, top_left_.y });
        actual_pos.push_back({top_left_.x + 1 , top_left_.y + 1});
        actual_pos.push_back({top_left_.x + 2, top_left_.y + 1});

        return Piece(type, pos,actual_pos);

    }
    else if (type == Piece_type::L_shape) {
        std::vector<Piece::Position>
                pos =
                {{2, 0},
                 {0, 1},
                 {1, 1},
                 {2, 1}};
        std::vector<Piece::Position> actual_pos ;
        actual_pos.push_back({top_left_});
        actual_pos.push_back({top_left_.x + 1, top_left_.y});
        actual_pos.push_back({top_left_.x + 2, top_left_.y});
        actual_pos.push_back({top_left_.x + 2, top_left_.y + 1});

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

