#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalPublisher : public rclcpp::Node {
  public:
    MinimalPublisher() : Node("minimal_publisher") {
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    }
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    void run() {
        auto message = std_msgs::msg::String();
        size_t count = 0;
        rclcpp::Rate r(1);
        while (rclcpp::ok()) {
            message.data = "Hello, world! " + std::to_string(count++);
            publisher_->publish(message);
            r.sleep();
        }
    }
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  MinimalPublisher pub;
  pub.run();
  rclcpp::shutdown();
  return 0;
}