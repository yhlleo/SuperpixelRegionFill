#include <iostream>

#include "seeds_opencv.h"
#include "Configs.h"

using namespace std;
using namespace cv;

int main()
{
	cv::Mat image = cv::imread( std::string(DATA_DIR "/demo.jpg"), IMREAD_UNCHANGED);
  
    if ( !image.empty() )
    {
        cv::Mat labels;
        int count;
        seeds(image, 2, 2, 4, labels, count);
		cv::imwrite( std::string(DATA_DIR "/demo-lables.png"), labels);
  
        cv::Mat contour;
        labelContourMask(labels, contour, false);
		cv::imwrite( std::string(DATA_DIR "/demo-contours.png"), contour);

        image.setTo(cv::Scalar(255, 255, 255), contour);
		cv::imwrite( std::string(DATA_DIR "/demo-seg.png"), image);
    }
    else
    {
        cout << "Open image failed!" << endl;
    }
    return 0;

}