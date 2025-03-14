from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription(
        [
            Node(
                package='turtlesim',
                executable='turtlesim_node',
            ),
            Node(
                package='bed_ydx_star_turtlesim',
                executable='draw_star',
                output='screen',
            ),
    ])