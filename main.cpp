#include <iostream>

#include "pubnub.hpp"
#include "pub_sub_helper.h"

#define PUBLISH_KEY "pub-c-35051607-8d2c-4d4f-bb63-f25f897ba2fe"
#define SUBSCRIBE_KEY "sub-c-8ef3c67a-9a3c-11e6-94c7-02ee2ddab7fe"

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

int main ()
{
    std::cout << "Hello, World!" << std::endl;
    pubnub::context pb(PUBLISH_KEY, SUBSCRIBE_KEY);
    pub_sub_helper helper;
    helper.subscribe(pb, "channel", on_subscribe);
    return 0;
}

