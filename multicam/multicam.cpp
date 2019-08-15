#include "multicam.hpp"


MultiCamStreamer::MultiCamStreamer(vector<int> index, bool display):
    camera_index(index), show_cam(display)
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
        while (capture->isOpened())
        {
            if(index == 0)
            {
                (*capture) >> frame1;
                if (show_cam)
                {
                    mu_lock.lock();
                    imshow("cam0", frame1);
                    mu_lock.unlock();
                }
            } else 
            {
                (*capture) >> frame2;
                if (show_cam)
                {
                    mu_lock.lock();
                    imshow("cam1", frame2);
                    mu_lock.unlock();
                }
            }

            if (waitKey(1) == 27) break;
            
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

int main(int argc, char** argv)
{
    bool display = false;
    if (argc < 2)
    {
        cout << "[INFO]: Execute './multicam display' to display camera streaming." << endl;
    } else
    {
        std::string action(argv[1]);
        if (action == "display")
        {
            display = true;
            cout << "Set to display camera streaming." << endl;
        }
    }
    
    vector<int> capture_index = {0, 2};
    MultiCamStreamer cam(capture_index, display);
    cam.join_threads();
    return 0;
}
