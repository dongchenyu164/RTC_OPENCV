/*
 * imProcessLib.cpp
 *
 *  Created on: 2017/05/25
 *      Author: cook
 */

// ======================================================================
//
//	include
//
// =======================================================================
#include "imProcessLib.h"
#include <time.h>
#include <random>
#include <vector>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#define IMAGE_WIDTH 640
#define IMAGE_HIGH 480
using namespace cv;
// ======================================================================
//
//	program
//
// =======================================================================

void cvt_RTCcolor_to_CVcolor(RTC::CameraImage& rtc_color, cv::Mat& color) {

	// ========== color convert RTC -> opencv ==============
	int len = 640 * 480 * 3;
	cv::Size imageSize = cv::Size(640, 480);
	color = cv::Mat(imageSize, CV_8UC3);

	memcpy(color.data, (void*) &(rtc_color.pixels[0]), len);

}

void cvt_RTCdepth_to_CVdepth(RTC::CameraImage& rtc_depth, cv::Mat& depth) {

	// ========== color convert RTC -> opencv ==============
	int len = 640 * 480;
	cv::Size imageSize = cv::Size(640, 480);
	depth = cv::Mat(imageSize, CV_16UC1);

	memcpy(depth.data, (void*) &(rtc_depth.pixels[0]), len);

}
void cvt_RTCir_to_CVir(RTC::CameraImage& rtc_ir, cv::Mat& ir) {

	// ========== color convert RTC -> opencv ==============
	int len = 640 * 480;
	cv::Size imageSize = cv::Size(640, 480);
	ir = cv::Mat(imageSize, CV_8UC1);

	memcpy(ir.data, (void*) &(rtc_ir.pixels[0]), len);

}


const int Limit_ContourNUM = 80;
const int Limit_Distance = 75;//连通域中心 偏离 图像中心的距离 最大值。（假设杯子在正中央）

int CalERROR_inCircleAndEdge(Vec3f Circle, std::vector<cv::Point> PointCollection, int ErrorLimit = 4);
Vec3f CalRadius_By3Points_No_sqrt(cv::Point p1, cv::Point p2, cv::Point p3);
Vec3f CalRadius_By3Points(cv::Point p1, cv::Point p2, cv::Point p3);
void GetRandNUM_NOT_Equal(int Res[], int Num, int RangeMax, int RangeMin = 0);
inline uchar GetPixel(Mat Src, int x, int y);
inline void SetPixel(Mat Src, int x, int y, uchar Value);
void SetPixel_RGB(Mat Src, int x, int y, cv::Scalar Value);
inline float QuickSqrt(float x);

