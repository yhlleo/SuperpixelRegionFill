#ifndef SEEDS_OPENCV_H
#define SEEDS_OPENCV_H

#include <opencv2/opencv.hpp>

void seeds(cv::InputArray image, int seed_width, int seed_height, int nr_levels, cv::OutputArray labels, int &count_superpixels);
void labelContourMask(cv::InputArray labels, cv::OutputArray contour, bool thick_line);

#endif
