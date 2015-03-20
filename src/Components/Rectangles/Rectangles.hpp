/*!
 * \file
 * \brief 
 * \author Lukasz Korpal
 */

#ifndef RECTANGLES_HPP_
#define RECTANGLES_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace Rectangles {

/*!
 * \class Rectangles
 * \brief Rectangles processor class.
 *
 * 
 */
class Rectangles: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Rectangles(const std::string & name = "Rectangles");

	/*!
	 * Destructor
	 */
	virtual ~Rectangles();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	// Input data streams
	Base::DataStreamIn<cv::Mat> in_img;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers

	// Properties

	
	// Handlers
	void FindRectangle();

};

} //: namespace Rectangles
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Rectangles", Processors::Rectangles::Rectangles)

#endif /* RECTANGLES_HPP_ */
