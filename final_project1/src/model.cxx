#include "model.hxx"
#include "piece.hxx"


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
        next_p = create_piece(random_piece());
        if (check_collision(next_p)){
            game_active = false;
        }
        lock_piece(active_piece_);
        active_piece_ = next_p;
        ghost_piece   = active_piece_;


    }

}


void Model::create_ghost()
{

    Piece copy_p = ghost_piece;
    while (is_it_inside_board(copy_p) && (!check_collision(copy_p))) {
        for (int i = 0; i < 4; i++) {

            copy_p.actual_pos_[i].y++;


        }

    }
    for (int i = 0; i < 4; i++) {

        copy_p.actual_pos_[i].y--;


    }

    ghost_piece.actual_pos_ = copy_p.actual_pos_;



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
        for (int i = 0; i < 4; i++) {
            ghost_piece.actual_pos_[i] =
                    {ghost_piece.actual_pos_[i].x-1,
                     ghost_piece.actual_pos_[i].y};

        }

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
        for (int i = 0; i < 4; i++) {
            ghost_piece.actual_pos_[i] =
                    {ghost_piece.actual_pos_[i].x+1,
                     ghost_piece.actual_pos_[i].y};

        }
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
            game_active =false;
            active_piece_ = create_piece(Piece_type::neither);
            ghost_piece = active_piece_;
            return true;
        }
    return false;
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



void
Model::move_piece_faster()
{
    double v = 6;

    active_piece_.velocity *= v;
}
void
Model::rotate_piece()
{
    Piece new_p = active_piece_;
    if (new_p.get_name() == Piece_type::line) {
        for (int i = 0; i < 4; i++) {
            int intial_x = active_piece_.pos_[i].x;
            int intial_y = active_piece_.pos_[i].y;
            int real_intial_x = active_piece_.actual_pos_[i].x;
            int real_intial_y = active_piece_.actual_pos_[i].y;

            new_p.pos_[i] = {intial_y, intial_x};

            Piece::Position diff = ge211::geometry::Posn<int>(new_p.pos_[i].x -
                    intial_x,new_p.pos_[i].y -intial_y);
           new_p.actual_pos_[i] = {active_piece_.actual_pos_[i].x +diff.x,
                                   active_piece_.actual_pos_[i].y +diff.y};

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

            Piece::Position diff = ge211::geometry::Posn<int>(new_p.pos_[i].x -
                    intial_x,new_p.pos_[i].y -intial_y);
            new_p.actual_pos_[i] = {active_piece_.actual_pos_[i].x + diff.x,
                                    active_piece_.actual_pos_[i].y + diff.y};
        }



        }
    if(is_it_inside_board(new_p) && (!check_collision(new_p))){
        active_piece_ = new_p;
        ghost_piece = active_piece_;
    }


    }

void
Model::lock_piece(Piece piece)
{

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
void
Model::place_at_the_bottom()
{
    active_piece_.actual_pos_ = ghost_piece.actual_pos_;
}

void Model::exchange_piece()
    {
        active_piece_ = create_piece(random_piece());
        times_swapped ++;
        ghost_piece = active_piece_;
    }



