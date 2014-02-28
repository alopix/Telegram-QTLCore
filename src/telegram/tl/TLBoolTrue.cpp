/*
 * TLBoolTrue.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: dustin
 */

#include "TLBoolTrue.hpp"

namespace telegram {
namespace tl {

TLBoolTrue::TLBoolTrue(QObject* parent) :
		TLBool(parent) {
}

TLBoolTrue::~TLBoolTrue() {
}

int TLBoolTrue::classId() const {
	return CLASS_ID;
}

} /* namespace tl */
} /* namespace telegram */
