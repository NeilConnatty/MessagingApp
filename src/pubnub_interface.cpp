//
// Created by Neil Connatty on 2016-11-04.
//

#include "pubnub_interface.h"


pubnub_interface::pubnub_interface (): m_pn(PUBLISH_KEY, SUBSCRIBE_KEY)
{
    m_pn.set_blocking_io(pubnub::non_blocking);
}

pubnub_interface::~pubnub_interface ()
{
}

void pubnub_interface::on_publish (pubnub::context &pn, pubnub_res res)
{
    if (PNR_OK == res) {
        std::cout << pn.last_publish_result() << std::endl;
    } else {
        std::cout << "Publish request failed with error code: " << res << std::endl;
    }
}

void pubnub_interface::publish_input (std::string input)
{
    m_helper.publish(m_pn, m_formatter.format_message(input), INPUT_CHANNEL, pubnub_interface::on_publish);
}

void pubnub_interface::send_message (std::string msg)
{
    m_helper.publish(m_pn, m_formatter.format_message(msg), MSG_CHANNEL, pubnub_interface::on_publish);
}

void pubnub_interface::show_image ()
{
    std::cout << "show_image()" << std::endl;
    publish_input("show image");
}

void pubnub_interface::hide_image ()
{
    std::cout << "hide_image()" << std::endl;
    publish_input("hide image");
}

void pubnub_interface::zoom_image()
{
    std::cout << "zoom_image()" << std::endl;
    publish_input("zoom image");
}

void pubnub_interface::reload_image ()
{
    std::cout << "reload_image()" << std::endl;
    publish_input("reload image");
}

void pubnub_interface::upload_image ()
{
    std::cout << "upload_image()" << std::endl;
    publish_input("upload image");
}

void pubnub_interface::scroll_left ()
{
    std::cout << "scroll_left()" << std::endl;
    publish_input("scroll left");
}

void pubnub_interface::scroll_right ()
{
    std::cout << "scroll_right()" << std::endl;
    publish_input("scroll right");
}

void pubnub_interface::flip_view ()
{
    std::cout << "flip_view()" << std::endl;
    publish_input("flip view");
}

void pubnub_interface::hide_or_show_image ()
{
    std::cout << "hide_or_show_image()" << std::endl;
    publish_input("hide or show image");
}

void pubnub_interface::toggle_function ()
{
    std::cout << "toggle_function()" <<std::endl;
    publish_input("toggle function");
}