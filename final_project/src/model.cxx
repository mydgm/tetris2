#include "model.hxx"
#include "piece.hxx"
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
/*void
Model::move_down(Piece piece)
{
    Position new_pos = {0,1};

    std::vector<ge211::Posn<int>> current_positions;

    for (auto pos: piece.get_body()) {

        pos = {pos.x + new_pos.x, pos.y+ new_pos.y};

        current_positions.push_back(pos);
    }

    piece.actual_pos_ = current_positions;
    //if (can_move(b)) {
      //  update_board(piece.get_body(), b);
        //update_current_piece(b);
    //}
}*/

void
Model::move_down()
{

    Piece next_p = active_piece_;
    for (int i = 0; i < 4; i++) {


        next_p.actual_pos_[i] =
                {active_piece_.actual_pos_[i].x,
                 active_piece_.actual_pos_[i].y + 1};


    }
    if(is_it_inside_board(next_p) && (!check_collision(next_p))){
        active_piece_ = next_p;
    }

    else{
        lock_piece(active_piece_);
        active_piece_ = create_piece(random_piece());

    }
}
void
Model::move_left(Piece piece)
{
    Piece next_p = active_piece_;
    for (int i = 0; i < 4; i++) {
        next_p.actual_pos_[i] =
                {active_piece_.actual_pos_[i].x-1,
                 active_piece_.actual_pos_[i].y};

    }
    if(is_it_inside_board(next_p)&& (!check_collision(next_p))){
        active_piece_ = next_p;
    }
}
void
Model::move_right(Piece piece)
{
    Piece next_p = active_piece_;
    for (int i = 0; i < 4; i++) {
        next_p.actual_pos_[i] =
                {active_piece_.actual_pos_[i].x+1,
                 active_piece_.actual_pos_[i].y};

    }
    if(is_it_inside_board(next_p)&&(!check_collision(next_p))){
        active_piece_ = next_p;
    }

}

void
Model::on_frame()
{   //probably need to check that my game doesn't get game over...
    Piece current = active_piece_;
    for (auto pos :current.get_body())
    {

        board_.is_occupied(pos);
    }
}

bool
Model::is_game_over()
{
    // this will always return true because we intiate the piece at the start
    // of the board so we first need to check if there is a move downward
    // that the piece can preform

    for (int i = 0; i < board_.dimensions().width; i++)
        if (board_.mboard[0][i] == 1) {
            active_piece_ = create_piece(Piece_type::neither);
            return true;
        }
    return false;
}

Piece
Model::ghost() const
{
    Piece ghost_piece = active_piece_;

    //while (is_it_possible to move)

    //for each position of ghost piece
    //(pos.y +1)

    Piece new_ghost = ghost_piece;

    // for each position of the new ghost
    // pos.y - 1
    // return new ghost
    // want the ghost piece to have the lowest possible value at the board
    //what function I can use to do that?
    return new_ghost;
}
bool
Model::check_collision(Piece p )
{
    Piece current_piece = active_piece_;

    for (auto pos: p.get_actual_body()) {
        if (board_.is_occupied(pos) == 1  || p.get_name() ==
                                            Piece_type::neither){
            return true;

    }
    }
    return false;

}


bool
Model::is_it_inside_board(Piece p)
{

    for (auto pos :p.get_actual_body()) {

        if (!board_.good_position(pos)) {

            return false;
        }
    }

    return true;
}

bool
Model::is_it_possible_move(Piece p)
{

    return is_it_inside_board(p) && check_collision(p);
}

