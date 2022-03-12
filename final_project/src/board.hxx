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

private:

    //
    // PRIVATE DATA MEMBERS

    Dimensions dims_;
    int mboard[20][10];

public:
    /// Returns the same `Dimensions` value passed to the
    /// constructor.
    Dimensions dimensions() const;
    void delete_line();

    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;

    /// Returns a rectangle containing all the positions of the board. This
    /// can be used to iterate over the positions:
    Rectangle all_positions() const;


};
