/*
 * TLVector.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: dustin
 */

#include "TLVector.hpp"

#include "StreamingUtils.hpp"
#include "TLContext.hpp"

namespace telegram {
namespace tl {

int TLVector::size() const {
	return mItems.size();
}

bool TLVector::empty() const {
	return mItems.empty();
}

bool TLVector::contains(const QVariant& var) const {
	return mItems.contains(var);
}

void TLVector::append(const QVariant& var) {
	mItems.append(var);
}

void TLVector::removeAt(int i) {
	mItems.removeAt(i);
}

void TLVector::clear() {
	mItems.clear();
}

const QVariant& TLVector::at(int i) const {
	return mItems.at(i);
}

int TLVector::indexOf(const QVariant& var, int from) const {
	return mItems.indexOf(var, from);
}

QVariant& TLVector::operator[](int i) {
	return mItems[i];
}

void TLVector::serializeBody(QDataStream& stream) {
	StreamingUtils::writeInt(mItems.length(), stream);
	if (mDestinationClass == QMetaType::Int) {
		foreach (QVariant v,mItems)
		{
			StreamingUtils::writeInt(v.toInt(), stream);
		}
	} else if (mDestinationClass == QMetaType::type("qlonglong")) {
		foreach (QVariant v,mItems)
		{
			StreamingUtils::writeLong(v.toLongLong(), stream);
		}
	} else if (mDestinationClass == QMetaType::QString) {
		foreach (QVariant v,mItems)
		{
			StreamingUtils::writeTLString(v.toString(), stream);
		}
	} else {
		foreach (QVariant v,mItems)
		{
			StreamingUtils::writeTLObject(v.value<TLObject*>(), stream);
		}
	}
}

void TLVector::deserializeBody(QDataStream& stream, TLContext* context) {
	int count = StreamingUtils::readInt(stream);
	for (int i = 0; i < count; ++i) {
		if (mDestinationClass == QMetaType::Int) {
			mItems.append(StreamingUtils::readInt(stream));
		} else if (mDestinationClass == QMetaType::type("qlonglong")) {
			mItems.append(StreamingUtils::readLong(stream));
		} else if (mDestinationClass == QMetaType::QString) {
			mItems.append(StreamingUtils::readTLString(stream));
		} else {
			mItems.append(
					QVariant::fromValue(context->deserializeMessage(stream)));
		}
	}
}

} /* namespace tl */
} /* namespace telegram */
