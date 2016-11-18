//
// Created by Neil Connatty on 2016-11-04.
//

#ifndef NITTY_PUBNUB_INTERFACE_H
#define NITTY_PUBNUB_INTERFACE_H

#include "pub_sub_helper.h"
#include "pubnub.hpp"
#include "formatting_helper.h"

/// BCCH app keys
#define PUBLISH_KEY "pub-c-ffee06f7-78b5-483c-b800-fae8f3a67f0c"
#define SUBSCRIBE_KEY "sub-c-3dc063c8-9bc0-11e6-814f-0619f8945a4f"
#define MSG_CHANNEL "bcch"
#define INPUT_CHANNEL "input"

class pubnub_interface
{
public:
    pubnub_interface ();
    ~pubnub_interface ();

    void send_message (std::string msg);
    void show_image ();
    void hide_image ();
    void zoom_image ();
    void reload_image ();
    void upload_image ();
    void scroll_left ();
    void scroll_right ();
    void flip_view ();
    void hide_or_show_image ();
    void toggle_function ();

private:
    static void on_publish (pubnub::context &pn, pubnub_res res);
    void publish_input (std::string input);

private:
    pubnub::context m_pn;
    messaging::pub_sub_helper m_helper;
    messaging::formatting_helper m_formatter;
};


#endif //NITTY_PUBNUB_INTERFACE_H
