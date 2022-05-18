#include <ros/console.h>
#include <std_msgs/Float64.h>

#include <accumulator/accumulator.hpp>

void data_handler(const std_msgs::Float64::ConstPtr& p) {
    constexpr std::size_t SIZE = 50;
    static dys::accumulator<std::double_t, std::array<std::double_t, SIZE>> acc(SIZE);
    
    auto charge = p->data;
    ROS_INFO("Charge: %lf", charge);

    if (auto discharge = acc.load(charge)) {
        ROS_DEBUG("Discharge: %lf", discharge.value());
    }

    auto average_charge = acc.level() / acc.count();
    std::cout << "Average charge: " << average_charge << std::endl;
}
