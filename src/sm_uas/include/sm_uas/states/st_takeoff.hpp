#pragma once

#include <smacc2/smacc.hpp>

namespace sm_uas
{
    struct StTakeoff : smacc2::SmaccState<StTakeoff, SmUAS>
    {
        using SmaccState::SmaccState;

        static void staticConfigure()
        {
            configure_orthogonal<OrFlightControl, CbTakeoff>(); 
        }

        void onEntry() 
        {
            RCLCPP_INFO(getLogger(), "Entering takeoff state.");
        }

        void onExit() 
        {
            RCLCPP_INFO(getLogger(), "Exiting takeoff state.");
        }
    };
}
