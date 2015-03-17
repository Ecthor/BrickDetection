/*!
 * \file
 * \brief
 * \author Lukasz Korpal
 */

#include <memory>
#include <string>

#include "HistogramEq.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace HistogramEq {

HistogramEq::HistogramEq(const std::string & name) :
		Base::Component(name)  {

}

HistogramEq::~HistogramEq() {
}

void HistogramEq::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	registerHandler("EqualizeHistogram", boost::bind(&HistogramEq::EqualizeHistogram, this));
	addDependency("EqualizeHistogram", &in_img);

}

bool HistogramEq::onInit() {

	return true;
}

bool HistogramEq::onFinish() {
	return true;
}

bool HistogramEq::onStop() {
	return true;
}

bool HistogramEq::onStart() {
	return true;
}

void HistogramEq::EqualizeHistogram() {
	cv::Mat src = in_img.read();
	cv::Mat dst;
	dst=src.clone();
	cv::equalizeHist( src, dst );
	out_img.write(dst);
}



} //: namespace HistogramEq
} //: namespace Processors
