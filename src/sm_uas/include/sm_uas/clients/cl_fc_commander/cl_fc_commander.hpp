#pragma once

namespace cl_fc_commander
{
    class ClFlightCommander : public smacc2::ISmaccClient
    {
        public:
            ClFlightCommander() {}

            void onInitialize() override
            {    
            }
    };
}