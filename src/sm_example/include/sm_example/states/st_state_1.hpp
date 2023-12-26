#pragma once

#include <smacc2/smacc.hpp>

namespace sm_example
{
    struct StState1 : smacc2::SmaccState<StState1, SmExample>
    {
        typedef mpl::list<
            Transition<EvEven<CbSubscriberBehavior, OrNumberChecker>, StState2>
        >reactions;

        using SmaccState::SmaccState;

        static void staticConfigure()
        {
            configure_orthogonal<OrNumberGenerator, CbPublishLow>(); 
            configure_orthogonal<OrNumberChecker, CbSubscriberBehavior>(); 
        }

        void onEntry() 
        {
            RCLCPP_INFO(getLogger(), "Entering StState1");
        }

        void onExit() 
        {
            RCLCPP_INFO(getLogger(), "Exiting StState1");
        }
    };
}
