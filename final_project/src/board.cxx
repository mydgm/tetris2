#include "board.hxx"



using namespace ge211;

Board::Board(Dimensions dims)
        : dims_(dims)
{
    for (int i = 0 ; i < dims_.width ; i++) {

        for (int j = 0; j < dims_.height ; j++) {

            mboard[j][i] = 0;
        }
    }
    if (dims_.width < 2 || dims_.height < 2) {
        throw ge211::Client_logic_error("Board::Board: dims too small");
    }

    if (dims_.width > 10 ||
        dims_.height > 20) {
        throw ge211::Client_logic_error("Board::Board: dims too large");
    }
}


Board::Dimensions
Board::dimensions() const
{
    return dims_;
}

bool
Board::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}

Board::Rectangle
Board::all_positions() const
{
    return Rectangle::from_top_left(the_origin, dims_);
}


int
Board::is_occupied(Position where) {

    return mboard[where.y][where.x];
}