//
// Created by Neil Connatty on 2016-10-27.
//

#ifndef FLORIE_MESSENGER_H
#define FLORIE_MESSENGER_H

#include "pubnub.hpp"

namespace messaging {
    class messenger {
    public:
        /** returns null on unsuccessful start */
        pubnub::context *start_messenger();

        /** returns empty string if no message */
        std::string get_latest_message(pubnub::context *pb);
    };
}

#endif //FLORIE_MESSENGER_H
