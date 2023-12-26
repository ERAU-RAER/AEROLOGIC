#pragma once

#include <sm_example/clients/cl_subscriber/cl_subscriber.hpp>
#include <smacc2/smacc_orthogonal.hpp>

namespace sm_example
{
    using namespace cl_subscriber; 

    class OrNumberChecker : public smacc2::Orthogonal<OrNumberChecker>
    {
        public:
            void onInitialize() override
            {
                auto ros_subscriber_client = this->createClient<ClSubscriber>("/number");
            }
    };
}
