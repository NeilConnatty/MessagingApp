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


void pubnub_interface::send_message (std::string msg)
{
    m_helper.publish(m_pn, m_formatter.format_message(msg), MSG_CHANNEL, pubnub_interface::on_publish);
}

void pubnub_interface::show_image ()
{
    m_helper.publish(m_pn, m_formatter.format_message("show image"), INPUT_CHANNEL, pubnub_interface::on_publish);
}

void pubnub_interface::hide_image ()
{
    m_helper.publish(m_pn, m_formatter.format_message("hide image"), INPUT_CHANNEL, pubnub_interface::on_publish);
}

void pubnub_interface::zoom_image()
{
    m_helper.publish(m_pn, m_formatter.format_message("zoom image"), INPUT_CHANNEL, pubnub_interface::on_publish);
}

void pubnub_interface::reload_image ()
{
    m_helper.publish(m_pn, m_formatter.format_message("reload image"), INPUT_CHANNEL, pubnub_interface::on_publish);
}

void pubnub_interface::upload_image ()
{
    m_helper.publish(m_pn, m_formatter.format_message("upload image"), INPUT_CHANNEL, pubnub_interface::on_publish);
}