#ifndef MULTICAM_HEADER
#define MULTICAM_HEADER

// #include <ros/ros.h>
#include <vector>
#include <string>
#include <iostream>

// Opencv stuff
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Thread stuff
#include <queue>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;
using namespace cv;

class MultiCamStreamer
{
public:
    ~MultiCamStreamer(); // Destructor
    MultiCamStreamer(vector<int> index); // Constructor
    void camSetup();
    void acquire(int index);
    void close();
    void join_threads();
    
private:
    int camera_count;
    vector<int> camera_index;
    vector<VideoCapture*> camera_capture;
    vector<queue<Mat>*> frame_queue;
    boost::mutex mu_lock;
    boost::thread_group threads;
    Mat frame1;
    Mat frame2;
};

#endif
