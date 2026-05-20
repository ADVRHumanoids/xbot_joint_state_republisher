#ifndef XBOT_JOINT_STATE_REPUBLISHER__XBOT_JOINT_STATE_REPUBLISHER_NODE_HPP_
#define XBOT_JOINT_STATE_REPUBLISHER__XBOT_JOINT_STATE_REPUBLISHER_NODE_HPP_

#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <xbot_msgs/msg/joint_state.hpp>

namespace xbot_joint_state_republisher
{

  /**
   * @brief A simple node that subscribes to /xbotcore/joint_states and republishes it as sensor_msgs::msg::JointState.
   *
   * The node accept a parameter "output_topic" to specify the topic to republish to, which defaults to "/joint_states".
   */
  class XbotJointStateRepublisher : public rclcpp::Node
  {
  public:
    explicit XbotJointStateRepublisher(const rclcpp::NodeOptions &options);

  private:
    using XbotJointState = xbot_msgs::msg::JointState;
    using CanonicalJointState = sensor_msgs::msg::JointState;

    void jointStateCallback(const XbotJointState::ConstSharedPtr msg);

    rclcpp::Subscription<XbotJointState>::SharedPtr subscription_;
    rclcpp::Publisher<CanonicalJointState>::SharedPtr publisher_;
  };

} // namespace xbot_joint_state_republisher

#endif // XBOT_JOINT_STATE_REPUBLISHER__XBOT_JOINT_STATE_REPUBLISHER_NODE_HPP_
