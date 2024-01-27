#pragma once

#include <smacc2/smacc_client_behavior.hpp>
#include <random>
#include <rclcpp/rclcpp.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>

namespace cl_fc_commander
{
    class CbTakeoff : public smacc2::SmaccClientBehavior, public smacc2::ISmaccUpdatable
    {
        private:
            ClFlightCommander *client_;
            px4_msgs::msg::VehicleCommand takeoff_command_;
            px4_msgs::msg::VehicleCommand arm_command_;

        public:
            CbTakeoff() {};

            void onEntry() override
            {
                this->requiresClient(client_);
                arm();
                publishTakeoffCommand();
            }

            virtual void update() {}

            void onExit() override {}

            void arm()
            {
                arm_command_.command = px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM;
                arm_command_.param1 = 1.0; 

                rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr publisher = client_->getVehicleCommandPublisher();
                publisher->publish(arm_command_);
            }

            void publishTakeoffCommand()
            {
                float *vehicle_global_position = client_->getVehicleGlobalPosition();
                float yaw = client_->getYaw();

                takeoff_command_.command = px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_TAKEOFF;
                takeoff_command_.param1 = 0.1; // desired pitch (deg)
                takeoff_command_.param2 = 0; // empty
                takeoff_command_.param3 = 0; // empty
                takeoff_command_.param4 = yaw; // yaw (deg)
                takeoff_command_.param5 = vehicle_global_position[0]; // latitude
                takeoff_command_.param6 = vehicle_global_position[1]; // longitude 
                takeoff_command_.param7 = vehicle_global_position[2] + 5.0; // altitude
                takeoff_command_.confirmation = 1;
                takeoff_command_.source_system = 255;
                takeoff_command_.target_system = 1; 
                takeoff_command_.target_component = 1;
                takeoff_command_.from_external = true;

                rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr publisher = client_->getVehicleCommandPublisher();
                publisher->publish(takeoff_command_);
            }
    };
}
