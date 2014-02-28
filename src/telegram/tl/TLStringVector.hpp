/*
 * TLStringVector.hpp
 *
 *  Created on: Feb 10, 2014
 *      Author: dustin
 */

#ifndef TLSTRINGVECTOR_HPP_
#define TLSTRINGVECTOR_HPP_

#include "TLVector.hpp"

namespace telegram {
namespace tl {

class TLStringVector: public TLVector {
Q_OBJECT

public:
	TLStringVector(QObject* parent = 0) :
			TLVector(parent) {
		setDestinationClass(QMetaType::QString);
	}
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLSTRINGVECTOR_HPP_ */
