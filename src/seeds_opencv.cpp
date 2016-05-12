#include "seeds_opencv.h"
#include "seeds2.h"
#include <vector>
#include <algorithm>

using namespace cv;

void seeds(InputArray _image, int seed_width, int seed_height, int nr_levels, OutputArray _labels, int &count_superpixels)
{
    cv::Mat image = _image.getMat();
    cv::Mat &labels = _labels.getMatRef();

    if (image.empty())
        CV_Error(CV_StsBadArg, "image is empty");
    if (image.type() != CV_8UC3)
        CV_Error(CV_StsBadArg, "image mush have CV_8UC3 type");

    int width = image.cols;
    int height = image.rows;
    int npixels = width * height;

    const int NR_BINS = 5; // Number of bins in each histogram channel

    SEEDS seeds(width, height, 3, NR_BINS);

    seeds.initialize(seed_width, seed_height, nr_levels);

    vector<UINT> ubuff(npixels);
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
        {
            Vec3b c = image.at<Vec3b>(y, x);

            // image is assumed to have data in BGR order
            UINT b = c[0];
            UINT g = c[1];
            UINT r = c[2];

            ubuff[x + y * width] = b | (g << 8) | (r << 16);
        }

    seeds.update_image_ycbcr(&ubuff[0]);
    seeds.iterate();

    UINT *slabels = seeds.get_labels();

    UINT maxElem = *std::max_element(slabels, slabels + npixels);

    vector<int> counts(maxElem + 1, 0);
    for (int i = 0; i < npixels; ++i)
        counts[slabels[i]]++;

    vector<int> deltas(maxElem + 1);
    int delta = 0;
    for (size_t i = 0; i < counts.size(); ++i)
    {
        if (counts[i] == 0)
            delta++;
        deltas[i] = delta;
    }

    for (int i = 0; i < npixels; ++i)
        slabels[i] -= deltas[slabels[i]];

    labels.create(height, width, CV_32SC1);
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            labels.at<int>(y, x) = slabels[x + y * width];

    count_superpixels = maxElem - deltas[maxElem] + 1;
}


void labelContourMask(InputArray _labels, OutputArray _contour, bool thick_line)
{
    cv::Mat labels = _labels.getMat();
    cv::Mat &contour = _contour.getMatRef();

    if (labels.empty())
        CV_Error(CV_StsBadArg, "image is empty");
    if (labels.type() != CV_32SC1)
        CV_Error(CV_StsBadArg, "labels mush have CV_32SC1 type");

    int width = labels.cols;
    int height = labels.rows;

    contour.create(height, width, CV_8UC1);
    contour.setTo(Scalar(0));

    const int dx8[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

    for (int j = 0; j < height; j++)
    {
        for (int k = 0; k < width; k++)
        {
            int neighbors = 0;
            for (int i = 0; i < 8; i++)
            {
                int x = k + dx8[i];
                int y = j + dy8[i];

                if( (x >= 0 && x < width) && (y >= 0 && y < height) )
                {
                    if( labels.at<int>(j, k) != labels.at<int>(y, x) )
                    {
                        if( thick_line || !contour.at<uchar>(y, x) )
                            neighbors++;
                    }
                }
            }
            if( neighbors > 1 )
			{
                contour.at<uchar>(j, k) = (uchar)-1;
			}
        }
    }
}