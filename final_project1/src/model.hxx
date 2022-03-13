#pragma once

#include <ge211.hxx>
#include <piece.hxx>
#include <board.hxx>

class Model
{
public:
    /// Model dimensions will use `int` coordinates, as board dimensions do.

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


    // update the piece to a new piece



    // return the active piece inside the board
    Piece active_piece()
    { return active_piece_; }

    void rotate_piece();



    // check the top row of the board and actually determine if there a full
    // column of board full and return game over
    bool is_game_over();

    //gives a shadow of the current piece at the bottom of the screen, also
    // check the lowest positon that the piece can actually reach


    //check the collisions of any of the pieces going on the board

    //check if the piece can actually move in any direction and return true
    // if it can
    void create_ghost();
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


private:




    //Piece exchanged_piece_;

    //Board board_;

    std::size_t score_ = 0;

    std::size_t score_increment_ = 0;





    // check if any row of board is full and delete it..





#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
        // Test_access will be allowed to access private members of this class.

        friend struct Test_access;
#endif


    bool
    check_collision(Piece p);
    bool
    is_it_inside_board(Piece p);
    void
    move_piece_faster();

};
