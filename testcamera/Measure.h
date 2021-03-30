#pragma once
#include <opencv2\core\core.hpp>
#include <vector>
double K[9] = { 3.110669260077860e+03,0,1.495744378401180e+03, 0,3.107207366112760e+03,2.018311619019980e+03, 0,0,1 };
class CMeasure
{
protected:
	//camera parameter array
	
	//camera inner matrix
	cv::Mat inner = cv::Mat(3, 3, CV_32FC1, K);
	//camera height
	float height = 1.45;
public: 
	//
	//
	//
	//
	template<class T> bool SolveXYZGround(std::vector<T>& src,
		std::vector<cv::Point3f>& dst)
	{
		src = { (400,400) };
		if (src.size()==0)
		{
			return false;
		}
		dst.resize(src.size());
		if (inner.type() == CV_32F)
		{
			for (size_t i = 0; i < dst.size(); i++)
			{
				dst[i].z = height / (src[i].y - inner.at<float>(1, 2)) * inner.at <float>(1, 1);
				dst[i].x = dst[i].z*(src[i].x - inner.at<float>(0, 2))/ inner.at <float>(0, 0);
				dst[i].y = -height;
			}
		}
		if (inner.type() == CV_64F)
		{
			for (size_t i = 0; i < dst.size(); i++)
			{
				dst[i].z = height / (src[i].y - inner.at<double>(1, 2)) * inner.at <double>(1, 1);
				dst[i].x = dst[i].z*(src[i].x - inner.at<double>(0, 2)) / inner.at <double>(0, 0);
				dst[i].y = -height;
			}
		}
		return true;
	}
	//
	bool SetInner(cv::Mat& src)
	{
		if (src.size().height != 3 || src.size().width != 3)
		{
			return false;
		}
		if (src.type()==CV_32F
			|| src.type() == CV_64F)
		{
			src.copyTo(inner);
			return true;
		}
		return false;
	}
	//
	cv::Mat GetInner(){ return inner; }
	void setHeight(float theight){ height = theight; }
	float getHeight(){ return height; }
	CMeasure();
	~CMeasure();
};

