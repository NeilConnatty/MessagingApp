//
// Created by Neil Connatty on 2016-10-27.
//

#include <string>
#include "pubnub.hpp"
#include "messenger.h"
#include <thread>

pubnub::context* context = 0;
messaging::messenger* messenger = 0;

void displayMessage (std::string msg)
{
    std::cout << msg << std::endl;
}

void on_subscribe (pubnub::context &pb, pubnub_res res)
{
    if (PNR_OK == res) {
        displayMessage(pb.get());
        messenger->get_latest_message(&pb, on_subscribe);
    } else {
        std::cout << "Subscribe Request failed" << std::endl;
    }
}

/** return false on unsuccessful initialize */
int initialize_messenger ()
{
    messenger = new messaging::messenger;
    if (messenger == 0) {
        std::cout << "error creating messenger" << std::endl;
        return 0;
    }

    context = messenger->start_messenger();
    if (context == 0) {
        std::cout << "error creating context" << std::endl;
        delete messenger;
        return  0;
    }
    messenger->get_latest_message(context, on_subscribe);
    return 1;
}


void stop_messenger ()
{
    delete messenger;
    delete context;
}


int main ()
{
    if (initialize_messenger()) {
        for (;;) {}
    } else {
        return 0;
    }
}