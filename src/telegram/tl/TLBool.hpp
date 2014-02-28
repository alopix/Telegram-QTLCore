/*
 * TLBool.hpp
 *
 *  Created on: Feb 3, 2014
 *      Author: dustin
 */

#ifndef TLBOOL_HPP_
#define TLBOOL_HPP_

#include "TLObject.hpp"

namespace telegram {
namespace tl {

class TLBool: public TLObject {
	Q_OBJECT

public:
	TLBool(QObject* parent = 0) :
			TLObject(parent) {
	}

	virtual ~TLBool() {
	}
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLBOOL_HPP_ */
