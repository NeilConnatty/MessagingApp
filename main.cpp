#include <iostream>

#include "pubnub.hpp"
#include "pub_sub_helper.h"

/*
#define PUBLISH_KEY     "pub-c-35051607-8d2c-4d4f-bb63-f25f897ba2fe"
#define SUBSCRIBE_KEY   "sub-c-8ef3c67a-9a3c-11e6-94c7-02ee2ddab7fe"
*/
#define PUBLISH_KEY "pub-c-ffee06f7-78b5-483c-b800-fae8f3a67f0c"
#define SUBSCRIBE_KEY "sub-c-3dc063c8-9bc0-11e6-814f-0619f8945a4f"
#define CHANNEL "bcch"

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
        cout << "successfully subscribed to channel" << endl;

        vector<string> msg = pb.get_all();

        for (unsigned i = 0; i < msg.size(); ++i) {
            cout << msg.at(i) << endl;
        }
    } else {
        std::cout << "Subscribe Request failed" << std::endl;
    }
}

void get_latest (pubnub::context &pb)
{

    vector<string> msg = pb.get_all();

    for (unsigned i = 0; i < msg.size(); ++i) {
        cout << msg.at(i) << endl;
    }
    /*
    string msg = pb.get();
    while (!msg.empty()) {
        cout << "New message: " << msg << endl;
        msg = pb.get();
    }
    cout << "No more new messages" << endl;
     */
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
    for (;;) {
        cout << "What would you like to do?" << endl;
        getline(cin, input);
        if (!input.compare("subscribe")) {
            cout << "Please input name of channel you wish to subscribe to:" << endl;
            getline(cin, input);
            helper.subscribe(context, input, on_subscribe);
        } else if (!input.compare("publish")) {
            string message;
            cout << "Please input the message you would like to send:" << endl;
            getline(cin, message);
            message = "\"" + message + "\"";
            cout << "Please input the channel you would like to send your message to:" << endl;
            getline(cin, input);
            helper.publish(context, message, input, on_publish);
        } else if (!input.compare("get messages")) {
            get_latest(context);
        } else if (!input.compare("get history")) {
            cout <<"Please input the channel you would like to get history from:" << endl;
            getline(cin, input);
            helper.history(context, input, on_history);
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
        cout << "Hello, World!" << endl;
        pubnub::context pb(PUBLISH_KEY, SUBSCRIBE_KEY);
        pb.set_blocking_io(pubnub::non_blocking);
        pub_sub_helper helper;
        input_loop(helper, pb);
    } catch (exception &exc) {
        cout << "Caught exception: " << exc.what() << endl;
    }
    return 0;
}

