//
// Created by Neil Connatty on 2016-10-27.
//

#include "messenger.h"
#include "pubnub.hpp"
#include "formatting_helper.h"
#include <exception>
#include <string>
#include <thread>

#define PUBLISH_KEY "pub-c-ffee06f7-78b5-483c-b800-fae8f3a67f0c"
#define SUBSCRIBE_KEY "sub-c-3dc063c8-9bc0-11e6-814f-0619f8945a4f"
#define CHANNEL "bcch"

using namespace pubnub;
using namespace messaging;

pubnub::context* messenger::start_messenger()
{  try {
        pubnub::context *pb = new pubnub::context(PUBLISH_KEY, SUBSCRIBE_KEY);
        pubnub_res res;

        res = pb->subscribe(CHANNEL).await();
        if (PNR_OK == res) {
            std::cout << "messenger::start_messenger Successfully subscribed" << std::endl;
            return pb;
        } else {
            std::cout << "messenger::start_messenger Error on subscribe with code: " << res << std::endl;
            delete pb;
            return 0;
        }
    } catch (std::exception &exc) {
        std::cout << "messenger::start_messenger exception" << exc.what() << std::endl;
        return 0;
    }
}

void get_message (pubnub::context *pb, std::function<void(pubnub::context &, pubnub_res)> callback)
{
    pb->subscribe(CHANNEL).then(callback);
}

void messenger::get_latest_message (pubnub::context *pb, std::function<void(pubnub::context &, pubnub_res)> callback)
{
    std::thread t(get_message, pb, callback);
    t.detach();
}