// opencv451.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include "quickopencv.h"

using namespace cv;
using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    
    //Mat src = imread("D:/images/lena.jpg");
    Mat src = imread("F:/opencv_tutorial_data-master/opencv_tutorial_data-master/images/sp_noise.png");
    if (src.empty())
    {
        printf("不能打开图像\n");
        return -1;
    }
    namedWindow("window", WINDOW_FREERATIO);
    imshow("输入图片", src);

    QuickDemo qd;
    //qd.colorSpace_Demo(src);
    //qd.mat_creation_demo();
    //qd.pixel_visit_demo(src);     //图像像素的读写操作
    //qd.operators_demo(src);       //图像像素的算术操作
    //qd.trackbar_demo2(src);       
    //qd.key_demo(src);             //键盘输入控制图片操作
    //qd.color_style_demo(src);     //颜色调整操作
    //qd.bitwise_demo(src);         //图像像素的逻辑运算
    //qd.channels_demo(src);        //图像通道分离和合并
    //qd.inrange_demo(src);		    //图像色彩空间转换
    //qd.pixel_statistic_demo(src); //图像像素值统计
    //qd.drawing_demo(src);         //图像几何图形绘制
    //qd.random_drawing();            // 随机数与随机图像绘制
    qd.mouse_demo(src);
    //qd.video_demo(src);             //视频文件与摄像头
   


    waitKey(0);
    destroyAllWindows();

    

    return 0;
}

