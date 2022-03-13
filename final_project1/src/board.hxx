#pragma once
#include <ge211.hxx>
#include <vector>
#include <piece.hxx>
#include <iostream>
#include <unordered_map>


class Board{
public:

    // Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    int is_occupied(Position where);

    explicit Board(Dimensions dims);
    int mboard[20][10];
    Piece_type tboard[20][10];

std::vector<Piece_type> past_pieces;

private:

    //
    // PRIVATE DATA MEMBERS

    Dimensions dims_;


public:
    /// Returns the same `Dimensions` value passed to the
    /// constructor.
    void delete_line(int row);
    Dimensions dimensions() const;

    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;

    /// Returns a rectangle containing all the positions of the board. This
    /// can be used to iterate over the positions:
    Rectangle all_positions() const;




#ifdef CS211_TESTING
// When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif
};
