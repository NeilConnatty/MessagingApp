//
// Created by Neil Connatty on 2016-10-27.
//

#include "messenger.h"
#include "pubnub.hpp"
#include "message_formatting_helper.h"
#include <exception>
#include <string>

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
        } else {
            std::cout << "messenger::start_messenger Error on subscribe with code: " << res << std::endl;
            delete pb;
            return 0;
        }

        formatting_helper helper;
        std::string message = "Successfully connected to messaging service";
        res = pb->publish(CHANNEL, helper.format_message(message)).await();
        if (PNR_OK == res) {
            return pb;
        } else {
            std::cout << "messenger::start_messenger Error on initial publish with code: " << res << std::endl;
            delete pb;
            return 0;
        }
    } catch (std::exception &exc) {
        std::cout << "messenger::start_messenger exception" << exc.what() << std::endl;
        return 0;
    }
}

std::string messenger::get_latest_message(pubnub::context* pb)
{
    try {
        pubnub_res res = pb->subscribe(CHANNEL).await();
        if (PNR_OK == res) {
            return pb->get();
        } else {
            std::cout << "messenger::get_latest_message Error on subscribe with code: " << res << std::endl;
            return "";
        }
    } catch (std::exception &exc) {
        std::cout << "messenger::get_latest_message exception" << exc.what() << std::endl;
        return "";
    }
}