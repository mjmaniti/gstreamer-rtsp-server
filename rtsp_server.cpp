// rtsp_server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

#include <iostream>

int main( int argc, char * argv[])
{
	

	GstRTSPServer* server;
	GMainLoop* loop;
	GstRTSPMediaFactory* factory;
	GstRTSPMountPoints* mounts;

	gst_init(&argc, &argv);

	//listens on port 8554 for requests
	server = gst_rtsp_server_new();

	loop = g_main_loop_new(NULL, FALSE); //loop part of gstreamer server

	gst_rtsp_server_attach(server, NULL); // attaches context

	//g_main_loop_run(loop); // starts serving clients

	factory = gst_rtsp_media_factory_new();
	gst_rtsp_media_factory_set_launch(factory,
		"( v4l2src device=/dev/video0 ! video/x-raw,width=1344,height=376,format=(string)YUY2 ! videoconvert ! video/x-raw,format=(string)I420 ! x264enc ! rtph264pay pt=96 name=pay0 )");

	gst_rtsp_media_factory_set_shared(factory, true);
	
	mounts = gst_rtsp_server_get_mount_points(server);

	gst_rtsp_mount_points_add_factory(mounts, "/test", factory);

	g_object_unref(mounts);

	g_main_loop_run(loop); // starts serving clients

	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
