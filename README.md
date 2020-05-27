# Intel RealSense ROS plugin for Gazebo and MoveIt!

Simulation of the Realsense R200 sensor in Gazebo.

## Use of Package 

This package is used to obtain color and depth image and depth registered points from a RS200 camera attached to the wrist of a Franka Emika Panda Robot. 

## Parts used for by Panda Simulation

rs200

Point Cloud Demo can be obtained by running 

```
roslaunch realsense_gazebo_plugin depth_proc.launch
```
##### Disclaimer: Already added to the Simulation Launch file in ```panda_simulation```

## Save Point Cloud as OBJ file

The point cloud data obtained from the camera can be saved as an .obj file by running 

```
rosrun src/SavePointCloud.cpp
```

## Run the point cloud demo

Using [depth_image_proc](http://wiki.ros.org/depth_image_proc) package, we can generate a point cloud from the depth image by running

```
roslaunch realsense_gazebo_plugin depth_proc.launch
```

## Acknowledgement

This is a modified and updated version of the work done by[SyrianSpock](https://github.com/SyrianSpock/realsense_gazebo_plugin) 
