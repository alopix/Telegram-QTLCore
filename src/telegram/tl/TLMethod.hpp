/*
 * TLMethod.hpp
 *
 *  Created on: Feb 8, 2014
 *      Author: dustin
 */

#ifndef TLMETHOD_HPP_
#define TLMETHOD_HPP_

#include "TLObject.hpp"

namespace telegram {
namespace tl {
class TLContext;
}
}

namespace telegram {
namespace tl {

class TLMethod: public TLObject {
Q_OBJECT

public:
	TLMethod(QObject* parent = 0) :
			TLObject(parent) {
	}

	virtual ~TLMethod() {
	}

	virtual TLObject* deserializeResponse(QDataStream& stream,
			TLContext* context) = 0;
};

} /* namespace tl */
} /* namespace telegram */
//Q_DECLARE_METATYPE(telegram::tl::TLMethod*)

#endif /* TLMETHOD_HPP_ */
