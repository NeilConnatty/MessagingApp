//
// Created by Neil Connatty on 2016-10-24.
//

#include "pub_sub_helper.h"
#include <thread>
using namespace pubnub;
using namespace std;
using namespace messaging;

void sub (context* pn, string channel, function<void(context &, pubnub_res)> func)
{
    pn->subscribe(channel).then(func);
}

void sub_on_thread (string publish_key, string subscribe_key, string channel, function<void(context &, pubnub_res)> func)
{
    context *pn = new context(publish_key, subscribe_key);
    pn->set_blocking_io(pubnub::non_blocking);
    pubnub_res res = pn->subscribe(channel).await();
    if (res == PNR_OK) {
        for (;;) {
            thread t(sub, pn, channel, func);
            t.join();
        }
    } else {
        cout << "initial subscribe unsuccessful, error code: " << res << endl;
    }
    delete pn;
}

void pub_sub_helper::subscribe(string publish_key, string subscribe_key, string channel,
                             function<void(context &, pubnub_res)> func)
{
    thread t(sub_on_thread, publish_key, subscribe_key, channel, func);
    t.detach();
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
