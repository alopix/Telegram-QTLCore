/*
 * TLBoolFalse.hpp
 *
 *  Created on: Feb 8, 2014
 *      Author: dustin
 */

#ifndef TLBOOLFALSE_HPP_
#define TLBOOLFALSE_HPP_

#include "TLBool.hpp"

namespace telegram {
namespace tl {

class TLBoolFalse: public TLBool {
Q_OBJECT

public:
	static const int CLASS_ID = 0xbc799737;

	TLBoolFalse(QObject* parent = 0) :
			TLBool(parent) {
	}

	virtual ~TLBoolFalse() {
	}

	virtual int classId() const {
		return CLASS_ID;
	}
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLBOOLFALSE_HPP_ */
