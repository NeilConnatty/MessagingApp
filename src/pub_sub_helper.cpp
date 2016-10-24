//
// Created by Neil Connatty on 2016-10-24.
//

#include "pub_sub_helper.h"

void pub_sub_helper::subscribe(pubnub::context &pn, std::string channel,
                             std::function<void(pubnub::context &, pubnub_res)> func)
{
    pn.subscribe(channel).then(func);
}

void pub_sub_helper::publish (pubnub::context &pn, std::string msg, std::string channel,
                           std::function<void(pubnub::context &, pubnub_res)> func)
{
    pn.publish(channel, msg).then(func);
}
