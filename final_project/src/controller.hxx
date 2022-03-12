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
    //void on_key(ge211::Key) override;

    // void on_frame(double) override;

    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
    //int              upd_frames_ = 0;

};