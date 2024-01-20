import os
from launch import LaunchDescription
from launch_ros.actions import Node
import launch.actions
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
    world_file_path = '/root/workspace/dev/src/sim/worlds/test_world.world'

    return LaunchDescription([
        launch.actions.ExecuteProcess(
            cmd=['ign', 'gazebo', '-r', world_file_path],
            output='screen'),

    ])
