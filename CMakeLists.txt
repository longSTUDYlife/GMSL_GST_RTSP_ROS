cmake_minimum_required(VERSION 3.10)
project(gstreamer_fangwei)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0)
pkg_check_modules(GST_RTSP REQUIRED gstreamer-rtsp-server-1.0)

include_directories(${GST_INCLUDE_DIRS} ${GST_RTSP_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS} ${GST_RTSP_LIBRARY_DIRS})

add_executable(gstreamer_fangwei src/main.cpp)
target_link_libraries(gstreamer_fangwei ${GST_LIBRARIES} ${GST_RTSP_LIBRARY} /usr/lib/aarch64-linux-gnu/libgstrtspserver-1.0.so)
