//
// Created by Neil Connatty on 2016-10-24.
//

#include "pub_sub_helper.h"
using namespace pubnub;
using namespace std;
using namespace messaging;

void pub_sub_helper::subscribe(context &pn, string channel,
                             function<void(context &, pubnub_res)> func)
{
    pn.subscribe(channel).then(func);
}

void pub_sub_helper::publish (context &pn, string msg, string channel,
                           function<void(context &, pubnub_res)> func)
{
    pn.publish(channel, msg).then(func);
}

void pub_sub_helper::history(pubnub::context &pn, std::string channel,
                             std::function<void(pubnub::context &, pubnub_res)> func)
{
    pn.history(channel, 100).then((func));
}
