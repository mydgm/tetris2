#pragma once

#include <ge211.hxx>
#include <piece.hxx>
#include <board.hxx>

class Model{
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

private:

    Board board_;

};