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
		Base::Component(name)  {

}

Rectangles::~Rectangles() {
}

void Rectangles::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	registerHandler("FindRectangle", boost::bind(&Rectangles::FindRectangle, this));
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

void Rectangles::FindRectangle() {
}



} //: namespace Rectangles
} //: namespace Processors
