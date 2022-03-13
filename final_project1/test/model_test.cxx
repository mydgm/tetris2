#include "model.hxx"
#include <catch.hxx>


TEST_CASE("Check Rotate and Check Move Down")
{
    Model b = Model();
    //Check that function moves the active piece down the screen
    b.active_piece_ = create_piece(Piece_type::square);
    Piece intial_p = b.active_piece_;
    //checking move down function
    b.move_down();
    b.move_down();
    b.move_down();
    CHECK_FALSE(b.active_piece_.actual_pos_ == intial_p.actual_pos_);
    //checks that the rotation function does nothing to a square
    //square shouldn't rotate
    Piece p_square = b.active_piece_;
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_square.actual_pos_);
    //line cant rotate on the when its all the way against the way
    //in this case the line is against the top wall
    b.active_piece_ = create_piece(Piece_type::line);
    //cant flip at top or sides
    Piece p_line = b.active_piece_;
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_line.actual_pos_);
    b.move_down();
    b.move_down();
    b.move_down();
    b.move_down();
    b.move_down();
    b.move_down();
    //test the whole cw loop of rotation for line
    CHECK_FALSE(b.active_piece_.actual_pos_ == p_line.actual_pos_);
    p_line.actual_pos_ = {{5,5},{5,6},{5,7},{5,8}};
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_line.actual_pos_);
    p_line.actual_pos_ = {{4,6},{5,6},{6,6},{7,6}};
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_line.actual_pos_);
    p_line.actual_pos_ = {{5,5},{5,6},{5,7},{5,8}};
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_line.actual_pos_);
    p_line.actual_pos_ = {{4,6},{5,6},{6,6},{7,6}};
    b.rotate_piece();



    //check t flipped rotation
    b.active_piece_ = create_piece(Piece_type::t_flipped);
    Piece p_t = b.active_piece_;
    b.move_down();
    b.move_down();
    b.move_down();
    CHECK_FALSE(b.active_piece_.actual_pos_ == p_t.actual_pos_);
    p_t.actual_pos_ = {{6,4},{5,3},{5,4},{5,5}};
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_t.actual_pos_);
    p_t.actual_pos_ = {{5,5},{6,4},{5,4},{4,4}};
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_t.actual_pos_);
    p_t.actual_pos_ = {{4,4},{5,5},{5,4},{5,3}};
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_t.actual_pos_);
    p_t.actual_pos_ = {{5,3},{4,4},{5,4},{6,4}};
    b.rotate_piece();
    CHECK(b.active_piece_.actual_pos_ == p_t.actual_pos_);


}

TEST_CASE("Check Game Over")
{
    //testing when a position in the top row is occupied then the game is over
    //aka pos.y of a piece = 0
    Model b = Model();
    bool gg = b.is_game_over();
    CHECK(gg == false);
    CHECK(b.board_.mboard[19][2] == 0);
    b.active_piece_ = create_piece(Piece_type::line);
    b.active_piece_.actual_pos_ = {{5,19},{5,18},{5,17},{5,16}};
    b.lock_piece(b.active_piece_);
    bool gg2 = b.is_game_over();
    CHECK(gg2 == false);
    CHECK(b.board_.mboard[19][5] == 1);
    b.active_piece_ = create_piece(Piece_type::line);
    b.active_piece_.actual_pos_ = {{5,15},{5,14},{5,13},{5,12}};
    b.lock_piece(b.active_piece_);
    bool gg3 = b.is_game_over();
    CHECK(gg3 == false);
    b.active_piece_ = create_piece(Piece_type::line);
    b.active_piece_.actual_pos_ = {{5,11},{5,10},{5,9},{5,8}};
    b.lock_piece(b.active_piece_);
    b.active_piece_ = create_piece(Piece_type::line);
    b.active_piece_.actual_pos_ = {{5,7},{5,6},{5,5},{5,4}};
    b.lock_piece(b.active_piece_);
    b.active_piece_ = create_piece(Piece_type::line);
    b.active_piece_.actual_pos_ = {{5,3},{5,2},{5,1},{5,0}};
    b.lock_piece(b.active_piece_);
    bool gg4 = b.is_game_over();
    CHECK(gg4 == true);
}

TEST_CASE("Piece Move")
{
    Model b = Model();
    //testing that the piece can move left fine by comparing it to its
    // initial position
    b.active_piece_ = create_piece(Piece_type::line);
    Piece copy_p = b.active_piece_;
    b.move_left(b.active_piece_);
    CHECK_FALSE(b.active_piece_.actual_pos_ == copy_p.actual_pos_);
    b.move_left(b.active_piece_);
    b.move_left(b.active_piece_);
    b.move_left(b.active_piece_);
    //continue to move piece left
    CHECK_FALSE(b.active_piece_.actual_pos_ == copy_p.actual_pos_);
    copy_p.actual_pos_ = b.active_piece_.actual_pos_;
    b.move_left(b.active_piece_);
    //active piece shouldn't be able to move left anymore
    CHECK(b.active_piece_.actual_pos_ == copy_p.actual_pos_);
    //checking that the piece can move right
    b.move_right(b.active_piece_);
    CHECK_FALSE(b.active_piece_.actual_pos_ == copy_p.actual_pos_);
}

TEST_CASE("Ghost piece")
{
    Model b = Model();
    //ghost piece should be initialized to the same positions and piece type
    // as the active piece
    CHECK(b.ghost_piece.actual_pos_ == b.active_piece_.actual_pos_);
    CHECK(b.ghost_piece.get_name() == b.active_piece_.get_name());
    //this function should move the ghost piece all the waay down
    //thus the ghost piece and actual piece shoudln't have the same pos
    b.create_ghost();
    CHECK_FALSE(b.ghost_piece.actual_pos_ == b.active_piece_.actual_pos_);
    //function sets the position of the piece equal to the position of the
    // ghost piece
    b.place_at_the_bottom();
    CHECK(b.ghost_piece.actual_pos_ == b.active_piece_.actual_pos_);

}
