#pragma once

#include <smacc2/smacc_client_behavior.hpp>
#include <random>

namespace cl_fc_commander
{
    class CbTakeoff : public smacc2::SmaccClientBehavior, public smacc2::ISmaccUpdatable
    {
        private:
            ClFlightCommander *client_;

        public:
            CbTakeoff() {};

            void onEntry() override
            {
                this->requiresClient(client_);
            }

            virtual void update()
            {
            }

            void onExit() override {}
    };
}
