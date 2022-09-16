#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;

class QuickDemo {
public:
	void colorSpace_Demo(Mat& image);
	void mat_creation_demo();
	void pixel_visit_demo(Mat& image);		//图像像素的读写操作
	void operators_demo(Mat& image);		//图像像素的算术操作
	void trackbar_demo(Mat& image);			//TrackBar滚动条操作
	void trackbar_demo2(Mat& image);
	void key_demo(Mat& image);				//键盘输入控制图片操作
	void color_style_demo(Mat& image);		//颜色调整操作
	void bitwise_demo(Mat& image);			//图像像素的逻辑运算
	void channels_demo(Mat& image);			//图像通道分离和合并
	void inrange_demo(Mat& image);			//图像色彩空间转换
	void pixel_statistic_demo(Mat& image);	//图像像素值统计
	void drawing_demo(Mat& image);			//图像几何图形绘制
	void random_drawing();					//随机数与随机图像绘制
	void mouse_demo(Mat& image);						//鼠标响应

	void video_demo(Mat& image);
};