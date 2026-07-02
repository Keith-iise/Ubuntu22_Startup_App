cd /home/slam/share/D435I_SLAM_ws
source install/setup.bash
ros2 launch realsense2_camera rs_launch.py   enable_color:=true   enable_depth:=true   pointcloud.enable:=true   align_depth.enable:=true   rgb_camera.color_profile:=640x480x30   depth_module.depth_profile:=640x480x30
