#include "model.hxx"
#include <catch.hxx>


TEST_CASE("example test (TODO: replace this)")
{
    Model b = Model();
    std::vector<Piece::Position> initial_p = b.active_piece_.actual_pos_;
    b.active_piece_.actual_pos_[1] = {b.active_piece_.actual_pos_[1].x+1, b
                                      .active_piece_.actual_pos_[1].y+1};

    b.move_down();

    CHECK(initial_p == b.active_piece_.actual_pos_);

}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
