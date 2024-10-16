# GMSL_GST_RTSP_ROS
## four_cam.launch
This file launches four ros nodes to get streams from RTSP server and convert the video into ROS topics. Take one of nodes as an example and others are similar.
```
    <node name="rtsp_to_ros_camera0" pkg="rtsp_to_ros" type="rtsp_to_ros" output="screen">
        <param name="pipeline" value="rtspsrc location=rtsp://10.101.25.27:8554/camera0 latency=0 ! rtph264depay ! h264parse config-interval=-1 ! nvv4l2decoder enable-max-performance=true disable-dpb=true ! nvvidconv ! video/x-raw,format=BGRx,width=1920,height=1536 ! videoconvert ! appsink sync=false" />
        <param name="topic" value="camera0/image" />
    </node>
```
`pipeline`: Alternate **10.101.25.27:8554** with the **IP:port of RTSP server**
`topic`: This will be the name of output ROS topic
## Outputs
![alt text](<Peek 2024-09-02 10-02.gif>)