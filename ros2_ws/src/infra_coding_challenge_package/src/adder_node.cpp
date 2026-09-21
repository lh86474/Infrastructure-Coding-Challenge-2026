#include "rclcpp/rclcpp.hpp"
#include <memory>
#include "std_msgs/msg/float64.hpp"

class AdderNode : public rclcpp::Node {
	public:
		AdderNode() : Node("adder_node") {
			publisher_ = create_publisher<std_msgs::msg::Float64>("/output_topic", 10);	

			subscription_a_ = create_subscription<std_msgs::msg::Float64>(
					"/input_topic_a", 10,
					[this](std_msgs::msg::Float64::SharedPtr msg) {
						callback_a(msg);
					});
			subscription_b_ = create_subscription<std_msgs::msg::Float64>(
					"/input_topic_b", 10,
					[this](std_msgs::msg::Float64::SharedPtr msg) {
						callback_b(msg);
					});
		}

	private:
		rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
		rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_a_;
		rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_b_;

		double latest_a_ = 0.0;
		bool received_a_ = false;
		double latest_b_ = 0.0;
		bool received_b_ = false;

		void callback_a(const std_msgs::msg::Float64::SharedPtr msg) {
			latest_a_ = msg->data;
			received_a_ = true;
			publish_sum();
		}

		void callback_b(const std_msgs::msg::Float64::SharedPtr msg) {
			latest_b_ = msg->data;
			received_b_ = true;
			publish_sum();
		}

		void publish_sum() {
			if (!received_a_ || !received_b_ ) {
				return;
			}
			std_msgs::msg::Float64 message;
			message.data = latest_a_ + latest_b_;
			publisher_->publish(message);
		}
};

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<AdderNode>());
	rclcpp::shutdown();
	return 0;
}
