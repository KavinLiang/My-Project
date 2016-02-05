#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "hsv.h"
using namespace cv;
using namespace std;
int getoutcounter=0;
#ifndef HARRIS_H   
#define HARRIS_H
class  harris  
{  
private :  
    cv::Mat cornerStrength;   //opencv harris函數檢測結果，也就是每個像素的角點響應函數值  
    cv::Mat cornerTh;  //cornerStrength閾值化的結果  
    cv::Mat localMax;  //局部最大值結果  
    int  neighbourhood;  //鄰域窗口大小  
    int  aperture; //sobel邊緣檢測窗口大小（sobel獲取各像素點x，y方向的灰度導數）  
    double  k;  
    double  maxStrength; //角點響應函數最大值  
    double  threshold; //閾值除去響應小的值  
    int  nonMaxSize; //這裡採用默認的3，就是最大值抑制的鄰域窗口大小  
    cv::Mat kernel; //最大值抑制的核，這裡也就是膨脹用到的核  
public :  
    harris():neighbourhood(3),aperture(3),k(0.01),maxStrength(0.0),threshold(0.01),nonMaxSize(3){  
  
    };  
  
    void  setLocalMaxWindowsize( int  nonMaxSize){  
        this ->nonMaxSize = nonMaxSize;  
    };  
  
   // 計算角點響應函數以及非最大值抑制  
    void  detect( const  cv::Mat &image){  
            //opencv自帶的角點響應函數計算函數  
            cv::cornerHarris (image,cornerStrength,neighbourhood,aperture,k);  
            double  minStrength;  
            //計算最大最小響應值  
            cv::minMaxLoc (cornerStrength,&minStrength,&maxStrength);  
  
            cv::Mat dilated;  
            //默認3*3核膨脹，膨脹之後，除了局部最大值點和原來相同，其它非局部最大值點被  
            //3*3鄰域內的最大值點取代  
            cv::dilate (cornerStrength,dilated,cv::Mat());  
            //與原圖相比，只剩下和原圖值相同的點，這些點都是局部最大值點，保存到localMax  
            cv::compare(cornerStrength,dilated,localMax,cv::CMP_EQ);  
    }  
  
  //  獲取角點圖  
    cv::Mat getCornerMap( double  qualityLevel) {  
            cv::Mat cornerMap;  
            // 根據角點響應最大值計算閾值  
            threshold= qualityLevel*maxStrength;  
            cv::threshold(cornerStrength,cornerTh,  
            threshold,255,cv::THRESH_BINARY);  
            // 轉為8-bit圖  
            cornerTh.convertTo(cornerMap,CV_8U);  
             //和局部最大值圖與，剩下角點局部最大值圖，即：完成非最大值抑制  
            cv::bitwise_and(cornerMap,localMax,cornerMap);  
            return  cornerMap;  
    }  
  
    void  getCorners(std::vector<cv::Point> &points,  
            double  qualityLevel) {  
           // 獲取角點圖  
            cv::Mat cornerMap= getCornerMap(qualityLevel);  
            // 獲取角點  
            getCorners(points, cornerMap);  
    }  
  
    // 遍歷全圖，獲得角點  
    void  getCorners(std::vector<cv::Point> &points,  
    const  cv::Mat& cornerMap) {  
  
            for (  int  y = 0; y < cornerMap.rows; y++ ) {  
                    const  uchar* rowPtr = cornerMap.ptr<uchar>(y);  
                    for (  int  x = 0; x < cornerMap.cols; x++ ) {  
                     //非零點就是角點  
                          if  (rowPtr[x]) {  
                                points.push_back(cv::Point(x,y));  
                          }  
                     }  
                }  
          }  
  
