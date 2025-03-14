#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class DrawStar : public rclcpp::Node
{
public:
    DrawStar() : Node("draw_star")
    {
        timer_ = this->create_wall_timer(std::chrono::milliseconds(200), std::bind(&DrawStar::loop, this));  
        // /turtle1/cmd_vel plublisher
        publish_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        RCLCPP_INFO(this->get_logger(), "It's drawing a star.");

    }

private:

    void loop()
    {
        // Publish transforms
        auto msg = geometry_msgs::msg::Twist();
        if (count_ < 10)
        {
            msg.linear.x = 1.0;
            msg.angular.z = 0.0;
        }
        else if(count_>=10 && count_<20)
        {
            msg.linear.x = 0.0;
            msg.angular.z = -1.2;
        }
        else if(count_>=20 && count_<30){
            msg.linear.x = 1.0;
            msg.angular.z = 0.0;
        }
        else{
            msg.linear.x = 0.0;
            msg.angular.z = 0.52;
        }
        publish_->publish(msg);
        count_++;
        if (count_ > 40)
        {
            count_ = 0;
        }
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publish_;
    int count_ = 0;

};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DrawStar>());
    rclcpp::shutdown();
    return 0;
}