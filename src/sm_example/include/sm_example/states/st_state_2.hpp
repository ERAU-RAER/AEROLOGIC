#pragma once

#include <smacc2/smacc.hpp>

namespace sm_example
{
    struct StState2 : smacc2::SmaccState<StState2, SmExample>
    {
        typedef mpl::list<
            Transition<EvEven<CbSubscriberBehavior, OrNumberChecker>, StState1>
        >reactions;

        using SmaccState::SmaccState;

        static void staticConfigure()
        {
            configure_orthogonal<OrNumberGenerator, CbPublishHigh>(); 
            configure_orthogonal<OrNumberChecker, CbSubscriberBehavior>(); 
        }

        void onEntry() 
        {
            RCLCPP_INFO(getLogger(), "Entering StState2");
        }

        void onExit() 
        {
            RCLCPP_INFO(getLogger(), "Exiting StState2");
        }
    };
}
