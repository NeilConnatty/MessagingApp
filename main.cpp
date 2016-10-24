#include <iostream>

#include "pubnub.hpp"

static void on_publish(pubnub::context &pb, pubnub_res result)
{
    if (PNR_OK == result) {
        std::cout << "Published OK" << std::endl;
    }
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    pubnub::context pb("demo", "demo");
    pubnub::futres f = pb.publish("hello_world", "\"Don't call us\"");
    f.then(on_publish);
    return 0;
}

