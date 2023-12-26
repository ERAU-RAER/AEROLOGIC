#pragma once

#include <smacc2/client_bases/smacc_subscriber_client.hpp>
#include <std_msgs/msg/int16.hpp>

namespace sm_example
{
    namespace cl_subscriber
    {
        class ClSubscriber : public smacc2::client_bases::SmaccSubscriberClient<std_msgs::msg::Int16>
        {
            public:
                ClSubscriber(std::string topicName)
                : smacc2::client_bases::SmaccSubscriberClient<std_msgs::msg::Int16>(topicName)
                {
                }
        };
    }
}