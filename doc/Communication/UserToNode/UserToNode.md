[Communication](../Communication.md)
# User to Node Comms
The Node is responsible for communicating over ROS the Sonar Sensor Array data.

## Overview
It is expected that the majority of the Node's communication responsibilities is to provide Sonar Sensor Array data.  While there may be other low level communication provided over ROS (such as heartbeats, diagnostics, etc) which will be further defined in the future, major consideration for the time being will be given to the Sensor Data that is streamed from the Sensor Array.

Note that the Node will be built using [eROS](https://github.com/fastrobotics/eros), such that it will automatically include a variety of input/output messages (such as heartbeats, diagnostics, etc).

## Message Selection

## References
- https://docs.ros.org/en/noetic/api/sensor_msgs/html/msg/Range.html
- https://wiki.ros.org/rviz/DisplayTypes/Range