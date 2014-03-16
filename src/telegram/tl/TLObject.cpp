/*
 * TLObject.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: dustin
 */

#include "TLObject.hpp"

#include "TLContext.hpp"
#include <QDataStream>
#include "StreamingUtils.hpp"
#include <QDebug>

namespace telegram {
namespace tl {

QByteArray TLObject::serialize() const {
	QByteArray bytes;
	QDataStream stream(&bytes, QIODevice::WriteOnly);
	stream.setByteOrder(QDataStream::LittleEndian);
	serialize(stream);
	return bytes;
}

void TLObject::serialize(QDataStream& stream) const {
	StreamingUtils::writeInt(classId(), stream);
	serializeBody(stream);
}

void TLObject::deserialize(QDataStream& stream, TLContext* context) {
	int cid = StreamingUtils::readInt(stream);
	if (cid != classId()) {
		QString error = "Wrong class id. Found: " + QString::number(cid, 16)
				+ ", expected " + QString::number(classId(), 16);
		qDebug() << "Error:" << error << endl;
		throw error;
	}
	deserializeBody(stream, context);
}

void TLObject::serializeBody(QDataStream& stream) const {
	Q_UNUSED(stream)
}

void TLObject::deserializeBody(QDataStream& stream, TLContext* context) {
	Q_UNUSED(stream)
	Q_UNUSED(context)
}

}
/* namespace tl */
} /* namespace telegram */
