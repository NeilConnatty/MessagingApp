//
// Created by Neil Connatty on 2016-11-04.
//

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "pubnub_interface.h"

#ifndef NITTY_BCCH_WINDOW_H
#define NITTY_BCCH_WINDOW_H

class BCCH_app
{
public:
    void Run ();
    void send_message ();

private:
    void init_widgets (pubnub_interface &pn_interface);

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
    sfg::Button::Ptr m_send_message_button;
    sfg::Button::Ptr m_show_image_button;
    sfg::Button::Ptr m_hide_image_button;
    sfg::Button::Ptr m_zoom_image_button;
    sfg::Button::Ptr m_reload_image_button;
};


#endif //NITTY_BCCH_WINDOW_H
