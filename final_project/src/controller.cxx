#include "controller.hxx"

using namespace ge211;

static const double initial_velocity = 2;

Controller::Controller()
        : Controller(10,20)
{ }

Controller::Controller(int width, int height)
        : model_(height),
          view_(model_)

{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}
double max_frame = 20;
double update_frame = 0;



void Controller::on_frame(double)
{
    if(!model_.is_game_over()) {
        Piece p = model_.active_piece_;
        if (update_frame >= max_frame) {
            model_.move_down();
            update_frame = 0;

        }
        update_frame += 1;
    }

}

void Controller::on_key(ge211::Key key)
{

    if (!model_.is_game_over()) {

        if (key == key.left()) {
            model_.move_left(model_.active_piece());

        }
        if (key == key.right()) {
            model_.move_right(model_.active_piece());
        }
        if (key == key.down()) {
            model_.move_down();
        }
        if (key == key.up()) {
            model_.rotate_piece();

        }
    }
}
void Controller::on_key_up(ge211::Key key) {
    if (key == ge211::Key::down()){
        model_.active_piece_.velocity = initial_velocity;
    }
}

View::Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

