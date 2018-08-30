# SuperpixelRegionFill
Superpixels-based region filling

GitHub: [yhlleo/SuperpixelRegionFill](https://github.com/yhlleo/SuperpixelRegionFill)

抠取图像区域的一个小demo，借助图像超像素分割的方法，将图像成子分块，再利用种子填充算法，选取子块区域。

超像素分割方法，采用论文*SEEDS: Superpixels Extracted via Energy-Driven Sampling*提出的方法，对于物体的边界具有较好的保留，如下图所示。可以辅助目标检测中制作Banchmark。

[![Star](http://atilimcetin.com/SEEDS/star_small.png)](http://atilimcetin.com/SEEDS/star.png)
[![Star Labels](http://atilimcetin.com/SEEDS/star_labels_small.png)](http://atilimcetin.com/SEEDS/star_labels.png)


本工程在其基础上，获得的图像`labels`和`contours`，然后分别实现区域种子填充，Windows下编译环境为：

 - OpenCV
 - CMake
 - Visual Studio

工程`demo`包括：

 - `SuperSeedsTest`: SEEDS 提供的用例，可获取超像素分割`labels`和`contours`
 - `SeedFillTest` : 基于`labels`种子填充子块
 - `BoundaryFillTest` : 基于`contours`种子填充子块

[![vs_solution](http://i.imgur.com/4T6sLV3.png)](http://i.imgur.com/4T6sLV3.png)

(测试代码以`./data`文件下`demo.jpg`为例）

[![demo-seg](http://i.imgur.com/XPTfOsD.png)](http://i.imgur.com/XPTfOsD.png)

在选取了种子点`(col, row)->(248, 71)`后，两种方法得到的区域mask分别为:

[![demo-contours-sf](http://i.imgur.com/FnIgHp8.png)](http://i.imgur.com/FnIgHp8.png)

[![demo-contours-bf](http://i.imgur.com/qcNIHY9.png)](http://i.imgur.com/qcNIHY9.png)

由于保存的`labels`图像是8bit位图(内存中是`CV_32SC1`)，所以是有损的，如果使用`labels`区域填充的时候，最好不要使用demo中从保存图像中加载`labels`数据（也就是在内存中进行，例如通过函数传参）。

种子填充算法使用递归的形式，对于小块的像素区域比较有效，但是由于编译器栈深度有限，填充区域过大的时候，会出现栈溢出的BUG，这里需要注意一下。


## References

 - [SEEDS: Superpixels Extracted via Energy-Driven Sampling](http://www.mvdblive.org/seeds/)
 - [SEEDS Superpixels Wrapper for OpenCV](https://github.com/yhlleo/SEEDS-superpixels)
