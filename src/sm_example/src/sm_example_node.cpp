#include <rclcpp/rclcpp.hpp>
#include <sm_example/sm_example.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    smacc2::run<sm_example::SmExample>();
    return 0;
}
