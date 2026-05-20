# Joint State Republisher

`xbot_joint_state_republisher` is a ROS 2 C++ bridge that republishes:

- input: `xbot_msgs/msg/JointState` on `/xbotcore/joint_states`
- output: `sensor_msgs/msg/JointState` on a configurable topic, defaulting to `/joint_states`

It keeps the same message timing and joint identifiers, and only maps the fields needed by the canonical joint-state message:

- `header` -> `header`
- `name` -> `name`
- `link_position` -> `position`
- `link_velocity` -> `velocity`
- `effort` -> `effort`

The remaining `xbot_msgs/msg/JointState` fields are ignored.

## Build

```bash
colcon build --packages-select xbot_joint_state_republisher
```

## Run

The package is built as a composable component and also exposes the generated executable:

```bash
ros2 run xbot_joint_state_republisher xbot_joint_state_republisher
```

## Notes

- This node is only a thin republisher
- The output type uses `float64[]` for `position`, `velocity`, and `effort`, so values from the source message are forwarded by numeric conversion.
