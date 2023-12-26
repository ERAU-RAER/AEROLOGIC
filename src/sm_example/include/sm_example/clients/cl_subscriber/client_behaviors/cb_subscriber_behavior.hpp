#pragma once

#include <sm_example/clients/cl_subscriber/cl_subscriber.hpp>

namespace sm_example 
{
    namespace cl_subscriber
    {
        template <typename TSource, typename TOrthogonal>
        struct EvEven : sc::event<EvEven<TSource, TOrthogonal>>
        {
        };

        class CbSubscriberBehavior : public smacc2::SmaccClientBehavior
        {
            public:
                void onEntry() override
                {
                    ClSubscriber *client;
                    this->requiresClient(client);

                    client->onMessageReceived(&CbSubscriberBehavior::callback, this);
                }

                template <typename TOrthogonal, typename TSourceObject>
                void onOrthogonalAllocation()
                {
                    postMyEvent_ = [=] { this->postEvent<EvEven<TSourceObject, TOrthogonal>>(); };
                }

                void callback(const std_msgs::msg::Int16 &msg)
                {
                    if (msg.data % 2 == 0)
                    {
                        this->postMyEvent_();
                    }
                }

                std::function<void()> postMyEvent_;
        };
    }
}