#pragma once

#include <ge211.hxx>
#include <piece.hxx>
#include <board.hxx>

class Model
{
public:
    /// Model dimensions will use `int` coordinates, as board dimensions do.
    using Dimensions = Board::Dimensions;

    /// Model positions will use `int` coordinates, as board positions do.
    using Position = Board::Position;

    /// Model rectangles will use `int` coordinates, as board rectangles do.
    using Rectangle = Board::Rectangle;

    /// Constructs a model with `size` as its rows number.
    Model(int size);

    /// Constructs a model with the given width and height.
    Model();

    /// Returns a rectangle containing all the positions of the board.
    /// This can be used to iterate over the positions.
    Rectangle board() const;


    // function on frame to set the board position to true if the game detect
    // collison.

    void on_frame();
    // update the piece to a new piece

    void update_piece();


    // return the active piece inside the board
    Piece active_piece()
    { return active_piece_; }

    void rotate_piece();

    Piece next_piece()
    { return next_piece_; }

    // check the top row of the board and actually determine if there a full
    // column of board full and return game over
    bool is_game_over();

    //gives a shadow of the current piece at the bottom of the screen, also
    // check the lowest positon that the piece can actually reach


    //check the collisions of any of the pieces going on the board

    //check if the piece can actually move in any direction and return true
    // if it can
    bool is_it_possible_move();
    void ghost();
    // add a piece to the board and update that position of the board to true.
    void lock_piece(Piece);


    //exchange the current piece if the player doesn't want it to be there if
    //
    void exchange_piece();

    //place the current piece at the very bottom position of the the board.
    void place_at_the_bottom();

    // Responsible for updating the score and checking it
    std::size_t score() const
    { return score_; }

    // Moves a piece left on left arrow press
    void move_left(Piece piece);

    // Moves a piece right on right arrow press
    void move_right(Piece piece);

    // Moves a piece down if it will not collide.
    //void move_down(Piece piece);
    void move_down();

    Piece active_piece_ = create_piece(random_piece());

    Board board_;

    std::vector<Piece> past_pieces;
    void clear_line();
    int times_swapped = 0;
    bool game_active = false;
    Piece ghost_piece = active_piece_;

    void
    hard_drop();
private:


    Piece next_piece_ = create_piece(random_piece());

    //Piece exchanged_piece_;

    //Board board_;

    std::size_t score_ = 0;

    std::size_t score_increment_ = 0;

    bool can_exchange_piece_ = true;


    bool check_collision();

    // check if any row of board is full and delete it..


    void
    update_board(std::vector<Position> posns, Piece brick);


#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
        // Test_access will be allowed to access private members of this class.

        friend struct Test_access;
#endif


    bool
    check_collision(Piece p);
    bool
    is_it_inside_board(Piece p);
    bool
    is_it_possible_move(Piece p);
    void
    move_piece_faster();

    void
    move_ghost_down();

};

/*class Model
{
public:

    /// Model dimensions will use `int` coordinates, as board dimensions do.
    using Dimensions = Board::Dimensions;

    /// Model positions will use `int` coordinates, as board positions do.
    using Position = Board::Position;

    /// Model rectangles will use `int` coordinates, as board rectangles do.
    using Rectangle = Board::Rectangle;

    /// Constructs a model with `size` as its rows number.
    Model(int size);

    /// Constructs a model with the given width and height.
    Model();

    //returns the current brick
    Piece current_piece() const
    {return current_piece_;}

    //returns the brick held in the hold
    Piece_type hold_piece() const
    {return hold_piece_;}

    //returns the brick that will come down next
    Piece_type next_piece() const
    {return next_piece_;}

    Board get_board() const
    {return board_;}

    std::size_t score() const
    {return score_;}
    /// Returns a rectangle containing all the positions of the board.
    /// This can be used to iterate over the positions.
    Rectangle board() const;

    //returns the current brick's "shadow", the lowest position it can
    //reach in its current column without overlapping another piece or going
    //over the bottom
    Piece ghost() const;

    //forcefully updates the game to place the current brick at the bottom
    //of its current column (as far as it can go) and turn the next brick
    //into the current brick
    void hard_drop();

    //switches the current brick with the brick in the hold if the player
    //can hold (determined by if the piece has already been switched out
    //for what was in the hold, i.e. you can't switch hold and current
    //back once they have been switched without changing the value of current)
    //if there is no piece in the hold, the current piece goes to the
    //hold and is replaced by the next piece
    void hold();

    //update the game by shifting the current brick down by one square and
    //turning the next brick into the current brick if the current brick
    //cannot move further down
    void tick();

    //updates the grid by setting all positions in the first position vector
    //argument to none, while setting the Brick's positions_ to brick_type_.
    void update_board(std::vector<Position>, Piece);

    bool game_over() const
    {return game_over_;}

    //returns whether or not the given Brick can exist with its current
    //positions used for determining whether a hypothetical brick after
    //a move (rotation or translation)would be allowed to exist on the board
    bool can_move(Piece&) const;

    void update_current_piece(Piece);

    // Moves a piece left on left arrow press
    void move_left(Piece piece);

    // Moves a piece right on right arrow press
    void move_right(Piece piece);

    // Moves a piece down if it will not collide.
    void move_down(Piece piece);

    // rotate a piece 90 degree to the right if in_bounds
    void rotate_cw(Piece piece);

private:

    Piece current_piece_ = create_piece(random_piece());

    Piece_type hold_piece_;

    Piece_type next_piece_;

    Board board_;

    std::size_t score_ = 0;

    std::size_t score_increment_ = 0;
    bool can_hold_ = true;

    bool game_over_ = false;

    //clears all filled lines currently on the board and appropriately deals
    //with scoring
    void clear_all_lines_();

    //clears a single line at the integer row position and does not
    //affect scoring
    void clear_line_(int);

    //returns whether or not the line at int row_number is filled and able
    //to be cleared
    bool line_is_filled_(int);

    //checks to see if the Brick will collide with any other bricks
    //returns true if the Brick has no collisions with any other pieces
    //on the grid
    bool collision_check_(Piece) const;

    //checks to see if the Brick has all positions within the bounds of
    //the game grid
    //returns true if the Brick is in bounds
    bool in_bounds_(Piece) const;

    //creates a new random brick and initializes it to the next_brick_
    Piece new_piece_();
};*/