int CupProcess(Mat BackGround, Mat EmptyCup)
{
    Mat Gray_BackGround;
    Mat Gray_EmptyCup;
	
	std::cout<<"Enter CupProcess()"<<std::endl;
    cvtColor(BackGround, Gray_BackGround, CV_BGR2GRAY);
	cvtColor(EmptyCup, Gray_EmptyCup, CV_BGR2GRAY);
	std::cout<<"cvtColor over. CupProcess()"<<std::endl;
	
	Mat Gray_Cup = Gray_EmptyCup - Gray_BackGround;
	std::cout<<"Gray_EmptyCup - Gray_BackGround over. CupProcess()"<<std::endl;

	Mat Bin_Cup(Gray_Cup);
	threshold(Gray_Cup, Bin_Cup, 40, 255, CV_THRESH_BINARY);
	std::cout<<"threshold over. CupProcess()"<<std::endl;
	imshow("CupProcess-threshold", Bin_Cup);
	medianBlur(Bin_Cup, Bin_Cup, 3);
	std::cout<<"threshold over. CupProcess()"<<std::endl;
	
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(Bin_Cup,Bin_Cup,element);
	dilate(Bin_Cup,Bin_Cup,element);
	erode(Bin_Cup,Bin_Cup,element);
	std::cout<<"erode dilate over. CupProcess()"<<std::endl;

	imshow("CupProcess-erode", Bin_Cup);

    int CenterPointCol = IMAGE_WIDTH / 2;
    int ROI_Width = 640;
    cv::Rect rect(CenterPointCol - ROI_Width / 2, 0, ROI_Width, IMAGE_HIGH);

    Mat ROI_Bin_Cup = Bin_Cup(rect);

    /// 寻找连通域，忽略连通域内部的连通域。
    std::vector<std::vector<cv::Point>> Contours_Cup;
    std::vector<cv::Vec4i> hierarchy_Cup;
	findContours(ROI_Bin_Cup, Contours_Cup, hierarchy_Cup, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	std::cout<<"findContours over. CupProcess() ||||Contours:" << Contours_Cup.size() <<std::endl;

	Mat FinalEdge(480,640, CV_8U, Scalar(0));

    int MaxY = 65535;
    //目的：寻找杯子的下沿。
    //计算连通域边界 与 边界下方一个像素 的差值。
    for (unsigned int i = 0; i < Contours_Cup.size(); i++)
    {
        int _count = Contours_Cup[i].size();
        if (_count < Limit_ContourNUM)
            continue;
		int SumX=0;
		int SumY=0;
		for (int j = 0; j < _count; j++)
		{
			SumX+=Contours_Cup[i][j].x;
			SumY+=Contours_Cup[i][j].y;
		}
		int CenterX = SumX/_count;
		int CenterY = SumY/_count;//camera的视点变了,杯子位置也变了,
		int DistanceFromCenter = (IMAGE_HIGH/2-60-CenterY)*(IMAGE_HIGH/2-60-CenterY)+(IMAGE_WIDTH/2-CenterX)*(IMAGE_WIDTH/2-CenterX);
		if(DistanceFromCenter>Limit_Distance*Limit_Distance)
			continue;

        for (int j = 0; j < _count; j++)
        {
            int Up = GetPixel(ROI_Bin_Cup, Contours_Cup[i][j].x, Contours_Cup[i][j].y);
            int Down = GetPixel(ROI_Bin_Cup, Contours_Cup[i][j].x, Contours_Cup[i][j].y + 1);
            if (Up - Down > 0)
            {
                if (MaxY > Contours_Cup[i][j].y)
                    MaxY = Contours_Cup[i][j].y;
                SetPixel(FinalEdge, Contours_Cup[i][j].x, Contours_Cup[i][j].y, 255);
            }
        }
    }

	imshow("CupProcess-LastEdge", FinalEdge);
    //imwrite("D:\\Cup_Bin.png", Bin_Cup);
    //imwrite("D:\\Cup_Edge.png",FinalEdge);
    return MaxY;
}

int LiquidLevelCupProcess(Mat RealTimeLiquidLevel, Mat EmptyCup)
{
    Mat Gray_RealTimeLiquidLevel;
    Mat Gray_EmptyCup;

    cvtColor(RealTimeLiquidLevel, Gray_RealTimeLiquidLevel, CV_BGR2GRAY);
	cvtColor(EmptyCup, Gray_EmptyCup, CV_BGR2GRAY);

	Mat Gray_LiquidLevel = Gray_EmptyCup - Gray_RealTimeLiquidLevel;

	Mat Bin_LiquidLevel(Gray_LiquidLevel);

	threshold(Gray_LiquidLevel, Bin_LiquidLevel, 65, 255, CV_THRESH_BINARY);

    medianBlur(Bin_LiquidLevel, Bin_LiquidLevel, 3);
    medianBlur(Bin_LiquidLevel, Bin_LiquidLevel, 3);
	medianBlur(Bin_LiquidLevel, Bin_LiquidLevel, 3);

	/*=============切断液面圆跟原始瓶子之间的链接============*/
	//卧槽...切断操作的圆本身会干扰液面识别....
	circle(Bin_LiquidLevel, Point(IMAGE_WIDTH / 1, IMAGE_HIGH * 0), Limit_Distance*3.5, Scalar(0),3);
	/*=======================================================*/

    int CenterPointCol = IMAGE_WIDTH / 2;
    int ROI_Width = 640;
    cv::Rect rect(CenterPointCol - ROI_Width / 2, 0, ROI_Width, IMAGE_HIGH);

    Mat ROI_Bin_LiquidLevel = Bin_LiquidLevel(rect);

    std::vector<std::vector<cv::Point>> Contours_LiquidLevel;
    std::vector<cv::Vec4i> hierarchy_LiquidLevel;
    findContours(ROI_Bin_LiquidLevel, Contours_LiquidLevel, hierarchy_LiquidLevel, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	std::cout<<"findContours."<<std::endl;
	//imshow("ROI_Bin_LiquidLevel", ROI_Bin_LiquidLevel);

    Mat FinalEdge(480, 640, CV_8U, Scalar(0));

    int MaxY = 65535;
    std::vector<cv::Point> LiquidEdge;
    //目的：寻找液面的上沿。
    //计算连通域边界 与 边界上方一个像素 的差值。
    for (unsigned int i = 0; i < Contours_LiquidLevel.size(); i++)
    {
        int _count = Contours_LiquidLevel[i].size();
        if (_count < Limit_ContourNUM)
            continue;

        int SumX = 0;
        int SumY = 0;
        for (int j = 0; j < _count; j++)
        {
            SumX += Contours_LiquidLevel[i][j].x;
            SumY += Contours_LiquidLevel[i][j].y;
        }
        SumX /=	_count;
        SumY /=	_count;
        //计算欧氏距离（忽略平方运算）
        int Distance = (SumX - IMAGE_WIDTH / 2)*(SumX - IMAGE_WIDTH / 2) + (SumY - IMAGE_HIGH / 2)*(SumY - IMAGE_HIGH / 2);
        if (Distance > Limit_Distance*Limit_Distance)
             continue;

        for (int j = 0; j < _count; j++)
        {
            int Up = GetPixel(ROI_Bin_LiquidLevel, Contours_LiquidLevel[i][j].x, Contours_LiquidLevel[i][j].y);
            int Down = GetPixel(ROI_Bin_LiquidLevel, Contours_LiquidLevel[i][j].x, Contours_LiquidLevel[i][j].y - 1);
            if (Up - Down > 0)
            {
                SetPixel(FinalEdge, Contours_LiquidLevel[i][j].x, Contours_LiquidLevel[i][j].y, 255);
                LiquidEdge.insert(LiquidEdge.end(), cv::Point(Contours_LiquidLevel[i][j].x, Contours_LiquidLevel[i][j].y));
            }
        }
    }

    if (LiquidEdge.size() == 0)
		return -1;
    int CirclePoints[3];
    Vec3f Circle;
    srand((unsigned int)(time(NULL)));
    //srand((unsigned int)(rand()));
	int ReTryCount=200;
	while(ReTryCount--)
    {
        GetRandNUM_NOT_Equal(CirclePoints, 3, LiquidEdge.size());
        Circle = CalRadius_By3Points(LiquidEdge[CirclePoints[0]],
                                                    LiquidEdge[CirclePoints[1]],
                                                    LiquidEdge[CirclePoints[2]]);

        if (Circle[2] >= 200)
            continue;
        if (Circle[2] == -1)
            continue;
        MaxY = CalERROR_inCircleAndEdge(Circle, LiquidEdge, 4);
        if (MaxY != -1)
            break;
	}
	//imshow("FinalEdge", FinalEdge); //waitKey();
    return MaxY;
}

//计算一个圆与一些点集的匹配程度。误差圆半径正负ErrorLimit个像素。超过误差的点不计入匹配统计中，即忽略超过误差的点。
//返回液面高度。
int CalERROR_inCircleAndEdge(Vec3f Circle, std::vector<cv::Point> PointCollection, int ErrorLimit)
{
    int Error = 0;
    int MaxY = 65535;

    int Radius = (Circle[2]);
    int x = Circle[0];
    int y = Circle[1];
    int Limit = ErrorLimit;

    int LostCount = 0;
    for (unsigned int i = 0; i < PointCollection.size(); i++)
    {
        int tmpx = PointCollection[i].x;
        int tmpy = PointCollection[i].y;
        int tmp = sqrt((tmpx - x)*(tmpx - x) + (tmpy - y)*(tmpy - y)) - Radius;
        //std::cout << "tmp: " << tmp << "\t" << "Diff x: " << PointCollection[i].x - x << "\t" << "Diff y: " << PointCollection[i].y - y << std::endl;
        if (tmp < 0 && -tmp < Limit)
        {
            Error += tmp;
            PointCollection[i].x += 10000;
            PointCollection[i].y += 10000;
            if (MaxY > tmpy)
                MaxY = tmpy;
        }
        else if (tmp >= 0 && tmp < Limit)
        {
            Error += tmp;
            PointCollection[i].x += 10000;
            PointCollection[i].y += 10000;
            if (MaxY > tmpy)
                MaxY = tmpy;
        }
        else
            LostCount++;
    }

    std::cout << "Radius: " << Radius << "\t" << "Res: " << Error << "\t" << "LostCount: " << LostCount << std::endl;
    std::cout << "==================================================================================" << std::endl;
    if ((LostCount / (double)PointCollection.size()) > 0.7)
        return -1;
    else if (Error > PointCollection.size())//平均每个点误差为1像素。
        return -1;

    Mat Res(480,640,CV_8UC3,Scalar(60,60,60));
    for (unsigned int i = 0; i < PointCollection.size(); i++)
    {
        int tmpx = PointCollection[i].x;
        if (tmpx > 10000)
        {
            int tmpy = PointCollection[i].y - 10000;
            tmpx -= 10000;
            SetPixel_RGB(Res, tmpx, tmpy, Scalar(255, 125, 0));
        }
    }
	circle(Res, Point(x, y), Radius, Scalar(0, 0, 255));
	line(Res, Point(0, MaxY), Point(640, MaxY), Scalar(0, 255, 0));
	//line(gRealTimeLiquidLevel, Point(0, MaxY), Point(640, MaxY), Scalar(0, 255, 0));

	//imwrite("D:\\Level_Circle.png", Res);

	//imshow("RREESS",Res);

    return MaxY;
}

//通过三点计算圆心半径，半径的开方运算是不进行的。
Vec3f CalRadius_By3Points_No_sqrt(cv::Point p1, cv::Point p2, cv::Point p3)
{
    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;
    int x3 = p3.x;
    int y3 = p3.y;

    Vec3f Res(0, 0, -1);

    int a = 2 * (x2 - x1);
    int b = 2 * (y2 - y1);
    int c = x2*x2 + y2*y2 - x1*x1 - y1*y1;
    int d = 2 * (x3 - x2);
    int e = 2 * (y3 - y2);
    int f = x3*x3 + y3*y3 - x2*x2 - y2*y2;
    int Determine = (b*d - e*a);

    if (Determine == 0)//三点共线，无法计算。
        return Res;

    Res[0] = (b*f - e*c) / (double)Determine;
    Res[1] = (d*c - a*f) / (double)Determine;
    Res[2] = ((Res[0] - x1) * (Res[0] - x1) + (Res[1] - y1) * (Res[1] - y1));

    return Res;
}
//通过三点计算圆心半径，后续数据处理不方便，故加上开方运算。
Vec3f CalRadius_By3Points(cv::Point p1, cv::Point p2, cv::Point p3)
{
    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;
    int x3 = p3.x;
    int y3 = p3.y;

    Vec3f Res(0,0,-1);

    int a = 2 * (x2 - x1);
    int b = 2 * (y2 - y1);
    int c = x2*x2 + y2*y2 - x1*x1 - y1*y1;
    int d = 2 * (x3 - x2);
    int e = 2 * (y3 - y2);
    int f = x3*x3 + y3*y3 - x2*x2 - y2*y2;
    int Determine = (b*d - e*a);

    if (Determine == 0)//三点共线，无法计算。
        return Res;

    Res[0] = (b*f - e*c) / (double)Determine;
    Res[1] = (d*c - a*f) / (double)Determine;
    Res[2] = sqrt((Res[0] - x1) * (Res[0] - x1) + (Res[1] - y1) * (Res[1] - y1));

    return Res;
}

inline int GetRandNUM(int RangeMax, int RangeMin)
{
    //srand((unsigned int)(time(NULL)));
    return ((rand() * rand()) % (RangeMax - RangeMin)) + RangeMin;
}

std::default_random_engine random_generator(time(NULL));
//获得互不相等的随机数
void GetRandNUM_NOT_Equal(int Res[], int Num, int RangeMax, int RangeMin)
{
    if (Num > RangeMax - RangeMin)
        return;

    std::uniform_int_distribution<int> dis1(RangeMin, RangeMax-1);
    for (int i = 0; i < Num; i++)
    {
        bool isDuplicate = true;
        while (isDuplicate)
        {
            Res[i] = dis1(random_generator);
            isDuplicate = false;
            for (int j = i - 1; j >= 0; j--)
                if (Res[i] == Res[j])
                    isDuplicate = true;
        }
    }
}

inline uchar GetPixel(Mat Src, int x, int y)
{
    uchar *Data = Src.ptr<uchar>(y);
    return Data[x];
}

inline void SetPixel(Mat Src, int x, int y, uchar Value)
{
    uchar *Data = Src.ptr<uchar>(y);
    Data[x] = Value;
}
//Mat里的顺序是BGR，所以更改顺序，Scalar(R,G,B)。
inline void SetPixel_RGB(Mat Src, int x, int y, cv::Scalar Value)
{
    uchar *Data = Src.ptr<uchar>(y);
    Data[x * 3] = Value[2];
    Data[x * 3 + 1] = Value[1];
    Data[x * 3 + 2] = Value[0];
}
