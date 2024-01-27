#pragma once

#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_global_position.hpp>
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <cmath>

namespace cl_fc_commander
{
    class ClFlightCommander : public smacc2::ISmaccClient
    {
        private:
            rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr vehicle_command_publisher_;
            rclcpp::Subscription<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr vehicle_global_position_subscriber_;
            rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr vehicle_odometry_;
            float gps_data_[3]; // lat (deg), lon (deg), alt (m)
            float yaw_;

        public:
            ClFlightCommander() {}

            void onInitialize() override
            {    
                vehicle_command_publisher_ = getNode()->create_publisher<px4_msgs::msg::VehicleCommand>("/fmu/in/vehicle_command", 10);

                rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
		        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

                vehicle_global_position_subscriber_ = getNode()->create_subscription<px4_msgs::msg::VehicleGlobalPosition>(
                    "/fmu/out/vehicle_global_position", 
                    qos, 
                    std::bind(&ClFlightCommander::globalPositionCallback, this, std::placeholders::_1)
                );

                vehicle_odometry_ = getNode()->create_subscription<px4_msgs::msg::VehicleOdometry>(
                    "fmu/out/vehicle_odometry",
                    qos,
                    std::bind(&ClFlightCommander::odometryCallback, this, std::placeholders::_1)
                );
            }

            void globalPositionCallback(const px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg)
            {
                gps_data_[0] = msg->lat;     
                gps_data_[1] = msg->lon;     
                gps_data_[2] = msg->alt;     
            }

            void odometryCallback(const px4_msgs::msg::VehicleOdometry::SharedPtr msg)
            {
                yaw_ = atan2(2.0 * (msg->q[0] * msg->q[3] + msg->q[1] * msg->q[2]), 
                    1.0 - 2.0 * (msg->q[2] * msg->q[2] + msg->q[3] * msg->q[3])); 

                yaw_ = yaw_ * (180.0 / M_PI);
                if (yaw_ < 0) {
                    yaw_ += 360.0;
                }
            }

            float *getVehicleGlobalPosition()
            {
                return gps_data_;
            }

            float getYaw()
            {
                return yaw_;
            }

            rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr getVehicleCommandPublisher() 
            {
                return vehicle_command_publisher_;
            }
    };
}