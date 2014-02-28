/*
 * TLLongVector.hpp
 *
 *  Created on: Feb 10, 2014
 *      Author: dustin
 */

#ifndef TLLONGVECTOR_HPP_
#define TLLONGVECTOR_HPP_

#include "TLVector.hpp"

namespace telegram {
namespace tl {

class TLLongVector: public TLVector {
Q_OBJECT

public:
	TLLongVector(QObject* parent = 0) :
			TLVector(parent) {
		setDestinationClass(QMetaType::type("qlonglong"));
	}
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLLONGVECTOR_HPP_ */
