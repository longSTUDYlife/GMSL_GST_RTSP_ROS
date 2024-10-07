# GStreamer RTSP Server for Multiple Cameras

This project demonstrates how to create an RTSP server using GStreamer that streams video from multiple GMSL2 cameras. The server mounts different camera streams at different paths and serves them over RTSP.

## Features

- Streams video from four GMSL2 cameras (`/dev/video0` to `/dev/video3`).
- Each camera is mounted on its own GStreamer pipeline:
```
nvv4l2camerasrc device=/dev/video%d latency=0 ! video/x-raw(memory:NVMM),format=UYVY,width=1920,height=1536 ! nvvidconv ! nvv4l2h264enc ! h264parse ! queue max-size-buffers=1 ! rtph264pay name=pay0 pt=96 sync=false
```
- Video encoding is done using NVIDIA's hardware acceleration (`nvv4l2h264enc`).

## Requirements

Before you compile and run this code, you need to install the necessary libraries and dependencies.

### Dependencies

This code depends on several libraries:

- **GStreamer** (Base, Good, Bad, Ugly plugins)
- **GStreamer RTSP Server**
- **glib**

### Installing Dependencies

#### Ubuntu/Debian

You can install the required libraries on Ubuntu/Debian systems using the following commands:

```
sudo apt-get update
sudo apt-get install gstreamer1.0-tools gstreamer1.0-plugins-base gstreamer1.0-plugins-good \
                     gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav \
                     libgstrtspserver-1.0-dev libglib2.0-dev
```
#### Compile
```
mkdir build
cd build
.. cmake
make
```
#### Run
```
./gstreamer_fangwei
```
