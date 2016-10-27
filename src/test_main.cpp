//
// Created by Neil Connatty on 2016-10-27.
//

#include <string>
#include "pubnub.hpp"
#include "messenger.h"

pubnub::context* context = 0;
messaging::messenger* messenger = 0;

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

    return 1;
}

/** return empty string on no new messages or on error */
std::string retrieve_new_message ()
{
    std::cout << "retrieveNewMessage() called" << std::endl;
    std::string str = messenger->get_latest_message(context);
    return str;
}


void stop_messenger ()
{
    delete messenger;
    delete context;
}


int main ()
{
    if (initialize_messenger()) {
        std::cout << retrieve_new_message() << std::endl;
        stop_messenger();
        return 1;
    } else {
        return 0;
    }
}