#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <iomanip> 

using namespace cv;
using namespace std;

void hough(Mat dst,double *x1,double *y1,double *x2,double *y2,double *x3,double *y3)
{
	*x1=0;
    *x2=0;
	*x3=0;
	*y1=0;
	*y2=0;
	*y3=0;
	Mat ccdst;

	Canny(dst, dst, 50, 200, 3); 
	//dilate( dst, dst, 5);
 //   erode( dst, dst, 5);

	cvtColor(dst, ccdst, CV_GRAY2BGR);

	vector<Vec4i> lines1;
    HoughLinesP(dst, lines1, 1, CV_PI/180, 10, 30, 50 );
	vector<double> slope(1000);
	//各個斜率
	vector<int> slopeplus(100);
	vector<int> slopeminus(100);
	vector<int> slopezero(100);
	//斜率分類，紀錄位置
	int plus=0;
	int minus=0;
	int zero=0;
	//紀錄位置次數
	double plusx=0;
	double plusy=0;
	double minusx=0;
	double minusy=0;
	double zerox=0;
	double zeroy=0;
	double slope1=0;
	double slope2=0;
	double slope3=0;
	for( size_t i = 0; i < lines1.size(); i++ )
	{
		Vec4f l = lines1[i];
		line( ccdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
		slope[i] = (l[3]-l[1])/(l[2]-l[0]);
		//cout << l[0] << "," << l[1] << "到" << l[2] << "," << l[3] << endl;
		//cout << slope[i];
		if(slope[i]>1.5 && slope[i]<1.85){
			slopeplus[plus] = i;
			plusx = plusx + l[0] + l[2];
			plusy = plusy + l[1] + l[3];
			slope1 = slope1 +slope[i];
			plus++;
		}
		if(slope[i]>-0.3 && slope[i]<0.3){
			slopezero[zero] = i;
			zerox = zerox + l[0] + l[2];
			zeroy = zeroy + l[1] + l[3];
			slope2 = slope2 +slope[i];
			zero++;
		}
		if(slope[i]<-1.5 && slope[i]>-1.85){
			slopeminus[minus] = i;
			minusx = minusx + l[0] + l[2];
			minusy = minusy + l[1] + l[3];
			slope3 = slope3 +slope[i];
			minus++;
		}
	}
	//cout << plus << "    " << zero << "    " << minus << "   "  << endl;
	if(plus!=0){
	plusx = plusx/(2*plus);
	plusy = plusy/(2*plus);
	slope1 = slope1/plus;
	}
	if(zero!=0){
	zerox = zerox/(2*zero);
	zeroy = zeroy/(2*zero);
	slope2 = slope2/zero;
	}
	if(minus!=0){
	minusx = minusx/(2*minus);
	minusy = minusy/(2*minus);
	slope3 = slope3/minus;
	}
 //   cout << "plus: " << plusx << "," << plusy << endl <<"slope1: " << slope1 << endl;
	//cout << "zero: " << zerox << "," << zeroy << endl <<"slope2: " << slope2 << endl;
	//cout << "minus: " << minusx << "," << minusy << endl <<"slope3: " << slope3 << endl;

	double a1=-slope1;
	double b1=1;
	double c1=-a1*plusx-b1*plusy;
	double a2=-slope2;
	double b2=1;
	double c2=-a2*zerox-b2*zeroy;
	double a3=-slope3;
	double b3=1;
	double c3=-a3*minusx-b3*minusy;

    //double angle1=(a1*a2+b1*b2)/(sqrt(pow(double(a1),2)+pow(double(b1),2))*sqrt(pow(double(a2),2)+pow(double(b2),2)));
	//double angle2=(a1*a3+b1*b3)/(sqrt(pow(double(a1),2)+pow(double(b1),2))*sqrt(pow(double(a3),2)+pow(double(b3),2)));
	//double angle3=(a3*a2+b3*b2)/(sqrt(pow(double(a3),2)+pow(double(b3),2))*sqrt(pow(double(a2),2)+pow(double(b2),2)));
	//angle1 = acos(angle1)*180/3.14;
	//angle2 = acos(angle2)*180/3.14;
	//angle3 = acos(angle3)*180/3.14;
	//if(angle1 > 90)
	//	angle1 = 180 - angle1;
	//if(angle2 > 90)
	//	angle2 = 180 - angle2;
	//if(angle3 > 90)
	//	angle3 = 180 - angle3;
	//cout << "角度1:" << angle1 << "  角度2: " << angle2 << "  角度3: " << angle3 << endl;

	double X1,X2,X3,Y1,Y2,Y3=0;
	if(plus==0 ||  minus==0){
		*x1=0;
		*y1=0;
	}
	else{
		X1 = (b1*c3-b3*c1)/(a1*b3-b1*a3);
		Y1 = (a1*c3-a3*c1)/(b1*a3-a1*b3);
		if(X1<0 || X1>640 || Y1<0 || Y1>480){
			*x1=0;
			*y1=0;
		}
		else{
			*x1=X1;
			*y1=Y1;
		}
	}
	if(plus==0 || zero==0){
		*x2=0;
		*y2=0;
	}
	else{
		X2 = (b2*c3-b3*c2)/(a2*b3-b2*a3);
		Y2 = (a2*c3-a3*c2)/(b2*a3-a2*b3);	
		if(X2<0 || X2>640 || Y2<0 || Y2>480){
			*x2=0;
			*y2=0;
		}
		else{
			*x2=X2;
			*y2=Y2;		
		}
	}
	if(zero==0 || minus==0){
		*x3=0;
		*y3=0;
	}
	else{
		X3 = (b1*c2-b2*c1)/(a1*b2-b1*a2);
		Y3 = (a1*c2-a2*c1)/(b1*a2-a1*b2);	
		if(X3<0 || X3>640 || Y3<0 || Y3>480){
			*x3=0;
			*y3=0;
		}
		else{
			*x3=X3;
			*y3=Y3;
		}   
	}
	//if(plus==0 || zero==0 || minus==0){
	//	*x1=0;
	//	*y1=0;
	//	*x2=0;
	//	*y2=0;
	//	*x3=0;
	//	*y3=0;
	//}
	//else{
	//	X3 = (b1*c2-b2*c1)/(a1*b2-b1*a2);
	//	Y3 = (a1*c2-a2*c1)/(b1*a2-a1*b2);
	//	X1 = (b1*c3-b3*c1)/(a1*b3-b1*a3);
	//	Y1 = (a1*c3-a3*c1)/(b1*a3-a1*b3);
	//	X2 = (b2*c3-b3*c2)/(a2*b3-b2*a3);
	//	Y2 = (a2*c3-a3*c2)/(b2*a3-a2*b3);
	//	if(X1<0 || X1>640 || Y1<0 || Y1>480){
	//		*x1=0;
	//		*y1=0;
	//	}
	//	else{
	//		*x1=X1;
	//		*y1=Y1;
	//	}
	//	if(X2<0 || X2>640 || Y2<0 || Y2>480){
	//		*x2=0;
	//		*y2=0;
	//	}
	//	else{
	//		*x2=X2;
	//		*y2=Y2;		
	//	}
	//	if(X3<0 || X3>640 || Y3<0 || Y3>480){
	//		*x3=0;
	//		*y3=0;
	//	}
	//	else{
	//		*x3=X3;
	//		*y3=Y3;
	//	}   

    imwrite("houghline.jpg",ccdst);
	//}
	/*cout << "頂點:" << endl;
	cout << setprecision(8) << x1 << "," << y1 << endl << x2 << "," << y2 << endl << x3 << "," << y3 << endl;
    */
	//imshow("detected lines1", ccdst);
	
}
