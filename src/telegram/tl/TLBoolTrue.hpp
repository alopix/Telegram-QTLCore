/*
 * TLBoolTrue.hpp
 *
 *  Created on: Feb 3, 2014
 *      Author: dustin
 */

#ifndef TLBOOLTRUE_HPP_
#define TLBOOLTRUE_HPP_

#include <QObject>
#include "TLBool.hpp"

namespace telegram {
namespace tl {

class TLBoolTrue: public TLBool {
Q_OBJECT

public:
	static const int CLASS_ID = 0x997275b5;

	TLBoolTrue(QObject* parent = 0);

	virtual ~TLBoolTrue();

	virtual int classId() const;
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLBOOLTRUE_HPP_ */
