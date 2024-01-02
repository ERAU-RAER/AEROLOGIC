#include <rclcpp/rclcpp.hpp>
#include <sm_uas/sm_uas.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    smacc2::run<sm_uas::SmUAS>();
    return 0;
}
