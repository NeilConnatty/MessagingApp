//
// Created by Neil Connatty on 2016-11-01.
//

#include <iostream>
#include <formatting_helper.h>

#include "pubnub.hpp"
#include "pub_sub_helper.h"

/// BCCH app keys
#define PUBLISH_KEY "pub-c-ffee06f7-78b5-483c-b800-fae8f3a67f0c"
#define SUBSCRIBE_KEY "sub-c-3dc063c8-9bc0-11e6-814f-0619f8945a4f"
#define MSG_CHANNEL "bcch"
#define INPUT_CHANNEL "input"

using namespace std;
using namespace messaging;

static void on_publish (pubnub::context &pb, pubnub_res result)
{
    if (PNR_OK == result) {
        cout << pb.last_publish_result() << endl;
    } else {
        cout << "Publish request failed" << endl;
    }
}

static void on_subscribe (pubnub::context &pb, pubnub_res result)
{
    if (PNR_OK == result) {
        cout << "message received" << endl;

        vector<string> msg = pb.get_all();

        for (unsigned i = 0; i < msg.size(); ++i) {
            cout << msg.at(i) << endl;
        }
    } else {
        std::cout << "Subscribe Request failed" << std::endl;
    }
}

static void on_history (pubnub::context &pb, pubnub_res result)
{
    if (PNR_OK == result) {
        cout << "successfully got history: " << endl;

        vector<string> msg = pb.get_all();

        for (vector<string>::iterator it = msg.begin(); it != msg.end(); ++it) {
            cout << *it << endl;
        }
    } else {
        std::cout << "History Request failed" << std::endl;
    }
}

void input_loop (pub_sub_helper &helper, pubnub::context &context)
{
    string input;
    formatting_helper formatter;
    for (;;) {
        cout << "What would you like to do?" << endl;
        getline(cin, input);
        if (!input.compare("publish")) {
            string message;
            cout << "Please input the message you would like to send:" << endl;
            getline(cin, message);
            message = formatter.format_message(message);
            helper.publish(context, message, MSG_CHANNEL, on_publish);
        } else if (!input.compare("get history")) {
            helper.history(context, MSG_CHANNEL, on_history);
        } else if (!input.compare("zoom image")) {
            input = formatter.format_message(input);
            helper.publish(context, input, INPUT_CHANNEL, on_publish);
        } else if (!input.compare("show image")) {
            input = formatter.format_message(input);
            helper.publish(context, input, INPUT_CHANNEL, on_publish);
        } else if (!input.compare("hide image")) {
            input = formatter.format_message(input);
            helper.publish(context, input, INPUT_CHANNEL, on_publish);
        } else if (!input.compare("reload image")) {
            input = formatter.format_message(input);
            helper.publish(context, input, INPUT_CHANNEL, on_publish);
        } else if (!input.compare("quit")) {
            return;
        } else {
            cout << "That is not a valid input." << endl;
        }
    }
}

int main ()
{
    try {
        pubnub::context pb(PUBLISH_KEY, SUBSCRIBE_KEY);
        pb.set_blocking_io(pubnub::non_blocking);
        pub_sub_helper helper;
        input_loop(helper, pb);
    } catch (exception &exc) {
        cout << "Caught exception: " << exc.what() << endl;
    }
    return 0;
}

