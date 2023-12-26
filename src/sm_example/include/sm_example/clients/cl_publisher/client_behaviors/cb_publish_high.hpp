#pragma once

#include <smacc2/smacc_client_behavior.hpp>
#include <std_msgs/msg/int16.hpp>
#include <random>

namespace cl_publisher
{
    class CbPublishHigh : public smacc2::SmaccClientBehavior, public smacc2::ISmaccUpdatable
    {
        private:
            ClPublisher *client_;

        public:
            CbPublishHigh() {};

            void onEntry() override
            {
                this->requiresClient(client_);
            }

            virtual void update()
            {
                std_msgs::msg::Int16 data;

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(10, 19);

                data.data = distrib(gen);

                this->client_->publish(data);
            }

            void onExit() override {}
    };
}
