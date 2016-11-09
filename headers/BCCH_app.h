//
// Created by Neil Connatty on 2016-11-04.
//

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "pubnub_interface.h"

#ifndef NITTY_BCCH_WINDOW_H
#define NITTY_BCCH_WINDOW_H

#define FOOTPEDAL_LEFT 12
#define FOOTPEDAL_MIDDLE 74
#define FOOTPEDAL_RIGHT 63

class BCCH_app
{
public:
    void Run ();
    void send_message ();

private:
    void init_widgets (pubnub_interface &pn_interface);
    sfg::Button::Ptr init_button (std::string name, std::function<void()> delegate);
    void handle_events (sf::RenderWindow &render_window, sf::Event &event);
    void render_screen (sf::RenderWindow &render_window);

private:
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 900;
    const unsigned int FONT_SIZE = 40;

    sfg::SFGUI m_sfgui;
    sfg::Desktop m_desktop;
    pubnub_interface m_pn_interface;

    sfg::Box::Ptr m_box;
    sfg::Window::Ptr m_window;

    sfg::Label::Ptr m_label;
    sfg::Entry::Ptr m_entry;
    std::vector<sfg::Button::Ptr> buttons;
};


#endif //NITTY_BCCH_WINDOW_H
