//
// Created by Neil Connatty on 2016-11-10.
//

#ifndef NITTY_WIDGET_MANAGER_H
#define NITTY_WIDGET_MANAGER_H

#include "pubnub_interface.h"
#include "BCCH_app.h"
#include <SFGUI/Widgets.hpp>
#include <SFGUI/SFGUI.hpp>

class widget_manager
{
public:
    void init_window (sfg::Desktop &desktop, int screen_width, int screen_height);

private:
    void send_message ();
    sfg::Button::Ptr init_button (std::string name, std::function<void()> delegate);
    sfg::Box::Ptr create_box (sfg::Box::Orientation orientation);
    sfg::Box::Ptr create_vertical_box ();
    sfg::Box::Ptr create_horizontal_box ();
    void init_messages_frame ();
    void init_images_frame ();
    void init_take_photo_frame ();
    void init_view_frame ();
    void init_widgets ();
    sfg::Window::Ptr create_window (sfg::Box::Ptr content, int screen_width, int screen_height);

private:
    const unsigned int FONT_SIZE = 40;
    const unsigned int FRAME_FONT_SIZE = 30;

    pubnub_interface m_pn_interface;
    sfg::Entry::Ptr m_message_entry;
    std::vector<sfg::Widget::Ptr> widgets;

};


#endif //NITTY_WIDGET_MANAGER_H
