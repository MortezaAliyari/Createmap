# Create map with lidar
In this repo, i created map of unknown environment base on C++17 thread library as a standard lib.

If you like the project give me a star! :star: 

You can see the video: &nbsp;&nbsp;
[![website](./img/youtube-dark.svg)](https://www.youtube.com/channel/UCyRBig4xgAdaRdIz14Xymrg)
&nbsp;&nbsp;
---

### This package runned on below circumstances :
- Ubuntu Focal
- ROS Noetic 
- Gazebo11 & TurtleBot3
- Thread lib
- C++17
- Cmake 3.20
---
Run below commands:
```
roslaunch turtlebot3_gazebo turtlebot3_world.launch
```
you can have any environment! also you can use webots environment!
```
roslaunch mor_createmap createmap.launch
```
use own keyboard to move and control the robot
```
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```
also you can save the created map with below service command from map server.
```
rosrun map_server map_saver -f ~/my_map
```
