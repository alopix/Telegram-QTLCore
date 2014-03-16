/*
 * TLVector.hpp
 *
 *  Created on: Feb 8, 2014
 *      Author: dustin
 */

#ifndef TLVECTOR_HPP_
#define TLVECTOR_HPP_

#include "TLObject.hpp"

namespace telegram {
namespace tl {

class TLVector: public TLObject {
Q_OBJECT

Q_PROPERTY(int destinationClass READ destinationClass WRITE setDestinationClass)

public:
	static const int CLASS_ID = 0x1cb5c415;

	// User stands for TLObject in our case!
	// TODO: make our own Q_DECLARE_METATYPE and get the id using QMetaType::type("")!!!
	TLVector(QObject* parent = 0) :
			TLObject(parent) {
		mDestinationClass = QMetaType::type("telegram::tl::TLObject*");
	}

	virtual ~TLVector() {
	}

	virtual int classId() const {
		return CLASS_ID;
	}

	int destinationClass() const {
		return mDestinationClass;
	}

	void setDestinationClass(int newValue) {
		// TODO: also add all TLObject children
		if (newValue != QMetaType::Int
				&& newValue != QMetaType::type("qlonglong")
				&& newValue != QMetaType::QString
				&& newValue != QMetaType::type("telegram::tl::TLObject*")) {
			QString error = "Unsupported destination class";
			throw error;
		}
		mDestinationClass = newValue;
	}

	// List implementation
	int size() const;
	bool empty() const;
	bool contains(const QVariant& var) const;
	void append(const QVariant& var);
	void removeAt(int i);
	void clear();
	const QVariant& at(int i) const;
	int indexOf(const QVariant& var, int from = 0) const;
	QVariant& operator[](int i);

	// TLObject
	virtual void serializeBody(QDataStream& stream) const;
	virtual void deserializeBody(QDataStream& stream, TLContext* context);

private:
	QVariantList mItems;
	int mDestinationClass;
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLVECTOR_HPP_ */
