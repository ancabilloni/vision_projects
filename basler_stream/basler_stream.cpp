#include </opt/pylon5/include/pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

using namespace Pylon;
using namespace cv; 
using namespace std;

int main(int argc, char* argv[])
{
    int exitCode = 0;
    int key;

    PylonInitialize();

    try
    {
        CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());
        camera.MaxNumBuffer = 5;
        camera.StartGrabbing(GrabStrategy_LatestImageOnly);

        // pylon ImageFormatConverter
        CImageFormatConverter formatConverter;

        formatConverter.OutputPixelFormat = PixelType_BGR8packed;

        CPylonImage pylonImage;

        Mat openCvImage;

        CGrabResultPtr ptrGrabResult;

        namedWindow("CV Video Client",1);

        while (true)
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);

            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Convert grabbed buffer to a pylon image
                formatConverter.Convert(pylonImage, ptrGrabResult);
                // Create an OpenCV image from a pylon image
                openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
                imshow("frame", openCvImage);
                if (waitKey(10) == 27) // stop capture by pressing ESC 
                {
                    cout << "Seem like q pressed!" << endl;
                    destroyAllWindows();
                    break;
                }
            }
            else
            {
                cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
            }
        }
    }
    catch (const GenericException &e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
        << e.GetDescription() << endl;
        exitCode = 1;
    }

    // Comment the following two lines to disable waiting on exit.
    cerr << endl << "Press Enter to exit." << endl;
    while( cin.get() != '\n');

    // Releases all pylon resources. 
    
    PylonTerminate();  

    return exitCode;
}