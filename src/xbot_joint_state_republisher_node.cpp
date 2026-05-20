#include "xbot_joint_state_republisher/xbot_joint_state_republisher_node.hpp"

#include <functional>
#include <utility>

#include <rclcpp_components/register_node_macro.hpp>

namespace xbot_joint_state_republisher
{

  XbotJointStateRepublisher::XbotJointStateRepublisher(const rclcpp::NodeOptions &options)
      : rclcpp::Node("xbot_joint_state_republisher", options)
  {
    this->declare_parameter<std::string>("output_topic", "/joint_states");
    const bool sensor_qos = this->declare_parameter<bool>("sensor_qos", false);

    const auto output_qos = sensor_qos
                                ? rclcpp::SensorDataQoS()
                                : rclcpp::QoS(rclcpp::KeepLast(10)).reliable().durability_volatile();

    publisher_ = create_publisher<CanonicalJointState>(
        this->get_parameter("output_topic").as_string(), output_qos);

    subscription_ = create_subscription<XbotJointState>(
        "/xbotcore/joint_states",
        rclcpp::SensorDataQoS(),
        std::bind(&XbotJointStateRepublisher::jointStateCallback, this, std::placeholders::_1));

    RCLCPP_INFO(
        get_logger(),
        "xbot_joint_state_republisher started: /xbotcore/joint_states -> %s",
        this->get_parameter("output_topic").as_string().c_str());
  }

  void XbotJointStateRepublisher::jointStateCallback(const XbotJointState::ConstSharedPtr msg)
  {
    CanonicalJointState out_msg;
    out_msg.header = msg->header;
    out_msg.name = msg->name;

    out_msg.position.reserve(msg->link_position.size());
    for (const auto value : msg->link_position)
    {
      out_msg.position.push_back(static_cast<double>(value));
    }

    out_msg.velocity.reserve(msg->link_velocity.size());
    for (const auto value : msg->link_velocity)
    {
      out_msg.velocity.push_back(static_cast<double>(value));
    }

    out_msg.effort.reserve(msg->effort.size());
    for (const auto value : msg->effort)
    {
      out_msg.effort.push_back(static_cast<double>(value));
    }

    publisher_->publish(std::move(out_msg));
  }

} // namespace xbot_joint_state_republisher

RCLCPP_COMPONENTS_REGISTER_NODE(xbot_joint_state_republisher::XbotJointStateRepublisher)