void
Model::move_piece_faster()
{
    double v = 6;

    active_piece_.velocity *= v;
}
void
Model::rotate_piece()
{
    ///check rotate
    Piece new_p = active_piece_;
    if (new_p.get_name() == Piece_type::line) {
        for (int i = 0; i < 4; i++) {
            int intial_x = active_piece_.pos_[i].x;
            int intial_y = active_piece_.pos_[i].y;
            int real_intial_x = active_piece_.actual_pos_[i].x;
            int real_intial_y = active_piece_.actual_pos_[i].y;

            new_p.pos_[i] = {intial_y, intial_x};

            Piece::Position diff = ge211::geometry::Posn<int>(new_p
                                                                      .pos_[i].x -
                                                              intial_x,
                                                              new_p.pos_[i]
                                                                      .y -
                                                              intial_y);
           new_p.actual_pos_[i] = {active_piece_.actual_pos_[i].x +
                                            diff.x,
                                            active_piece_.actual_pos_[i].y +
                                            diff.y};
            /*int intial_x = active_piece_.pos_[i].x;
            int intial_y = active_piece_.pos_[i].y;
            int real_intial_x = active_piece_.actual_pos_[i].x;
            int real_intial_y = active_piece_.actual_pos_[i].y;

            active_piece_.pos_[i] = {intial_y, intial_x};

            Piece::Position diff = ge211::geometry::Posn<int>(active_piece_
                                                                      .pos_[i].x -
                                                              intial_x,
                                                              active_piece_.pos_[i]
                                                                      .y -
                                                              intial_y);
            active_piece_.actual_pos_[i] = {active_piece_.actual_pos_[i].x +
                                            diff.x,
                                            active_piece_.actual_pos_[i].y +
                                            diff.y};*/


        }
    }
    else if (active_piece_.get_name() == Piece_type ::square){
        //do nothing
    }
    else {
        for (int i = 0; i < 4; i++) {
            int intial_x = active_piece_.pos_[i].x;
            int intial_y = active_piece_.pos_[i].y;
            int real_intial_x = active_piece_.actual_pos_[i].x;
            int real_intial_y = active_piece_.actual_pos_[i].y;

            new_p.pos_[i] = {2- intial_y, intial_x};

            Piece::Position diff = ge211::geometry::Posn<int>(new_p
                                                                      .pos_[i].x -
                                                              intial_x,
                                                              new_p.pos_[i]
                                                                      .y -
                                                              intial_y);
            new_p.actual_pos_[i] = {active_piece_.actual_pos_[i].x +
                                    diff.x,
                                    active_piece_.actual_pos_[i].y +
                                    diff.y};
        }


            /*for (int i = 0; i < 4; i++) {
                int intial_x = active_piece_.pos_[i].x;
                int intial_y = active_piece_.pos_[i].y;
                int real_intial_x = active_piece_.actual_pos_[i].x;
                int real_intial_y = active_piece_.actual_pos_[i].y;

                active_piece_.pos_[i] = {2 - intial_y, intial_x};

                Piece::Position diff = ge211::geometry::Posn<int>(active_piece_
                                                                          .pos_[i]
                                                                          .x -
                                                                  intial_x,
                                                                  active_piece_.pos_[i]
                                                                          .y -
                                                                  intial_y);
                active_piece_.actual_pos_[i] = {active_piece_.actual_pos_[i].x +
                                                diff.x,
                                                active_piece_.actual_pos_[i].y +
                                                diff.y};
            }*/

        }
    if(is_it_inside_board(new_p) && (!check_collision(new_p))){
        active_piece_ = new_p;
    }


    }

void
Model::lock_piece(Piece piece)
{

  //*past_pieces.push_back(piece);
    for( auto pos: piece.get_actual_body()){
        board_.mboard[pos.y][pos.x] = 1;
        board_.tboard[pos.y][pos.x] = piece.get_name();
    }


}



void
Model::clear_line()
{
    for (int j = 19; j >=0 ; j--) {
        int sum_row = 0;
        for (int i = 0; i < board_.dimensions().width; i++) {
            if (board_.mboard[j][i] == 1) {
                sum_row++;
            }
        }
        if (sum_row == 10) {
            board_.delete_line(j);


        }
    }
}

void Model::exchange_piece()
    {
        active_piece_ = create_piece(random_piece());
    }

void
Model::update_piece()
{
active_piece_ = next_piece_;

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
