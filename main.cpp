#include <iostream>

#include "pubnub.hpp"
#include "pub_sub_helper.h"

#define PUBLISH_KEY     "pub-c-35051607-8d2c-4d4f-bb63-f25f897ba2fe"
#define SUBSCRIBE_KEY   "sub-c-8ef3c67a-9a3c-11e6-94c7-02ee2ddab7fe"

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
            /*
            pubnub_res res = context.subscribe(input).await();
            if (PNR_OK == res) {
                cout << "First subscribe completed, waiting to finish second..." << endl;
                /// literally have to subscribe twice... god knows why they designed it this way
                helper.subscribe(context, input, on_subscribe);
            } else {
                cout << "Subscribe failed with code: " << (int)res << ". Please try again" << endl;
            }
             */
        } else if (!input.compare("publish")) {
            string message;
            cout << "Please input the message you would like to send:" << endl;
            getline(cin, message);
            message = "\"" + message + "\"";
            cout << "Please input the channel you would like to send your message to:" << endl;
            getline(cin, input);
            helper.publish(context, message, input, on_publish);
        } else if (!input.compare("get messages")) {
            input = context.get();
            while (!input.empty()) {
                cout << "New message: " << input << endl;
                input = context.get();
            }
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
        pub_sub_helper helper;
        input_loop(helper, pb);
    } catch (exception &exc) {
        cout << "Caught exception: " << exc.what() << endl;
    }
    return 0;
}

