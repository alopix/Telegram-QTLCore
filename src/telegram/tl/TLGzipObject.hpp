/*
 * TLGzipObject.hpp
 *
 *  Created on: Feb 12, 2014
 *      Author: dustin
 */

#ifndef TLGZIPOBJECT_HPP_
#define TLGZIPOBJECT_HPP_

#include "TLObject.hpp"

namespace telegram {
namespace tl {

class TLGzipObject: public TLObject {
Q_OBJECT

Q_PROPERTY(QByteArray packedData READ packedData WRITE setPackedData)

public:
	static const int CLASS_ID = 0x3072CFA1;

	TLGzipObject(QByteArray packedData, QObject* parent = 0) :
			TLObject(parent), mPackedData(packedData) {
	}
	TLGzipObject(QObject* parent = 0) :
			TLObject(parent) {
	}

	virtual ~TLGzipObject() {
	}

	virtual int classId() const {
		return CLASS_ID;
	}

	QByteArray packedData() const {
		return mPackedData;
	}

	void setPackedData(QByteArray newValue) {
		if (newValue != mPackedData) {
			mPackedData = newValue;
		}
	}

	virtual void serializeBody(QDataStream& stream);
	virtual void deserializeBody(QDataStream& stream, TLContext* context);

private:
	QByteArray mPackedData;
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLGZIPOBJECT_HPP_ */
