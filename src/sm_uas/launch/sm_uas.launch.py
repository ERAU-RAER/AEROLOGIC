from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='sm_uas',
            executable='sm_uas_node',
            name='sm_uas_node',
            output='screen'
        ),
        Node(
            package='sm_uas',
            executable='preflight_ok',
            name='preflight_ok',
            output='screen'
        )
    ])
