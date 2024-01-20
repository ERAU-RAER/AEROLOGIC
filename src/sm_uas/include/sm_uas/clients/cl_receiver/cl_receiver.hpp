#pragma once

#include <iostream>
#include <rclcpp/rclcpp.hpp> 
#include <smacc2/client_bases/smacc_subscriber_client.hpp>
#include <std_msgs/msg/bool.hpp>
#include <functional>

namespace sm_uas
{
    namespace cl_receiver
    {
        template <typename TSource, typename TOrthogonal>
        struct EvPreflightOk : sc::event<EvPreflightOk<TSource, TOrthogonal>>
        {
        };

        class ClReceiver : public smacc2::ISmaccClient
        {
            public:
                ClReceiver() {}

                void onInitialize() override
                {
                    subscription_ = getNode()->create_subscription<std_msgs::msg::Bool>(
                        "preflight_ok", 10, std::bind(&ClReceiver::callback, this, std::placeholders::_1));
                }

                template <typename TOrthogonal, typename TSourceObject>
                void onOrthogonalAllocation()
                {
                    postPreflightOk = [=] { this->postEvent<EvPreflightOk<TSourceObject, TOrthogonal>>(); };
                }

                void callback(const std_msgs::msg::Bool::SharedPtr preflight_ok) 
                {
                    if (preflight_ok->data)
                    {
                        postPreflightOk();
                    }
                }

                std::function<void()> postPreflightOk;
            
            private:
                rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_;
        };
    }
}