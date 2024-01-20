#include <iostream>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class PreflightOk : public rclcpp::Node
{
    public:
        PreflightOk()
        : Node("preflight_ok")
        {
            publisher_ = this->create_publisher<std_msgs::msg::Bool>("preflight_ok", 10);
            RCLCPP_INFO(this->get_logger(), "Press enter to takeoff.");
        }

        void run()
        {
            auto message = std_msgs::msg::Bool();

            while(rclcpp::ok())
            {
                std::cin.get(); 

                message.data = true; 
                publisher_->publish(message);
            }
        }

    private:
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PreflightOk>();
    node->run();
    rclcpp::shutdown();
    return 0;
}
