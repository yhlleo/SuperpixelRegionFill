# SEEDS Superpixels Wrapper for OpenCV
This is a simple OpenCV wrapper for original SEEDS superpixels implementation. It uses the version 1.1 from [author's website](http://www.mvdblive.org/seeds/).

## Example

```c++
#include "seeds_opencv.h"

int main()
{
    cv::Mat image = cv::imread("star.png", cv::IMREAD_COLOR);

    cv::Mat labels;
    int count;
    seeds(image, 2, 2, 4, labels, count);

    cv::Mat contour;
    labelContourMask(labels, contour, false);

    image.setTo(cv::Scalar(255, 255, 255), contour);

    cv::imwrite("star_labels.png", image);

    return 0;
}
```

[![Star](http://atilimcetin.com/SEEDS/star_small.png)](http://atilimcetin.com/SEEDS/star.png)
[![Star Labels](http://atilimcetin.com/SEEDS/star_labels_small.png)](http://atilimcetin.com/SEEDS/star_labels.png)


## License

Wrapper is MIT license. Please refer to [author's website](http://www.mvdblive.org/seeds/) for the license of original SEEDS superpixels implementation.
