/*
 * TLIntVector.hpp
 *
 *  Created on: Feb 10, 2014
 *      Author: dustin
 */

#ifndef TLINTVECTOR_HPP_
#define TLINTVECTOR_HPP_

#include "TLVector.hpp"

namespace telegram {
namespace tl {

class TLIntVector: public TLVector {
Q_OBJECT

public:
	TLIntVector(QObject* parent = 0) :
			TLVector(parent) {
		setDestinationClass(QMetaType::Int);
	}
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLINTVECTOR_HPP_ */
