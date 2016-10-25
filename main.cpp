#include <iostream>

#include "pubnub.hpp"
#include "pub_sub_helper.h"

#define PUBLISH_KEY "pub-c-35051607-8d2c-4d4f-bb63-f25f897ba2fe"
#define SUBSCRIBE_KEY "sub-c-8ef3c67a-9a3c-11e6-94c7-02ee2ddab7fe"

using namespace std;
using namespace messaging;

static void on_publish (pubnub::context &pb, pubnub_res result)
{
    if (PNR_OK == result) {
        std::cout << pb.last_publish_result() << std::endl;
    } else {
        std::cout << "Publish request failed" << std::endl;
    }
}

static void on_subscribe (pubnub::context &pb, pubnub_res result)
{
    if (PNR_OK == result) {
        std::vector<std::string> msg = pb.get_all();

        for (std::vector<std::string>::iterator it = msg.begin(); it != msg.end(); ++it) {
            std::cout << *it << std::endl;
        }
    } else {
        std::cout << "Subscribe Request failed" << std::endl;
    }
}

void input_loop (pub_sub_helper &helper, pubnub::context &context)
{
    string input;
    for (;;) {
        cout << "What would you like to do?" << endl;
        getline(cin, input);
        if (!input.compare("subscribe")) {
            cout << "Valid input" << endl;
        } else if (!input.compare("publish")) {
            cout << "Valid input" << endl;
        } else if (!input.compare("quit")) {
            return;
        } else {
            cout << "That is not a valid input." << endl;
        }
    }
}

int main ()
{
    cout << "Hello, World!" << endl;
    pubnub::context pb(PUBLISH_KEY, SUBSCRIBE_KEY);
    pub_sub_helper helper;
    input_loop(helper, pb);
    return 0;
}

