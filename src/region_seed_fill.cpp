#include "region_seed_fill.h"

void RegionSeedFill::ccaSeedFill( 
		cv::Point2i _pt, 
		const cv::Mat& _labelImg, 
		cv::Mat& _fillImg, 
		NeighbourCount nc /* = NEIGHBOUR_4 */ )
{
	if ( _labelImg.empty() /*|| _labelImg.type() != CV_8UC1*/ )
	{
		cout << "Input image empty!" << endl;
		return;
	}

	const int cols = _labelImg.cols;
	const int rows = _labelImg.rows;

	cv::Mat labelImg;
	_labelImg.convertTo( labelImg, CV_8UC1);

	cv::Mat(
		rows, 
		cols, 
		CV_8UC1, 
		cv::Scalar(0)).copyTo(_fillImg);

	
	int label = labelImg.at<uchar>(_pt.y, _pt.x); 

	cv::Mat filled(
		rows, 
		cols, 
		CV_8UC1, 
		cv::Scalar(0));

	if ( nc == NEIGHBOUR_4 )
		_neighbours = 4;
	else
		_neighbours = 8;

	seedFill(
		_pt, 
		labelImg, 
		_fillImg, 
		filled, 
		label,
		nc);

}

void RegionSeedFill::seedFill( 
		cv::Point2i _pt, 
		const cv::Mat& _labelImg, 
		cv::Mat& _fillImg, 
		cv::Mat& _isfilled, 
		int& _preLabel, 
		NeighbourCount nc /* = NEIGHBOUR_4 */)
{
//	cout << iters++ << endl;

	if ( _pt.x >= 0 && _pt.x < _labelImg.cols && 
		 _pt.y >= 0 && _pt.y < _labelImg.rows )
	{
		if ( int( _labelImg.at<uchar>(_pt.y, _pt.x) ) == _preLabel && 
			 int( _isfilled.at<uchar>(_pt.y, _pt.x) ) == 0 )
		{

			_fillImg.at<uchar>(_pt.y, _pt.x)  = (uchar)-1;
			_isfilled.at<uchar>(_pt.y, _pt.x) = (uchar)-1;

			if (nc == NEIGHBOUR_4)
			{
				for ( int i=0; i<_neighbours; i++ )
				{
					seedFill(
						cv::Point2i( 
						_pt.x+_dx4[i], 
						_pt.y+_dy4[i] ),
						_labelImg,
						_fillImg,
						_isfilled,
						_preLabel,
						nc);
				}
			}
			else
			{
				for ( int i=0; i<_neighbours; i++ )
				{
					seedFill(
						cv::Point2i( 
						_pt.x+_dx8[i], 
						_pt.y+_dy8[i] ),
						_labelImg,
						_fillImg,
						_isfilled,
						_preLabel,
						nc);
				}
			}
		}
	}
}

void RegionSeedFill::ccaBoundaryFill(
		cv::Point2i _pt, 
		const cv::Mat& _contour, 
		cv::Mat& _fillImg, 
		int contourLabel /*= 255*/,
		NeighbourCount nc /* = NEIGHBOUR_4 */)
{
	if ( _contour.empty() /*|| _labelImg.type() != CV_8UC1*/ )
	{
		cout << "Input image empty!" << endl;
		return;
	}

	const int cols = _contour.cols;
	const int rows = _contour.rows;

	cv::Mat contour;
	_contour.convertTo( contour, CV_8UC1);

	cv::Mat(
		rows, 
		cols, 
		CV_8UC1, 
		cv::Scalar(0)).copyTo(_fillImg);

	cv::Mat filled(
		rows, 
		cols, 
		CV_8UC1, 
		cv::Scalar(0));

	if ( nc == NEIGHBOUR_4 )
		_neighbours = 4;
	else
		_neighbours = 8;

	boundaryFill(_pt, contour, _fillImg, filled, contourLabel, nc);

}

void RegionSeedFill::boundaryFill(
		cv::Point2i _pt, 
		const cv::Mat& _contour, 
		cv::Mat& _fillImg, 
		cv::Mat& _isfilled, 
		int label /*= CONTOUR_LABEl*/,
		NeighbourCount nc /*= NEIGHBOUR_4*/)
{
	if ( _pt.x >= 0 && _pt.x < _contour.cols && 
		 _pt.y >= 0 && _pt.y < _contour.rows )
	{
		if ( int( _contour.at<uchar>(_pt.y, _pt.x) ) != label &&
			 int( _isfilled.at<uchar>(_pt.y, _pt.x) ) == 0 )
		{
			_fillImg.at<uchar>(_pt.y, _pt.x)  = (uchar)-1;
			_isfilled.at<uchar>(_pt.y, _pt.x) = (uchar)-1;

			if (nc == NEIGHBOUR_4)
			{
				for ( int i=0; i<_neighbours; i++ )
				{
					boundaryFill(
						cv::Point2i( 
						_pt.x+_dx4[i], 
						_pt.y+_dy4[i] ),
						_contour,
						_fillImg,
						_isfilled,
						label,
						nc);
				}
			}
			else
			{
				for ( int i=0; i<_neighbours; i++ )
				{
					boundaryFill(
						cv::Point2i( 
						_pt.x+_dx8[i], 
						_pt.y+_dy8[i] ),
						_contour,
						_fillImg,
						_isfilled,
						label,
						nc);
				}
			}


		}
	}
}