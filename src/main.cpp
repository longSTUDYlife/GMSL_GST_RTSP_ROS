#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <glib.h>  // For g_print

int main (int argc, char *argv[]) {
  GstRTSPServer *server;
  GstRTSPMountPoints *mounts;
  GstRTSPMediaFactory *factory;
  GMainLoop *loop;

  gst_init (&argc, &argv);

  g_print("Initializing RTSP server...\n");

  // Create a new RTSP server instance
  server = gst_rtsp_server_new ();
  g_object_set (server, "address", "0.0.0.0", "service", "8554", NULL);
  g_print("RTSP server created, listening on 0.0.0.0:8554\n");

  // Create a new mount points container
  mounts = gst_rtsp_server_get_mount_points (server);

  // Create and configure media factories for four cameras
  for (int i = 0; i < 4; ++i) {
    g_print("Setting up media factory for camera %d...\n", i);
    
    factory = gst_rtsp_media_factory_new ();
    gchar pipeline[512];
    g_snprintf (pipeline, sizeof(pipeline),
        "nvv4l2camerasrc device=/dev/video%d latency=0 ! video/x-raw(memory:NVMM),format=UYVY,width=1920,height=1536 ! nvvidconv ! nvv4l2h264enc ! h264parse ! queue max-size-buffers=1 ! rtph264pay name=pay0 pt=96 sync=false", i);
    g_print("Pipeline for camera %d: %s\n", i, pipeline);

    gst_rtsp_media_factory_set_launch (factory, pipeline);
    gst_rtsp_media_factory_set_shared (factory, TRUE);

    gchar path[256];
    g_snprintf (path, sizeof(path), "/camera%d", i);
    gst_rtsp_mount_points_add_factory (mounts, path, factory);
    g_print("Camera %d mounted at %s\n", i, path);
  }

  // Start the server
  g_object_unref (mounts);

  g_print("Starting the main loop...\n");
  loop = g_main_loop_new (NULL, FALSE);
  gst_rtsp_server_attach(server, NULL);
  g_main_loop_run (loop);

  g_print("Main loop terminated.\n");

  return 0;
}
