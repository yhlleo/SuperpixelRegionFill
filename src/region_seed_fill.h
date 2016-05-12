
#ifndef REGION_SEED_FILL_H
#define REGION_SEED_FILL_H
#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//static int iters = 0;

#define  CONTOUR_LABEl  255
const int dx4[4]       = {-1, 0, 1, 0};
const int dy4[4]       = {0, 1, 0, -1};
const int dx8[8]       = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dy8[8]       = { 0, -1, -1, -1, 0, 1, 1, 1 };

enum NeighbourCount{
	NEIGHBOUR_4,
	NEIGHBOUR_8
};

class RegionSeedFill
{
public:
	RegionSeedFill() : 
	  _dx8(dx8), 
	  _dy8(dy8),
	  _dx4(dx4),
	  _dy4(dy4)
	{
		_neighbours    = 0;
	}
	~RegionSeedFill() {}

public:
	// connected component analysis by seed-filling method
	void ccaSeedFill( 
			cv::Point2i _pt, 
			const cv::Mat& _labelImg, 
			cv::Mat& _fillImg,
			NeighbourCount nc = NEIGHBOUR_4 );

	void seedFill(
			cv::Point2i _pt,
			const cv::Mat& _labelImg, 
			cv::Mat& _fillImg, 
			cv::Mat& _isfilled,
			int& _preLabel,
			NeighbourCount nc = NEIGHBOUR_4);

	void ccaBoundaryFill(
			cv::Point2i _pt, 
			const cv::Mat& _contour, 
			cv::Mat& _fillImg,
			int contourLabel = 255,
			NeighbourCount nc = NEIGHBOUR_4);

	void boundaryFill(
			cv::Point2i _pt,
			const cv::Mat& _contour, 
			cv::Mat& _fillImg, 
			cv::Mat& _isfilled,
			int lable = CONTOUR_LABEl,
			NeighbourCount nc = NEIGHBOUR_4);

public:
	int _neighbours; 
	const int *_dx8;
	const int *_dy8;
	const int *_dx4;
	const int *_dy4;
};

#endif // REGION_SEED_FILL_H