#include "controller.hxx"

using namespace ge211;

int level_ = 1;
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

View::Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}