   // 用圈圈標記角點  
    void  drawOnImage(cv::Mat &image,  
    const  std::vector<cv::Point> &points,  
            cv::Scalar color= cv::Scalar(255,255,255),  
            int  radius=3,  int  thickness=2) {  
                    std::vector<cv::Point>::const_iterator it=points.begin();  
                    while  (it!=points.end()) {  
                     //角點處畫圈  
                    cv::circle(image,*it,radius,color,thickness);  
                    ++it;  
            }  
    }  
  
};
#endif // HARRIS_H  


void harrispoint(double *x11,double *y11,double *x22,double *y22,double *x33,double *y33 )
{
	*x11=0;
    *x22=0;
	*x33=0;
	*y11=0;
	*y22=0;
	*y33=0;
	
	int Y1=0;
	int Y2=0;
	int X2=0;
	int X3=0;
   Mat src = imread("img1.jpg");
   int x1=0,x2=0,x3=0,y1=0,y2=0,y3=0;
   if(!src.empty()){
		//模糊
		 GaussianBlur(src,src,Size(5,5),1);
		//銳化 
		 Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
		 filter2D(src, src, src.depth(), kernel);
		// 灰度變換
		 cv::cvtColor (src,src,CV_BGR2GRAY);  
		 // 經典的harris角點方法  
		  harris Harris;  
		  // 計算角點  
		  Harris.detect(src);  
		  //獲得角點  
		  std::vector<cv::Point> pts;  
		  Harris.getCorners(pts,0.01);  
		  // 標記角點  
		  // Harris.drawOnImage(image,pts);
  

		  int first=0;
		 for(size_t i=0; i < pts.size(); i++)
		 {
		  Vec2i l = pts[i];
			 if(first==0){
			 x1=l[0];
			 x2=l[0];
			 x3=l[0];
			 y1=l[1];
			 y2=l[1];
			 y3=l[1];
			 first++;
			 }
			 //cout << l[0] << "," << l[1] << endl;
			 if(l[1]<y1){
			   y1=l[1];
			 }
			 if(l[1]>y2){
			  y2=l[1];
			 }
			 if(l[0]<x2){
			   x2=l[0];
			 }
			 if(l[0]>x3){
			  x3=l[0];
			}

		}
	 Y1=y1;
	 Y2=y2+15;
     X2=x2;
	 X3=x3;
	if(Y1<10)
		Y1=0;
	if(Y2>470)
		Y2=480;
	if(X2<10)
		X2=0;
	if(X3>630)
		X3=640;
   }
   else{
    x2=0;
	x3=0;
	y1=0;
	y2=0;
   }
	  
   Mat image;
   while(true){
	  if(y1==0 && y2==0 && x2==0 && x3==0){
	   	*x11=0;
		*y11=0;
		*x22=0;
		*y22=0;
		*x33=0;
		*y33=0;
		break;
	  }
   //cout << "Y1:" << Y1 << endl <<  "Y2:" << Y2 << endl << "X2:" << X2  << endl << "X3:" << X3 << endl;
   Mat mask = Mat(src.rows, src.cols, CV_32FC1);
   for(int i=0;i < src.rows; i++)
      for(int j=0;j < src.cols; j++)
	  {
       mask.at<float>(i,j) = 255;
      }
   for(int i=Y1;i < Y2; i++)
      for(int j=X2;j < X3; j++)
	  {
       mask.at<float>(i,j) = 0;
      }
   imwrite("mask1.jpg",mask);
   Mat img1 = imread("img1.jpg");
   Mat mask1 = imread("mask1.jpg");
   Mat out;
   img1.copyTo(out,mask1);
   //imshow("mask", mask);
  // imshow("out",out);
   imwrite("out.jpg",out);

   
   Mat image1 = out;  
    
  
  image = out;
  // 灰度變換
   cvtColor (image,image,CV_BGR2GRAY);  
   GaussianBlur( image, image, Size(9, 9), 2, 2 );
   GaussianBlur( image, image, Size(9, 9), 2, 2 );
   // 經典的harris角點方法  
   harris Harris;  
   // 計算角點  
   Harris.detect(image);  
   //獲得角點  
   vector<cv::Point> pts1;  
   Harris.getCorners(pts1,0.01);  
   // 標記角點  
  // Harris.drawOnImage(image,pts);  
   for(size_t i=0; i < pts1.size(); i++)
   {
     Vec2i l = pts1[i];
     //cout << l[0] << "," << l[1] << endl;
   }
   
  // cv::namedWindow ( "harris" );  
   //cv::imshow ( "harris" ,image );  
   imwrite("harriscorner.jpg",image);
   //cout << "以下為圓的頂點" << endl;
   vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( image, circles, CV_HOUGH_GRADIENT, 1, image.rows/8, 10, 10, 0, 0 );
  int time=0;
  
  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
	  //cout << i << endl;
	 // cout << circles[i][0] << "   " << circles[i][1] << endl;
      // circle center
      circle( image, center, 3, Scalar(255,0,0), -1, 8, 0 );
      // circle outline
      circle( image, center, radius, Scalar(0,0,255), 3, 8, 0 );
	  time++;
  }
  getoutcounter++;
  //cout << "做" << getoutcounter << "次了" << endl;
  if(getoutcounter>7){
		*x11=0;
		*y11=0;
		*x22=0;
		*y22=0;
		*x33=0;
		*y33=0;
		break;
  }
  //else if(X2==0 && Y2==480){
	 //   if(time==0){
		//		Y1=Y1+1;
		//	continue;
		//}
		//else{
		//*x11=circles[0][0];
		//*y11=circles[0][1];
		//}
		//if(x11==0){
		//	Y1=Y1+1;
		//}
		//else{
		//	*x22=0;
		//	*y22=0;
		//	*x33=0;
		//	*y33=0;
		//	break;
		//}
	 // }
  //else if(X2==0 && Y1==0){
	 //   if(time==0){
		//		X3=X3-1;
		//	continue;
		//}
		//else{
	 //   *x33=circles[0][0];
		//*y33=circles[0][1];
		//}
		//if(x33==0){
		//	X3=X3-1;
		//}
		//else{
		//	*x22=0;
		//	*y22=0;
		//	*x11=0;
		//	*y11=0;
		//	break;		
		//}

	 // }
  else if(X2==0){
	    if(time==0 || time==1){
				Y1=Y1+1;
				X3=X3-1;
			continue;
		}
		else if(circles[0][1]<circles[1][1]){
		*x11=circles[0][0];
		*y11=circles[0][1];
		*x33=circles[1][0];
		*y33=circles[1][1];
		}
		else{
		*x33=circles[0][0];
		*y33=circles[0][1];
		*x11=circles[1][0];
		*y11=circles[1][1];
		}
		if(x11==0){
			Y1=Y1+1;
		}
		if(x33==0){
			X3=X3-1;
		}
		if(getoutcounter>3){
			*x11=0;
			*y11=0;
			*x22=0;
			*y22=0;
			break;
		}
		if(x11!=0 && x33!=0){
			*x22=0;
			*y22=0;
			break;
		}
	  }
  //else if(X3==640 && Y1==0){
	 // 	if(time==0){
		//		X2=X2+1;
		//	continue;
		//}
		//else{
	 //   *x22=circles[0][0];
		//*y22=circles[0][1];
		//}
		//if(x22=0){
		//X2=X2+1;
		//}
		//else{
		//	*x33=0;
		//	*y33=0;
		//	*x11=0;
		//	*y11=0;
		//	break;
		//}
  //    }
  //else if(X3==640 && Y2==480){
	 //   if(time==0){
		//		Y1=Y1+1;
		//	continue;
		//}
		//else{
  //    	*x11=circles[0][0];
		//*y11=circles[0][1];
		//}
		//if(x11==0){
		//	Y1=Y1+1;
		//}
		//else{
		//	*x22=0;
		//	*y22=0;
		//	*x33=0;
		//	*y33=0;
		//	break;
		//}
  //    }
  else if(X3==640){
	    if(time==0 || time==1){
				Y1=Y1+1;
				X2=X2+1;
	        continue;
		}
	    else if(circles[0][1]<circles[1][1]){
        *x11=circles[0][0];
		*y11=circles[0][1];
		*x22=circles[1][0];
		*y22=circles[1][1];
		}
		else{
        *x22=circles[0][0];
		*y22=circles[0][1];
		*x11=circles[1][0];
		*y11=circles[1][1];
		}
		if(x11==0){
			Y1=Y1+1;
		}
		if(x22==0){
			X2=X2+1;
		}
		if(getoutcounter>3){
			*x11=0;
			*y11=0;
			*x33=0;
			*y33=0;
			break;
		}
		if(x11!=0 && x22!=0){
			*x33=0;
			*y33=0;
			break;
		}
      }
  else if(Y1==0){
	    if(time==0 || time==1){
				X2=X2+1;
				X3=X3-1;
	        continue;
		}
	    else if(circles[0][0]<circles[1][0]){
        *x22=circles[0][0];
		*y22=circles[0][1];
		*x33=circles[1][0];
		*y33=circles[1][1];
		}
		else{
        *x33=circles[0][0];
		*y33=circles[0][1];
		*x22=circles[1][0];
		*y22=circles[1][1];
		}
		if(x22==0){
			X2=X2+1;
		}
		if(x33==0){
			X3=X3-1;
		}
		if(x22!=0 && x33!=0){
			*x11=0;
			*y11=0;
			break;
		}
      }
  else if(Y2==480){
	    if(time==0){
				Y1=Y1+1;
	        continue;
		}
		else{
        *x11=circles[0][0];
		*y11=circles[0][1];
		}
		if(x11==0){
			Y1=Y1+1;
		}
		else{
			*x22=0;
			*y22=0;
			*x33=0;
			*y33=0;
			break;
		}

      }
  else{
	  	if(time==0 || time==1 || time==2){
				Y1=Y1+1;
				X2=X2+1;
				X3=X3-1;
		    continue;
		}
		else{
	    if(circles[0][1]<circles[1][1] && circles[0][1]<circles[2][1]){
        *x11=circles[0][0];
		*y11=circles[0][1];
			if(circles[1][0]<circles[2][0]){
			*x22=circles[1][0];
			*y22=circles[1][1];
			*x33=circles[2][0];
			*y33=circles[2][1];
			}
			else{
			*x33=circles[1][0];
			*y33=circles[1][1];
			*x22=circles[2][0];
			*y22=circles[2][1];
			}
		}
		
		if(circles[1][1]<circles[0][1] && circles[1][1]<circles[2][1]){
		*x11=circles[1][0];
		*y11=circles[1][1];
			if(circles[0][0]<circles[2][0]){
			*x22=circles[0][0];
			*y22=circles[0][1];
			*x33=circles[2][0];
			*y33=circles[2][1];
			}
			else{
			*x33=circles[0][0];
			*y33=circles[0][1];
			*x22=circles[2][0];
			*y22=circles[2][1];
			}
		}
		if(circles[2][1]<circles[0][1] && circles[2][1]<circles[1][1]){
		*x11=circles[2][0];
		*y11=circles[2][1];
			if(circles[0][0]<circles[1][0]){
			*x22=circles[0][0];
			*y22=circles[0][1];
			*x33=circles[1][0];
			*y33=circles[1][1];
			}
			else{
			*x33=circles[0][0];
			*y33=circles[0][1];
			*x22=circles[1][0];
			*y22=circles[1][1];
			}
		}
		}
		if(x11==0){
			Y1=Y1+1;
		}
		if(x22==0){
			X2=X2+1;
		}
		if(x33==0){
			X3=X3-1;
		}
		if(x11!=0)
			break;
		}
  time==0;
  }
  getoutcounter=0;
  /// Show your results
  //namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  //imshow( "Hough Circle Transform Demo", image );
  //imwrite("houghcircle.jpg",image);
}
