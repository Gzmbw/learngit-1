/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月14日 星期六 22时59分44秒
 ==========================================================================*/

#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
#include<time.h>
using namespace cv;
using namespace std;
int main(int argc,char* argv[]){
	Mat img=imread(argv[1]);
	Mat	new_img;
	float nr=img.rows;
	float nc=img.cols;
	float f=1.5;
	float a=f*nr;
	float b=f*nc;
	new_img.create(a,b,img.type());
	CvScalar m1,m2,m3,m4,sum;//一个结构体
	for(float i=0;i<a;i++){
		for(float j=0;j<b;j++){
			float x=i/f;
			float y=j/f;
			int x1=(int)x;
			int x2=(int)x+1;
			int y1=(int)y;
			int y2=(int)y+1;
			m1=img.at<Vec3b>(x1,y1);
			m2=img.at<Vec3b>(x2,y1);
			m3=img.at<Vec3b>(x1,y2);
			m4=img.at<Vec3b>(x2,y2);
			sum.val[0]=(y2-y)*(m1.val[0]*(x2-x)+m2.val[0]*(x-x1))  +  (y-y1)*(m3.val[0]*(x2-x)+m4.val[0]*(x-x1));//线性内插公式
			sum.val[1]=(y2-y)*(m1.val[1]*(x2-x)+m2.val[1]*(x-x1))  +  (y-y1)*(m3.val[1]*(x2-x)+m4.val[1]*(x-x1));
			sum.val[2]=(y2-y)*(m1.val[2]*(x2-x)+m2.val[2]*(x-x1))  +  (y-y1)*(m3.val[2]*(x2-x)+m4.val[2]*(x-x1));
			new_img.at<Vec3b>(i,j)[0]=sum.val[0]/((x2-x1)*(y2-y1));
			new_img.at<Vec3b>(i,j)[1]=sum.val[1]/((x2-x1)*(y2-y1));
			new_img.at<Vec3b>(i,j)[2]=sum.val[2]/((x2-x1)*(y2-y1));
		}
	}
	imwrite("result.jpg",new_img);

	waitKey(0);
	return 0;
}
