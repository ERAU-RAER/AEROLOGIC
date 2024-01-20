#pragma once

#include <sm_uas/clients/cl_receiver/cl_receiver.hpp>
#include <smacc2/smacc_orthogonal.hpp>

namespace sm_uas
{
    using namespace cl_receiver;

    class OrCommunication : public smacc2::Orthogonal<OrCommunication>
    {
        public:
            void onInitialize() override
            {
                auto receiver_client = this->createClient<ClReceiver>();
            }
    };
}