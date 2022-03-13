#pragma once

#include "model.hxx"
#include "view.hxx"
#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    explicit Controller();

    Controller(int width, int height);

protected:
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;
    void on_frame(double) override;
    void on_key(ge211::Key key) override;

private:

    View view_;
    Model model_;




};