#include "multicam.hpp"


MultiCamStreamer::MultiCamStreamer(vector<int> index):
    camera_index(index)
{
    camera_count = index.size();
    camSetup();
};

MultiCamStreamer::~MultiCamStreamer()
// Clean up before exits
{
    close();
};

void MultiCamStreamer::join_threads()
// Keep threads ALIVE
{
    threads.join_all();
}

void MultiCamStreamer::camSetup()
// Set cup camera and call threads
{
    for (int i=0; i < camera_count; i++)
    {
        VideoCapture *capture;
        int idx = camera_index[i];

        capture = new VideoCapture(idx);
        cout << "Camera Setup: " << to_string(idx) << endl;

        camera_capture.push_back(capture);
    }

    for (int i=0; i < camera_count; i++)
    {
        threads.create_thread(boost::bind(&MultiCamStreamer::acquire, this, i));
    }
}

void MultiCamStreamer::acquire(int index)
// Acquiring images for each cam 
{
    VideoCapture *capture = camera_capture[index];
    if(capture->isOpened())
    {
        // namedWindow("cam" + to_string(index));
        while (capture->isOpened())
        {
            // Mat frame;
            if(index == 0)
            {
                (*capture) >> frame1;
                mu_lock.lock();
                imshow("cam0", frame1);
                mu_lock.unlock();
            } else 
            {
                (*capture) >> frame2;
                mu_lock.lock();
                imshow("cam1", frame2);
                mu_lock.unlock();
            }

            if (waitKey(5) == 27) break;
            
        }
        
        destroyWindow("cam" + to_string(index));
    }
    else
    {
        cout << "Don't even start cam" << to_string(index) << "!" << endl;
    }

}

void MultiCamStreamer::close()
// Close all cams when program exits
{
    VideoCapture *cap;
    for (int i = 0; i < camera_count; i++)
    {
        cap = camera_capture[i];
        if (cap->isOpened())
        {
            cap->release();
            cout << "Capture " << i << " released" << endl;
        }
    }
}

int main()
{
    vector<int> capture_index = {0, 2};
    MultiCamStreamer cam(capture_index);
    cam.join_threads();
    return 0;
}
