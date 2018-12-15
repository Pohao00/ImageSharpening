#include <cstdio>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;


int xSobel(Mat image, int x, int y)
{
  return image.at<uchar>(y-1, x-1) +
  2*image.at<uchar>(y, x-1) +
  image.at<uchar>(y+1, x-1) -
  image.at<uchar>(y-1, x+1) -
  2*image.at<uchar>(y, x+1) -
  image.at<uchar>(y+1, x+1);
}


int ySobel(Mat image, int x, int y)
{
  return image.at<uchar>(y-1, x-1) +
  2*image.at<uchar>(y-1, x) +
  image.at<uchar>(y-1, x+1) -
  image.at<uchar>(y+1, x-1) -
  2*image.at<uchar>(y+1, x) -
  image.at<uchar>(y+1, x+1);
}

int main()
{
	//宣告物件
  Mat src, dst, image2, image3;
  int sum;
  src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  dst = src.clone();
  image2 = imread("lena.jpg", 1);

  if( !src.data )
    { return -1; }
  
 //初始化
  for(int y = 0; y < src.rows; y++)
    for(int x = 0; x < src.cols; x++)
      dst.at<uchar>(y,x) = 0.0;
 //Sobel
    for(int y = 1; y < src.rows - 1; y++){
      for(int x = 1; x < src.cols - 1; x++){
        sum = abs(xSobel(src, x, y)) + abs(ySobel(src, x, y));
        if (sum > 255)
         sum = 255;
       if (sum < 0)
         sum = 0;
       dst.at<uchar>(y,x) = sum;
     }
   }

//正規化，與原圖結合
   for(int i=0;i<src.cols;i++) 
   {
     for(int j=0;j<src.rows;j++) 
     {
       if(dst.at<uchar>(j,i)<128)
        dst.at<uchar>(j,i) = 0;
      else
        dst.at<uchar>(j,i) = 40;
      image2.at<Vec3b>(j,i)[0] = image2.at<Vec3b>(j,i)[0] + dst.at<uchar>(j,i);
      image2.at<Vec3b>(j,i)[1] = image2.at<Vec3b>(j,i)[1] + dst.at<uchar>(j,i);
      image2.at<Vec3b>(j,i)[2] = image2.at<Vec3b>(j,i)[2] + dst.at<uchar>(j,i);			
    }
  }
  //cout<<dst.cols<<"\n"<<dst.rows<<endl;
  //cout<<image2.cols<<"\n"<<image2.rows<<endl;
  //cout<<image3.cols<<"\n"<<image3.rows<<endl;
  imwrite("big banana.jpg", image2);
  namedWindow("dst", CV_WINDOW_NORMAL);
  imshow("dst", dst);
  namedWindow("image2", CV_WINDOW_NORMAL);
  imshow("image2", image2);
  
  waitKey();
  return 0;
}
