#include "model.hxx"
#include <cmath>

Model::Model()
        : Model(20)
{}

Model::Model(int size)
        : board_({10, size})
{}

Model::Rectangle
Model::board() const
{
    return Rectangle::from_top_left(Position{0,0},board_.dimensions());
}
/*
Model::Model()
        : Model(20)
{}
Model::Model(int size)
        : board_({10, size}),
          hold_piece_(Piece_type::neither)
{
    next_piece_ = random_piece();
}
Model::Rectangle
Model::board() const
{
    return Rectangle::from_top_left(Position{0,0},board_.dimensions());
}
void Model::hard_drop()
{
    update_board(current_piece_.get_body(), ghost());
    current_piece_ = ghost();
    clear_all_lines_();
    current_piece_ = create_piece(next_piece_);
    update_board(current_piece_.get_body(), current_piece_);
    next_piece_ = random_piece();
    can_hold_ = true;
}
Piece Model::ghost() const
{
    Piece ghost_piece = current_piece_;
    while (can_move(ghost_piece)) {
        ghost_piece = move_down_ghost(ghost_piece, 1);
    }
    return move_down_ghost(ghost_piece, -1);
}
void Model::hold()
{
    if (can_hold_)
    {
        Piece_type temp_type = hold_piece_;
        hold_piece_ = current_piece_.get_type();
        if (temp_type != Piece_type::neither) {
            Piece b = create_piece(temp_type);
            update_board(current_piece_.get_body(), b);
            current_piece_ = b;
        }
        else {
            Piece b = create_piece(next_piece_);
            update_board(current_piece_.get_body(), b);
            current_piece_ = b;
            next_piece_ =  random_piece();
        }
        can_hold_ = false;
    }
}
void Model::tick()
{
    if (!game_over()) {
        update_board(current_piece_.get_body(), current_piece_);
        Piece temp_brick = move_down_ghost(current_piece_, 1);
        if (can_move(temp_brick)) {
            update_board(current_piece_.get_body(), temp_brick);
            current_piece_ = temp_brick;
        } else {
            clear_all_lines_();
            current_piece_ = create_piece(next_piece_);
            if (can_move(current_piece_)) {
                update_board(current_piece_.get_body(), current_piece_);
                next_piece_ = random_piece();
                can_hold_ = true;
            }
            else
                game_over_ = true;
        }
    }
}
void Model::clear_all_lines_()
{
    size_t rows_cleared = 0;
    for (int i=0; i <board_.dimensions().height; i++) {
        if (line_is_filled_(i)) {
            clear_line_(i);
            rows_cleared++;
        }
    }
    if (rows_cleared == 1) {
        score_increment_ = score_increment_ + 10;
        score_ =  score_increment_;
    }
    else if (rows_cleared > 1) {
        score_increment_ = (score_increment_ + rows_cleared) * 5;
        score_ =  score_increment_;
    }
}
void Model::clear_line_(int row)
{
    for (int i = 0; i < board_.dimensions().width; i++) {
        for (int j = row; j > 0; j--) {
            board_.set_piece_type(Position{i,j}, board_.get_piece_type
                                                               (Position{i, j-1}));
        }
        board_.set_piece_type(Position{0,i}, false);
    }
}
bool Model::line_is_filled_(int row)
{
    for (int i = 0; i < board_.dimensions().width; i++) {
        if (board_.get_piece_type(Position{i, row})
            == false) {
            return false;
        }
    }
    return true;
}
bool Model::can_move(Piece& brick) const
{
    return in_bounds_(brick) && collision_check_(brick);
}
bool Model::collision_check_(Piece brick) const
{
    for (Position pos : brick.get_body()) {
        if (board_.get_piece_type(pos) != false) {
            if (!current_piece_.has_position(pos)) {
                //board_.get_piece_type(pos) != false||
                return false;
            }
        }
    }
    return true;
}
bool Model::in_bounds_(Piece brick) const
{
    for (Position pos : brick.get_body()) {
        if (!board_.good_position(pos)) {
            return false;
        }
    }
    return true;
}
void Model::update_current_piece(Piece brick)
{
    current_piece_ = brick;
}
void Model::update_board(std::vector<Position> posns, Piece brick)
{
    for (Position pos: posns) {
        board_.set_piece_type(pos, false);
    }
    for (Position pos :brick.get_body()) {
        board_.set_piece_type(pos, true);
    }
}
void
Model::move_left(Piece piece)
{
    Position new_pos = {-1,0};
    std::vector<ge211::Posn<int>> current_positions;
    for (auto pos: piece.get_body()) {
        pos = {pos.x + new_pos.x, pos.y};
        current_positions.push_back(pos);
    }
    Piece b = Piece(piece.get_type(), current_positions);
    if (can_move(b)) {
        update_board(piece.get_body(), b);
        update_current_piece(b);
    }
}
void
Model::move_right(Piece piece)
{
    Position new_pos = {1,0};
    std::vector<ge211::Posn<int>> current_positions;
    for (auto pos: piece.get_body()) {
        pos = {pos.x + new_pos.x, pos.y};
        current_positions.push_back(pos);
    }
    Piece b = Piece(piece.get_type(), current_positions);
    if (can_move(b)) {
        update_board(piece.get_body(), b);
        update_current_piece(b);
    }
}
void
Model::move_down(Piece piece)
{
    Position new_pos = {0,1};
    std::vector<ge211::Posn<int>> current_positions;
    for (auto pos: piece.get_body()) {
        pos = {pos.x + new_pos.x, pos.y};
        current_positions.push_back(pos);
    }
    Piece b = Piece(piece.get_type(), current_positions);
    if (can_move(b)) {
        update_board(piece.get_body(), b);
        update_current_piece(b);
    }
}
void
Model::rotate_cw(Piece current_piece)
{
    if (current_piece.get_type() == Piece_type::square) {
        current_piece = Piece(current_piece);
    }
    std::vector<ge211::Posn<int>> rotated_positions;
    ge211::Posn<int> adjusted_posn = {0,0};
    int start_pos_x = current_piece.piece_intial_x_coord();
    int start_pos_y = current_piece.piece_intial_y_coord();
    for (auto pos: current_piece.get_body()) {
        adjusted_posn.x = pos.x - start_pos_x;
        adjusted_posn.y = pos.y - start_pos_y;
        adjusted_posn = {-1 * adjusted_posn.y + start_pos_x,
                         adjusted_posn.x+ start_pos_y};
        rotated_positions.push_back(adjusted_posn);
    }
    Piece b = Piece(current_piece.get_type(), rotated_positions);
    if (can_move(b)) {
        update_board(current_piece.get_body(), b);
        update_current_piece(b);
    }
}
 */