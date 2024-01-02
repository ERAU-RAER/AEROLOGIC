#pragma once

#include <sm_uas/clients/cl_fc_commander/cl_fc_commander.hpp>
#include <smacc2/smacc_orthogonal.hpp>

namespace sm_uas
{
    using namespace cl_fc_commander;

    class OrFlightControl : public smacc2::Orthogonal<OrFlightControl>
    {
        public:
            void onInitialize() override
            {
                auto flight_commander_client = this->createClient<ClFlightCommander>();
            }
    };
}