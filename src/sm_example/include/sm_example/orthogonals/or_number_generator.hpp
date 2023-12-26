#pragma once

#include <sm_example/clients/cl_publisher/cl_publisher.hpp>
#include <smacc2/smacc_orthogonal.hpp>

namespace sm_example
{
    using namespace cl_publisher; 

    class OrNumberGenerator : public smacc2::Orthogonal<OrNumberGenerator>
    {
        public:
            void onInitialize() override
            {
                auto ros_publisher_client = this->createClient<ClPublisher>("/number");
            }
    };
}
