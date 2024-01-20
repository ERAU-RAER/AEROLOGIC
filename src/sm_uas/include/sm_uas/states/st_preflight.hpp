#pragma once

#include <smacc2/smacc.hpp>

namespace sm_uas
{
    struct StPreflight : smacc2::SmaccState<StPreflight, SmUAS>
    {
        typedef mpl::list<
            Transition<EvPreflightOk<ClReceiver, OrCommunication>, StTakeoff>
        >reactions;

        using SmaccState::SmaccState;

        static void staticConfigure()
        {
        }

        void onEntry() 
        {
            RCLCPP_INFO(getLogger(), "Entering preflight state.");
        }

        void onExit() 
        {
            RCLCPP_INFO(getLogger(), "Exiting preflight state.");
        }
    };
}
