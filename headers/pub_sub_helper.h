//
// Created by Neil Connatty on 2016-10-24.
//

#ifndef FLORIE_PUBSUBHELPER_H
#define FLORIE_PUBSUBHELPER_H

#include <pubnub.hpp>

namespace messaging
{
    class pub_sub_helper
    {
    public:
        void subscribe (std::string publish_key, std::string subscribe_key, std::string channel, std::function<void(pubnub::context &, pubnub_res)> func);
        void publish (pubnub::context &pn, std::string msg, std::string channel, std::function<void(pubnub::context &, pubnub_res)> func);
        void history (pubnub::context &pn, std::string channel, std::function<void(pubnub::context &, pubnub_res)> func);
    };
}

#endif //FLORIE_PUBSUBHELPER_H
