/*!
 * \file
 * \brief
 * \author Lukasz Korpal
 */

#include <memory>
#include <string>

#include "Rectangles.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Rectangles {

Rectangles::Rectangles(const std::string & name) :
		Base::Component(name),
		BrickColour("Colour", -1)  {
	registerProperty(BrickColour);
}

Rectangles::~Rectangles() {
}

void Rectangles::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_contours", &in_contours);
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	registerStream("out_contours", &out_contours);
	registerStream("out_data", &out_data);
	// Register handlers
	registerHandler("FindRectangle", boost::bind(&Rectangles::FindRectangle, this));
	addDependency("FindRectangle", &in_contours);
	addDependency("FindRectangle", &in_img);

}

bool Rectangles::onInit() {

	return true;
}

bool Rectangles::onFinish() {
	return true;
}

bool Rectangles::onStop() {
	return true;
}

bool Rectangles::onStart() {
	return true;
}

static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;
	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	cv::Rect r = cv::boundingRect(contour);
	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}

void Rectangles::FindRectangle() {
	
	vector<vector<Point> > contours = in_contours.read();
	vector<vector<Point> > outcontours;
	vector<float> outdata;
	cv::Mat src = in_img.read();
	cv::Mat dst = src.clone();
	std::vector<cv::Point> approx;
	int counter = 0;
	
	for (int i = 0; i < contours.size(); i++)
	{
		// Approximate contour with accuracy proportional
		// to the contour perimeter
		cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
		// Skip small or non-convex objects
		if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
			continue;
		if (approx.size() >= 4 && approx.size() <= 6)
		{
			// Number of vertices of polygonal curve
			int vtc = approx.size();
			// Get the cosines of all corners
			std::vector<double> cos;
			for (int j = 2; j < vtc+1; j++)
			cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));
			// Sort ascending the cosine values
			std::sort(cos.begin(), cos.end());
			// Get the lowest and the highest cosine
			double mincos = cos.front();
			double maxcos = cos.back();
			// Use the degrees obtained above and the number of vertices
			// to determine the shape of the contour
			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
			{
				setLabel(dst, "RECT", contours[i]);
				outcontours.push_back(approx);
				CLOG(LNOTICE) << "Rectangle found!" << approx;
				outdata.push_back(float(BrickColour));
				circle(dst, approx[0], 5, cv::Scalar(255,255,0));
				//setLabel(dst, "0", approx[0]);
				CLOG(LNOTICE) << "Rectangle 0x found! " << float(approx[0].x);
				outdata.push_back(float(approx[0].x));
				//setLabel(dst, "1", approx[1]);
				circle(dst, approx[1], 5, cv::Scalar(255,255,0));
				circle(dst, approx[1], 6, cv::Scalar(255,255,0));
				outdata.push_back(float(approx[1].x));
				//setLabel(dst, "2", approx[2]);
				circle(dst, approx[2], 5, cv::Scalar(255,255,0));
				circle(dst, approx[2], 6, cv::Scalar(255,255,0));
				circle(dst, approx[2], 7, cv::Scalar(255,255,0));
				outdata.push_back(float(approx[2].x));
				//setLabel(dst, "RECT", contours[i]);
				circle(dst, approx[3], 5, cv::Scalar(255,255,0));
				circle(dst, approx[3], 7, cv::Scalar(255,255,0));
				circle(dst, approx[3], 9, cv::Scalar(255,255,0));
				outdata.push_back(float(approx[3].x));
				//setLabel(dst, "3", approx[3]);
				
				outdata.push_back(float(approx[0].y));
				outdata.push_back(float(approx[1].y));
				outdata.push_back(float(approx[2].y));
				outdata.push_back(float(approx[3].y));
				++counter;
			}
		}
	}


	out_img.write(dst);
	out_contours.write(outcontours);
	out_data.write(outdata);
}



} //: namespace Rectangles
} //: namespace Processors
