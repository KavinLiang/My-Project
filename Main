#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include "hsv.h"

using namespace cv;
using namespace std;

double rx1=34.25,rx2=28.2,rx3=39.9;
double ry1=26.45,ry2=16.4,ry3=16.4;
double yx1=7.85,yx2=2,yx3=13.7;
double yy1=26.45,yy2=3.4,yy3=3.4;
double gx1=7.85,gx2=2,gx3=13.7;
double gy1=26.45,gy2=16.4,gy3=16.4;
double bnx1=21,bnx2=15.1,bnx3=26.8;
double bny1=13.5,bny2=3.4,bny3=3.4;
double bx1=21,bx2=15.1,bx3=26.8;
double by1=26.45,by2=16.4,by3=16.4;
double px1=34.25,px2=28.2,px3=39.9;
double py1=13.5,py2=3.4,py3=3.4;
double realposition[6][6]={{rx1,ry1,rx2,ry2,rx3,ry3},
	                       {yx1,yy1,yx2,yy2,yx3,yy3},
						   {gx1,gy1,gx2,gy2,gx3,gy3},
					       {bnx1,bny1,bnx2,bny2,bnx3,bny3},
						   {bx1,by1,bx2,by2,bx3,by3},
						   {px1,py1,px2,py2,px3,py3}     };
double position[6][6]={0};//儲存各點位置
//hough use
double Xcompensation=0;//X補償量
double Ycompensation=0;//Y補償量
//harris use
double Xcompensation1=0;//X補償量
double Ycompensation1=0;//Y補償量
double firsttime=0;//初始化第一次用
double realdeep=27.47;//實際深度   
double deepfocus=0;//紀錄
double deepfocus1=0;
double reallength[18*18]={0};//紀錄實際距離點之間長度

  int HueHigh1=0;
  int HueLow1=0;
  int HueHigh[6]={0};
  int HueLow[6]={0};
  int SatHigh[6]={0};
  int SatLow[6]={0};
  int ValHigh[6]={0};
  int ValLow[6]={0};//紀錄各顏色值的trackbar位置
  int a=0,b=0,c=0,d=0,e=0,f=0,g=0;
	
