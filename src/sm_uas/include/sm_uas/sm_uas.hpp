#pragma once

#include <rclcpp/rclcpp.hpp>
#include <smacc2/smacc.hpp>

// CLIENTS
#include <sm_uas/clients/cl_fc_commander/cl_fc_commander.hpp>

// ORTHOGONALS
#include <sm_uas/orthogonals/or_flight_control.hpp>

// CLIENT BEHAVIORS
#include <sm_uas/clients/cl_fc_commander/client_behaviors/cb_takeoff.hpp>

using namespace smacc2;

namespace sm_uas
{
    // STATES
    class StPreflight;
    class StTakeoff;

    // STATE MACHINE
    struct SmUAS : public smacc2::SmaccStateMachineBase<SmUAS, StPreflight>
    {
        using SmaccStateMachineBase::SmaccStateMachineBase;

        void onInitialize() override
        {
            this->createOrthogonal<OrFlightControl>();
        }
    };
}

// STATES 
#include <sm_uas/states/st_preflight.hpp>
#include <sm_uas/states/st_takeoff.hpp>
