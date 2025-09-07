
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

### 📨 Deliverable 2 - Publishing transforms (30 pts)
### 📨 Deliverable 3 - Looking up a transform (30 pts)
![demo](lab2_demo.gif)

### 📨 Deliverable 4 - Mathematical derivations (25 pts)

1. In the [problem formulation](https://vnav.mit.edu/labs/lab2/exercises.html#problem-formulation), we mentioned that AV2’s trajectory is an arc of parabola in the $x$-$z$ plane of the world frame. Can you prove this statement?
    - Hint:  $\cos(2t)$ can be written as…
    - $1-2\sin(t)^2$
    - And parameterized sin(t) as result:
    - $[\sin(t),0,\cos(2t)]^T = [x,0,1-2x^2]^T~where~x=\sin(t)$
2. Compute $O^1_2(t)$, i.e., the position of AV2 relative to AV1’s body frame as a function of $t$.
    - Hint: write down the homogeneous transformations and compose them accordingly…
    - $O^w_1(t)=[\cos(t),\sin(t),0]^T,~and$ $O^w_2(t)=[\sin(t),0,\cos(2t)]^T,$
    - $O_2^1​(t)=R_{w→1}​(t)(O_2^w​(t)−O_1^w​(t)),$
    - $O_2^w​(t)−O_1^w​(t)=[\sin(t)-\cos(t),-\sin(t),\cos(2t)]^T,$
    - AV1’s reference frame is such that  stays tangent to AV1’s trajectory for all  and  is parallel to  for all  (i.e., equivalently, roll = pitch = 0, yaw = $t$) $→$ $y_1=O_1^w(t)'=[-\sin(t),\cos(t),0]^T$, $z_1=[0,0,1]^T$ and $x_1$ is orthogonal to $y$-$z$, so $$ x_1=y_1 \times z_1=\begin{bmatrix}
i & j & k \cr
-\sin(t) & \cos(t) & 0 \cr
0 & 0 & 1
\end{bmatrix}=
[\cos(t),\sin(t),0]^T$$
    - Rotation vector for transform from frame 1 to world: $$R_1^w=\begin{bmatrix}
\cos(t)&\sin(t)&0 \cr
-\sin(t) & \cos(t) & 0 \cr
0 & 0 & 1
\end{bmatrix}$$
    - Inverse: $$R_{w→1}​=(R_1^w)^T=\begin{bmatrix}
\cos(t)&-\sin(t)&0 \cr
\sin(t) & \cos(t) & 0 \cr
0 & 0 & 1
\end{bmatrix}$$
	- Result: $O_2^1​(t)=[\cos(t)\sin(t)-1,-\sin^2(t),\cos(2t)]^T$

3. Show that $O^1_2(t)$ describes a planar curve and find the equation of its plane $\prod$.
    - Hint: find a linear relation between $z_2^1$ and $y_2^1$
    - $z_2^1=\cos(2t)=1-2\sin^2(t)$ and $y_2^1=-\sin^2(t)→$
    - $z_2^1=1+2y_2^1$
4. Rewrite the above trajectory explicitly using a 2D frame of reference  on the plane found before. Try to ensure that the curve is centered at the origin of this 2D frame and that ,  are axes of symmetry for the curve.
    
    - Hints:
    
    1.  i) center the new 2D frame in $p^1=(-1,-1/2,0)$, these coordinates are in AV1’s frame
    2.  ii) start with a 3D reference frame centered in p with axes , compute 
    3.  iii) make sure that the  component vanishes after the change of coordinates
	- Centered: $O_2^p​(t)=[\cos(t)\sin(t),-\sin^2(t)-\frac{1}{2},\cos(2t)]^T$
	- 2D: $O_2^p​(t)=[\cos(t)\sin(t),-\sin^2(t)-\frac{1}{2}]^T=[\frac{1}{2}\sin(2t),\frac{1}{2}\cos(2t)]$
5. Using the expression of , prove that the trajectory of AV2 relative to AV1 is an ellipse and compute the lengths of its semi-axes.
    - Hint: what is the general form of the equation of an axis-aligned ellipse centered in the origin?
    - General equation of ellipse: $(\frac{x - h}{a})^2+(\frac{y - k}{b})^2=1$
    - $\sin^2(\alpha)+\cos^2(\alpha)=1$
    - $x_p=\frac{1}{2}\sin(2t)→\frac{x_p}{1/2}=\sin(2t)→$
    - $(\frac{\sin(2t)}{1/2})^2+(\frac{\cos(2t)}{1/2})^2=1$
    - It is circle with radius $\frac{1}{2}$
