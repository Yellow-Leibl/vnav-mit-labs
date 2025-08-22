
### 📨 Deliverable 1 - Nodes, topics, launch files (10 pts)

With the `ros2 launch` command above we have spawned a number of ROS nodes at the same time. Using your knowledge of ROS, answer the following questions:

1. List the nodes running in the two-drone static scenario.
    - Hint: you can directly inspect the launch file, use the `ros2 node list` command, or get some help from `rqt_graph`. You will notice that rViz is initially not shown in it but you can uncheck the _Debug_ option for a full picture.
    - **Answer**:
	    - ```bash
	      $ ros2 node list
	      /av1broadcaster
	      /av2broadcaster
	      /plots_publisher_node
	      /rviz2_node
	      /transform_listener_impl_56729484e6c0
	      /transform_listener_impl_57ff8b9f8d50
	      ```
2. How could you run the two-drone static scenario without using the `ros2 launch` command? List the commands that you would have to execute (in separate terminals) to achieve the same result.
    - Hint: `ros2 run [...]`, try things out before finalizing your answer!
    - **Answer**:
    - Run in several terminals
    - ```bash
      ros2 run tf2_ros static_transform_publisher 1 0 0 0 0 0 world av1
      ros2 run tf2_ros static_transform_publisher 0 0 1 0 0 0 world av2
      ros2 run two_drones_pkg plots_publisher_node
      ros2 run rviz2 rviz2 -d $(ros2 pkg prefix two_drones_pkg)/share/two_drones_pkg/config/default.rviz
      ```
3. List the topics that each node publishes / subscribes to. What nodes are responsible for publishing the av1, av2, frames? Which topic causes rViz to plot the drone meshes?
    - Hint: uncheck items on the left pane in rViz until the meshes disappear, then check what node is publishing the corresponding topic
    - **Answer**:
    - Open rqt_graph and look:
    - rectangle - topics
    - Topic /tf:
	    - Subscribes to: av1broadcaster, av2broadcaster
	    - Publishes to: transform_listener_impl_56729484e6c0, transform_listener_impl_57ff8b9f8d50
	- Topic /visuals:
		- Subscribes to: /plots_publisher_node
		- Publishes to: /rviz2_node
4. What changes if we omit `static:=True`? Why?
    - Hint: check out and briefly explain the if and unless keywords in the launch file
    - **Answer**:
    - According to file two_drones.launch.yaml, av1,2 broadcasters will not run and frames_publisher_node will start
