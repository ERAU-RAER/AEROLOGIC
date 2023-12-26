#pragma once

#include <smacc2/smacc.hpp>

// CLIENTS
#include <sm_example/clients/cl_publisher/cl_publisher.hpp>
#include <sm_example/clients/cl_subscriber/cl_subscriber.hpp>

// ORTHOGONALS
#include <sm_example/orthogonals/or_number_generator.hpp>
#include <sm_example/orthogonals/or_number_checker.hpp>

// CLIENT BEHAVIORS
#include <sm_example/clients/cl_publisher/client_behaviors/cb_publish_high.hpp>
#include <sm_example/clients/cl_publisher/client_behaviors/cb_publish_low.hpp>
#include <sm_example/clients/cl_subscriber/client_behaviors/cb_subscriber_behavior.hpp>

using namespace smacc2;

namespace sm_example
{
    // STATES
    class StState1;
    class StState2;

    // STATE MACHINE
    struct SmExample : public smacc2::SmaccStateMachineBase<SmExample, StState1>
    {
        using SmaccStateMachineBase::SmaccStateMachineBase;

        void onInitialize() override
        {
            this->createOrthogonal<OrNumberGenerator>();
            this->createOrthogonal<OrNumberChecker>();
        }
    };
}

// STATES 
#include <sm_example/states/st_state_1.hpp> 
#include <sm_example/states/st_state_2.hpp> 
