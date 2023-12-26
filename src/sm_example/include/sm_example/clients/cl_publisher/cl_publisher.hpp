#pragma once

#include <smacc2/client_bases/smacc_publisher_client.hpp>
#include <std_msgs/msg/int16.hpp>

namespace cl_publisher
{
    class ClPublisher : public smacc2::client_bases::SmaccPublisherClient
    {
        public:
            ClPublisher(std::string topicName) : topicName_(topicName) {}

            void onInitialize() override
            {
                this->configure<std_msgs::msg::Int16>(topicName_);
            }

            void publish(const std_msgs::msg::Int16 &msg)
            {
                SmaccPublisherClient::publish(msg);
            }

            std::string topicName_;
    };
}