int main()
{					
	if(firsttime==0){
	int counter1=0;
	//cout << "實際距離: " << endl;
	for(int i=0; i<6 ; i++)
		for(int j=0 ; j<6 ; j+=2)
			for(int k=0; k<6 ; k++)
				for(int l=0; l<6 ; l+=2)
				{
				   double a1=sqrt(pow(double(realposition[i][j]-realposition[k][l]),2)+pow(double(realposition[i][j+1]-realposition[k][l+1]),2));
				   
					   reallength[counter1]=a1;
					   //cout << reallength[counter1] << "         ";
				       counter1++; 					   
				   
				}//實際長度的每個點間距離
	//cout << counter1 << "<< counter1" << endl;
	}
	


	VideoCapture cap(0);
	if(!cap.isOpened()) // check if we succeeded
     return -1;
    Mat src;

	
   namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
   cvResizeWindow("Control",300,400);
   int iLowH = 0;
   int iHighH = 179;

   int iLowS = 0; 
   int iHighS = 255;

   int iLowV = 0;
   int iHighV = 255;

   int iLowH1=0;
   int iHighH1=179;
    //Create trackbars in "Control" window
   cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
   cvCreateTrackbar("HighH", "Control", &iHighH, 179);

   cvCreateTrackbar("LowH1", "Control", &iLowH1, 179); //Hue1 (0 - 179)
   cvCreateTrackbar("HighH1", "Control", &iHighH1, 179);

   cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
   cvCreateTrackbar("HighS", "Control", &iHighS, 255);

   cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
   cvCreateTrackbar("HighV", "Control", &iHighV, 255);


	//double yesornot[6]={0};//紀錄各底長
	//src = imread("source.jpg");
	if(g==0){
		cout << "請先調紅色，並按A儲存，請用大寫。" << endl;
		g++;
	}//60,140,70馬達位置
	while(true)
	{
		cap.read(src);

		Mat imgHSV;

	   cvtColor(src, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
	   Mat imgThresholded;
	   Mat imgThresholded1;

	   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
	   inRange(imgHSV, Scalar(iLowH1, iLowS, iLowV), Scalar(iHighH1, iHighS, iHighV), imgThresholded1); //Threshold the image
	   imgThresholded = imgThresholded + imgThresholded1;
	   erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
       dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
	   dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
       erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
   if(waitKey(10) == 65)
	   {
	   if(a==0){
	   HueHigh[0] = cvGetTrackbarPos("LowH", "Control");
	   HueLow[0] = cvGetTrackbarPos("HighH", "Control");
	   SatHigh[0] = cvGetTrackbarPos("LowS", "Control");
	   SatLow[0] = cvGetTrackbarPos("HighS", "Control");
	   ValHigh[0] = cvGetTrackbarPos("LowV", "Control");
	   ValLow[0] = cvGetTrackbarPos("HighV", "Control");
	   HueHigh1 = cvGetTrackbarPos("LowH1", "Control");
	   HueLow1 = cvGetTrackbarPos("HighH1", "Control");
	   a++;
	   }
	   if(a==1){
	   cvSetTrackbarPos("LowH", "Control",HueHigh[0]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[0]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[0]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[0]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[0]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[0]);
	   cvSetTrackbarPos("LowH1", "Control",HueHigh1);
	   cvSetTrackbarPos("HighH1", "Control",HueLow1);
	   }
	   cout << "儲存完成，在調黃色，按S儲存。" << endl;
   }
   if(waitKey(10) == 83)
   {
	   if(b==0){
	   HueHigh[1] = cvGetTrackbarPos("LowH", "Control");
	   HueLow[1] = cvGetTrackbarPos("HighH", "Control");
	   SatHigh[1] = cvGetTrackbarPos("LowS", "Control");
	   SatLow[1] = cvGetTrackbarPos("HighS", "Control");
	   ValHigh[1] = cvGetTrackbarPos("LowV", "Control");
	   ValLow[1] = cvGetTrackbarPos("HighV", "Control");
	   b++;
	   }
	   if(b==1){
	   cvSetTrackbarPos("LowH", "Control",HueHigh[1]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[1]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[1]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[1]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[1]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[1]);
	   }
	    cout << "儲存完成，在調綠色，按D儲存。" << endl;
   }
   if(waitKey(10) == 68)
   {
	   if(c==0){
   	   HueHigh[2] = cvGetTrackbarPos("LowH", "Control");
	   HueLow[2] = cvGetTrackbarPos("HighH", "Control");
	   SatHigh[2] = cvGetTrackbarPos("LowS", "Control");
	   SatLow[2] = cvGetTrackbarPos("HighS", "Control");
	   ValHigh[2] = cvGetTrackbarPos("LowV", "Control");
	   ValLow[2] = cvGetTrackbarPos("HighV", "Control");
	   c++;
	   }
	   if(c==1){
	   cvSetTrackbarPos("LowH", "Control",HueHigh[2]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[2]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[2]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[2]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[2]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[2]);
	   }
	    cout << "儲存完成，在調青色，按Z儲存。" << endl;
   }
   if(waitKey(10) == 90)
   {
	   if(d==0){
   	   HueHigh[3] = cvGetTrackbarPos("LowH", "Control");
	   HueLow[3] = cvGetTrackbarPos("HighH", "Control");
	   SatHigh[3] = cvGetTrackbarPos("LowS", "Control");
	   SatLow[3] = cvGetTrackbarPos("HighS", "Control");
	   ValHigh[3] = cvGetTrackbarPos("LowV", "Control");
	   ValLow[3] = cvGetTrackbarPos("HighV", "Control");	
	   d++;
	   }
	   if(d==1){
	   cvSetTrackbarPos("LowH", "Control",HueHigh[3]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[3]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[3]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[3]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[3]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[3]);
	   }
	    cout << "儲存完成，在調藍色，按X儲存" << endl;
   }
   if(waitKey(10) == 88)
   {
	   if(e==0){
   	   HueHigh[4] = cvGetTrackbarPos("LowH", "Control");
	   HueLow[4] = cvGetTrackbarPos("HighH", "Control");
	   SatHigh[4] = cvGetTrackbarPos("LowS", "Control");
	   SatLow[4] = cvGetTrackbarPos("HighS", "Control");
	   ValHigh[4] = cvGetTrackbarPos("LowV", "Control");
	   ValLow[4] = cvGetTrackbarPos("HighV", "Control");	
	   e++;
	   }
	   if(e==1){
	   cvSetTrackbarPos("LowH", "Control",HueHigh[4]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[4]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[4]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[4]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[4]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[4]);
	   }
	    cout << "儲存完成，調色完畢，按C儲存。" << endl;
   }
   if(waitKey(10) == 67)
   {
	   if(f==0){
   	   HueHigh[5] = cvGetTrackbarPos("LowH", "Control");
	   HueLow[5] = cvGetTrackbarPos("HighH", "Control");
	   SatHigh[5] = cvGetTrackbarPos("LowS", "Control");
	   SatLow[5] = cvGetTrackbarPos("HighS", "Control");
	   ValHigh[5] = cvGetTrackbarPos("LowV", "Control");
	   ValLow[5] = cvGetTrackbarPos("HighV", "Control");	
	   f++;
	   }
	   if(f==1){
	   cvSetTrackbarPos("LowH", "Control",HueHigh[5]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[5]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[5]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[5]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[5]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[5]);
	   }
	    cout << "儲存完畢，將位置移回原點，再按Q鍵至下一階段。" << endl;
   }
   Mat output;
   src.copyTo(output,imgThresholded);
   imshow("Thresholded Image", imgThresholded); //show the thresholded image
   imshow("Original", src); //show the original image
   imshow("Output", output);

   if(waitKey(30) == 81)//調完後空白鍵離開
   { break;
     destroyWindow("Thresholded Image");
	 destroyWindow("Original");
	 destroyWindow("Output");
   }

  }
 // 以上為顏色調整初始
  CvScalar Color;
  int Thickness;
  int Shift;
    Color=CV_RGB(255,0,0);
    Thickness=1;
    Shift=0;
  CvPoint FromPoint1 = cvPoint(192,470);
  CvPoint ToPoint1 = cvPoint(424,470);
  CvPoint FromPoint2 = cvPoint(192,210);
  CvPoint ToPoint2 = cvPoint(424,210);

  while(true)
  {
	cap.read(src);
	line(src,FromPoint1,ToPoint1,Color,Thickness,CV_AA,Shift);
    line(src,FromPoint2,ToPoint2,Color,Thickness,CV_AA,Shift);
	//line(src,FromPoint3,ToPoint3,Color,Thickness,CV_AA,Shift);
	imshow("Original", src);
	double x1,y1,x2,y2,x3,y3;
	while(true){
	Mat imgHSV;
    Mat dst;
    cvtColor(src, imgHSV, COLOR_BGR2HSV);

	   cvSetTrackbarPos("LowH", "Control",HueHigh[3]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[3]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[3]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[3]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[3]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[3]);//提取顏色位置


    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), dst); //Threshold the image
    erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
    dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
	dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
    erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
	hough(dst,&x1,&y1,&x2,&y2,&x3,&y3);
	cout << "青:" << endl;
	cout << x2 << "," << y2 << endl;
	cout << x3 << "," << y3 << endl;
	int out=0;
	if((y2-y3)<2 && (y2-y3)>-2){
      out=1;
	}
	else{
	  out=0;
	}
	cvtColor(src, imgHSV, COLOR_BGR2HSV);

	   cvSetTrackbarPos("LowH", "Control",HueHigh[4]);
	   cvSetTrackbarPos("HighH", "Control",HueLow[4]);
	   cvSetTrackbarPos("LowS", "Control",SatHigh[4]);
	   cvSetTrackbarPos("HighS", "Control",SatLow[4]);
	   cvSetTrackbarPos("LowV", "Control",ValHigh[4]);
	   cvSetTrackbarPos("HighV", "Control",ValLow[4]);//提取顏色位置


    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), dst); //Threshold the image
    erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
    dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
	dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
    erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
	hough(dst,&x1,&y1,&x2,&y2,&x3,&y3);
	cout << "藍:" << endl;
	cout << x2 << "," << y2 << endl;
	cout << x3 << "," << y3 << endl;
	if((y2-y3)<2 && (y2-y3)>-2){
      out=2;
	}
	else{
	  out=0;
	}
	if(out==2)
		break;
	}
	cout << "按復歸回到原點，到達原點後，按空白鍵離開" << endl;
	if(waitKey(100000) == 32){
		cap.read(src);
		break;
	}
  }
 // 以下開始計算位置
    int choose=1;
   while(true){
	cap.read(src);
	
   //  1=r; 2=y; 3=g; 4=bn; 5=b; 6=p
	double x1,y1,x2,y2,x3,y3;		
	//x1&y1是第一條與第三條邊的交角  
	//x2&y2是第一條與第二條邊的交角 
	//x3&y3是第二條與第三條邊的交角

	if(choose==1){
		cout << "hough: " << endl;
		for(int i=1; i<7 ; i++){
		  Mat imgHSV;
		  Mat dst;
		 cvtColor(src, imgHSV, COLOR_BGR2HSV);

		   cvSetTrackbarPos("LowH", "Control",HueHigh[i-1]);
		   cvSetTrackbarPos("HighH", "Control",HueLow[i-1]);
		   cvSetTrackbarPos("LowS", "Control",SatHigh[i-1]);
		   cvSetTrackbarPos("HighS", "Control",SatLow[i-1]);
		   cvSetTrackbarPos("LowV", "Control",ValHigh[i-1]);
		   cvSetTrackbarPos("HighV", "Control",ValLow[i-1]);//提取顏色位置
		if(i==1){
		   cvSetTrackbarPos("LowH1", "Control",HueHigh1);
		   cvSetTrackbarPos("HighH1", "Control",HueLow1);   
		}

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), dst); //Threshold the image
		erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
		dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
		dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
		erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
		hough(dst,&x1,&y1,&x2,&y2,&x3,&y3);
		position[i-1][0]=x1;
		position[i-1][1]=y1;
		position[i-1][2]=x2;
		position[i-1][3]=y2;
		position[i-1][4]=x3;
		position[i-1][5]=y3;//將各點計算值放入矩陣
			   if(i==1)
				   cout << "紅:" << endl;
			   if(i==2)
				   cout << "黃:" << endl;
			   if(i==3)
				   cout << "綠:" << endl;
			   if(i==4)
				   cout << "青:" << endl;
			   if(i==5)
				   cout << "藍:" << endl;
			   if(i==6)
				   cout << "紫:" << endl;
		cout << setprecision(8) << position[i-1][0] << "," << position[i-1][1] << endl;
		cout << setprecision(8) << position[i-1][2] << "," << position[i-1][3] << endl;
		cout << setprecision(8) << position[i-1][4] << "," << position[i-1][5] << endl;
		if( (position[i-1][5]-position[i-5][3])<4 && (position[i-1][5]-position[i-5][3])>-4){
		  position[i-1][2]=0;
		  position[i-1][3]=0;
		  position[i-1][4]=0;
		  position[i-1][5]=0;
		}

  		}
	}
	if(choose==2){
		cout << "harris: " << endl;
		for(int i=1; i<7 ; i++){
		  Mat imgHSV;
		  Mat dst;
		 cvtColor(src, imgHSV, COLOR_BGR2HSV);

		   cvSetTrackbarPos("LowH", "Control",HueHigh[i-1]);
		   cvSetTrackbarPos("HighH", "Control",HueLow[i-1]);
		   cvSetTrackbarPos("LowS", "Control",SatHigh[i-1]);
		   cvSetTrackbarPos("HighS", "Control",SatLow[i-1]);
		   cvSetTrackbarPos("LowV", "Control",ValHigh[i-1]);
		   cvSetTrackbarPos("HighV", "Control",ValLow[i-1]);//提取顏色位置
		if(i==1){
		   cvSetTrackbarPos("LowH1", "Control",HueHigh1);
		   cvSetTrackbarPos("HighH1", "Control",HueLow1);   
		}

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), dst); //Threshold the image
		erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
		dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
		dilate( dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
		erode(dst, dst, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
		imwrite("img1.jpg",dst);
		harrispoint(&x1,&y1,&x2,&y2,&x3,&y3);
		position[i-1][0]=x1;
		position[i-1][1]=y1;
		position[i-1][2]=x2;
		position[i-1][3]=y2;
		position[i-1][4]=x3;
		position[i-1][5]=y3;//將各點計算值放入矩陣
			   if(i==1)
				   cout << "紅:" << endl;
			   if(i==2)
				   cout << "黃:" << endl;
			   if(i==3)
				   cout << "綠:" << endl;
			   if(i==4)
				   cout << "青:" << endl;
			   if(i==5)
				   cout << "藍:" << endl;
			   if(i==6)
				   cout << "紫:" << endl;
		cout << setprecision(8) << position[i-1][0] << "," << position[i-1][1] << endl;
		cout << setprecision(8) << position[i-1][2] << "," << position[i-1][3] << endl;
		cout << setprecision(8) << position[i-1][4] << "," << position[i-1][5] << endl;
		if( (position[i-1][5]-position[i-5][3])<4 && (position[i-1][5]-position[i-5][3])>-4){
		  position[i-1][2]=0;
		  position[i-1][3]=0;
		  position[i-1][4]=0;
		  position[i-1][5]=0;
		}

  		}
	}

	int counter=0;
	double length[18*18]={0};
	double a0=0;
	for(int i=0; i<6 ; i++)
		for(int j=0 ; j<6 ; j+=2)
			for(int k=0; k<6 ; k++)
				for(int l=0; l<6 ; l+=2)
				{
                   if(position[i][j]!=0 && position[k][l]!=0)
					   a0=sqrt(pow(double(position[i][j]-position[k][l]),2)+pow(double(position[i][j+1]-position[k][l+1]),2));
				   else
					   a0=0;

					   length[counter]=a0;
				       counter++; 					   
				   
				}//算出各點間距離

	double allproportion[18*18]={0};
	double allfocus[18*18]={0}; 



	//cout << "比例" << endl;
    for(int i=0; i<counter; i++){
		if(reallength[i]!=0 && length[i]!=0 ){
			allproportion[i]=length[i]/reallength[i];//所有線段的比例
		}
		else
			allproportion[i]=0;  //確定有哪些長度有值

		if(reallength[i]!=0 && length[i]!=0){
			allfocus[i]=length[i]*realdeep/reallength[i];//所有線段的焦距
		}
		else
			allfocus[i]=0;  //確定有哪些焦距有值
	}
	//************比例演算*************//
	double proportionavg=0;
	double proportiontotal=0;
	double proportioncount=0;
	for(int i=0; i<counter; i++){
	  if(allproportion[i]!=0){
		  proportioncount++;
		  proportiontotal = allproportion[i] + proportiontotal;
	  }
	}
	proportionavg = proportiontotal / proportioncount;
	double totalproportionsigma=0;
	for(int i=0; i<counter; i++){
	  if(allproportion[i]!=0){
	    totalproportionsigma = pow((allproportion[i]-proportionavg),2) + totalproportionsigma;
	  }
	}
	double proportionsigma = sqrt(totalproportionsigma/proportioncount);
	//cout << "proportionsigma:" << proportionsigma << endl;
	double weight=0;
	double totalweightproportion=0;
	for(int i=0; i<counter; i++){
      if(allproportion[i]!=0){
		  if((allproportion[i]-proportionavg)<proportionsigma && (allproportion[i]-proportionavg)>-proportionsigma ){
		    //cout << "第" << i << "個" << allproportion[i] << endl;
		    weight = weight + allproportion[i]*length[i];//長度加權
			totalweightproportion = totalweightproportion + length[i];
			//fp << allfocus[i] << endl;
		  }
	  }
	}
	double proportion = weight/totalweightproportion;//實際與圖像長度比例
	proportiontotal=0;
	weight=0;
	totalweightproportion=0;
	//cout << proportion << "<<加權過後比例" << endl;
	//************比例演算*************//

	//************焦距演算*************//
	double focusavg=0;
	double focustotal=0;
	double focuscount=0;
	for(int i=0; i<counter; i++){
	  if(allfocus[i]!=0){
		  focuscount++;
		  focustotal = allfocus[i] + focustotal;
	  }
	}
	focusavg = focustotal / focuscount;
	double totalfocussigma=0;
	for(int i=0; i<counter; i++){
	  if(allfocus[i]!=0){
	    totalfocussigma = pow((allfocus[i]-focusavg),2) + totalfocussigma;
	  }
	}
	double focussigma = 0;
	focussigma = sqrt(totalfocussigma/focuscount);
    double deepweight=0;
	double totalweight=0;
	//cout << "focussigma:" << focussigma << endl;
	for(int i=0; i<counter; i++){
	  if((allfocus[i]-focusavg)<focussigma && (allfocus[i]-focusavg)>-focussigma ){
	    deepweight = deepweight + allfocus[i]*length[i];
		totalweight = totalweight + length[i];
		
	  }
	}

	if(firsttime==0){
		if(choose==1)
			deepfocus = deepweight/totalweight;  //初始計算Zfocuse 
		if(choose==2)
			deepfocus1 = deepweight/totalweight;
	}		
	double deep=0;
	if(choose==1){
	for(int i=0; i<counter; i++){
		if(length[i]!=0 && (allfocus[i]-focusavg)<focussigma && (allfocus[i]-focusavg)>-focussigma)
		deep = deep + (deepfocus*reallength[i]/length[i])*length[i];
		else
			continue;
	}//深度計算hough
	}
	if(choose==2){
	for(int i=0; i<counter; i++){
		if(length[i]!=0 && (allfocus[i]-focusavg)<focussigma && (allfocus[i]-focusavg)>-focussigma)
		deep = deep + (deepfocus1*reallength[i]/length[i])*length[i];
		else
			continue;
	}//深度計算harris
	}
	//cout << deepfocus << ":deepfocus" << endl;
	//cout << deepfocus1 << ":deepfocus1" << endl;

	//************焦距演算*************//

	//cout << "deep:" << deep <<  endl;
	//cout << "deep/totalweight:" << deep/totalweight << endl;
	double Zposition=deep/totalweight-realdeep;//實際Z
	double Xposition=0;
	double Yposition=0;
	double totalXYweight=0;
	//totalfocussigma=0;
	//focustotal=0;
	//deepweight=0;
	//totalweight=0;
	//deep=0;
	//************實距演算*************//
	for(int i=0; i<6; i++)
		for(int j=0; j<6; j+=2)
		{
			double a1=sqrt(pow(double(position[i][j]-319),2)+pow(double(position[i][j+1]-239),2));
			if(position[i][j]!=0){
				Xposition = Xposition + (realposition[i][j]-(position[i][j]-319)/proportion)*a1;
				Yposition = Yposition + (realposition[i][j+1]+(position[i][j+1]-239)/proportion)*a1;
				//cout << "X,Y=" << realposition[i][j]-(position[i][j]-319)/proportion << "," << realposition[i][j+1]+(position[i][j+1]-239)/proportion << endl;
				totalXYweight = totalXYweight + a1;
			}
			else
				continue;
		}//實際XY計算
	//************實距演算*************//
	

	//************實距穩定度演算*************//
    double Xavg = Xposition / totalXYweight;
	double Yavg = Yposition / totalXYweight;
	double totalXsigma=0;
	double totalYsigma=0;
	int sigmacount=0;
	for(int i=0; i<6; i++)
		for(int j=0; j<6; j+=2)
		{
			double a1=sqrt(pow(double(position[i][j]-319),2)+pow(double(position[i][j+1]-239),2));
			if(position[i][j]!=0){
				double Xcom = realposition[i][j]-(position[i][j]-319)/proportion;
				double Ycom = realposition[i][j+1]+(position[i][j+1]-239)/proportion;
				totalXsigma = pow((Xcom-Xavg),2) + totalXsigma;
				totalYsigma = pow((Ycom-Yavg),2) + totalYsigma;
				sigmacount++;
			}
			else
				continue;
		}//計算標準差
    double Xsigma = sqrt(totalXsigma/sigmacount);
	double Ysigma = sqrt(totalYsigma/sigmacount); 
	//cout << "Xsimga:" << Xsigma << "   Ysigma:" << Ysigma << endl;
	Xposition=0;
	Yposition=0;
	totalXYweight=0;
	//cout << "篩選後: " << endl;
	for(int i=0; i<6; i++)
		for(int j=0; j<6; j+=2)
		{
			double a1=sqrt(pow(double(position[i][j]-319),2)+pow(double(position[i][j+1]-239),2));
			if(position[i][j]!=0){
				double Xcom = realposition[i][j]-(position[i][j]-319)/proportion;
				double Ycom = realposition[i][j+1]+(position[i][j+1]-239)/proportion;
				if(Xsigma<1 && Ysigma<1){
				    Xposition = Xposition + (realposition[i][j]-(position[i][j]-319)/proportion)*a1;
					Yposition = Yposition + (realposition[i][j+1]+(position[i][j+1]-239)/proportion)*a1;
					//cout << "X,Y=" << realposition[i][j]-(position[i][j]-319)/proportion << "," << realposition[i][j+1]+(position[i][j+1]-239)/proportion << endl;
					totalXYweight = totalXYweight + a1;
		        }
				else if( (Xcom-Xavg)<Xsigma && (Xcom-Xavg)>-Xsigma){
				  if( (Ycom-Yavg)<Ysigma && (Ycom-Yavg)>-Ysigma ){
        			Xposition = Xposition + (realposition[i][j]-(position[i][j]-319)/proportion)*a1;
					Yposition = Yposition + (realposition[i][j+1]+(position[i][j+1]-239)/proportion)*a1;
					//cout << "X,Y=" << realposition[i][j]-(position[i][j]-319)/proportion << "," << realposition[i][j+1]+(position[i][j+1]-239)/proportion << endl;
					totalXYweight = totalXYweight + a1;
				  }
				}

				else
					continue;
			}
			else
				continue;
		}//在算一次增加穩定度
    //************實距穩定度演算*************//
	double realX = 0;
	double realY = 0;
	if(firsttime==1){
		if(choose==1){
		realX = (Xposition / totalXYweight)-Xcompensation;//實際X
		realY = (Yposition / totalXYweight)-Ycompensation;//實際Y
		cout << "hough:~~~" << endl;
		}
		if(choose==2){
		cout << "harris~~~:" << endl;
		realX = (Xposition / totalXYweight)-Xcompensation1;//實際X
		realY = (Yposition / totalXYweight)-Ycompensation1;//實際Y

		}
		cout << "實際位置X:" << -realX*10 << endl;
	    cout << "實際位置Y:" << realY*10 << endl;
	    cout << "實際位置Z:" << Zposition*10 << endl; 	

	  if(choose==1){
		    char filename[]="houghcout.txt";
		    fstream fp;
	     	fp.open(filename, ios::out);
		  	fp << -realX*10 << endl;
			fp <<  Zposition*10 << endl;
			fp << realY*10 << endl;
		    choose=2;
	  }
	  else if(choose==2){
			char filename1[]="harriscout.txt";
			fstream fp1;
			fp1.open(filename1, ios::out);
		  	fp1 << -realX*10 << endl;
			fp1 << Zposition*10 << endl;
			fp1 << realY*10 << endl;
		    choose=1;
	  }
	}
	if(firsttime==0){
		if(choose==1){
		Xcompensation = (Xposition / totalXYweight)-Xcompensation; //hough初始補償量X
		Ycompensation = (Yposition / totalXYweight)-Ycompensation; //hough初始補償量Y
		cout << "X補償量: " << Xcompensation << endl;
		cout << "Y補償量: " << Ycompensation << endl;
		choose=2;
		}
		else if(choose==2){
        Xcompensation1 = (Xposition / totalXYweight)-Xcompensation1; //harris初始補償量X
		Ycompensation1 = (Yposition / totalXYweight)-Ycompensation1; //harris初始補償量Y
		cout << "X補償量: " << Xcompensation1 << endl;
		cout << "Y補償量: " << Ycompensation1 << endl;
		choose=1;
		firsttime=1;
		}
	}
    imshow("source", src);
	if(waitKey(30)==27)
		break;
    //waitKey(0);
    }
	//imwrite("source.jpg",src);
    //waitKey(0);
	
}
