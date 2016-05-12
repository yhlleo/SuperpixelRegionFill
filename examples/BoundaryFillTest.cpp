#include <iostream>

#include "region_seed_fill.h"
#include "Configs.h"

using namespace std;
using namespace cv;

int main()
{
	cv::Mat image = cv::imread( std::string(DATA_DIR "/demo-contours.png"), IMREAD_UNCHANGED);
	cv::Point2i pt(248, 71);
	cv::Mat fillImage;

	if ( !image.empty() )
	{
		RegionSeedFill rsf;
		rsf.ccaBoundaryFill(pt, image, fillImage);

		cv::imwrite( std::string(DATA_DIR "/demo-contours-bf.png"), fillImage);
	}
	else
	{
		cout << "Image is empty!" << endl;
	}
}