/*
 * StreamingUtils.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: dustin
 */

#include "StreamingUtils.hpp"

#include "TLObject.hpp"
#include "TLMethod.hpp"
#include "TLVector.hpp"
#include "TLIntVector.hpp"
#include "TLLongVector.hpp"
#include "TLStringVector.hpp"
#include "TLContext.hpp"
#include "TLBoolTrue.hpp"
#include "TLBoolFalse.hpp"
#include <QtEndian>
#include <QDebug>

namespace telegram {
namespace tl {

void StreamingUtils::writeByte(char v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeByte" << endl;
	stream.writeRawData(&v, 1);
}

void StreamingUtils::writeInt(int v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeInt" << endl;
	QDataStream::ByteOrder oldOrder = stream.byteOrder();
	stream.setByteOrder(QDataStream::LittleEndian);
	stream << v;
	stream.setByteOrder(oldOrder);

	// "Old" implementation:
	//writeByte((v & 0xFF), stream);
	//writeByte(((v >> 8) & 0xFF), stream);
	//writeByte(((v >> 16) & 0xFF), stream);
	//writeByte(((v >> 24) & 0xFF), stream);
}

void StreamingUtils::writeLong(qlonglong v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeLong" << endl;
	QDataStream::ByteOrder oldOrder = stream.byteOrder();
	stream.setByteOrder(QDataStream::LittleEndian);
	stream << v;
	stream.setByteOrder(oldOrder);

	// "Old" implementation:
	//writeByte((v & 0xFF), stream);
	//writeByte(((v >> 8) & 0xFF), stream);
	//writeByte(((v >> 16) & 0xFF), stream);
	//writeByte(((v >> 24) & 0xFF), stream);
	//
	//writeByte(((v >> 32) & 0xFF), stream);
	//writeByte(((v >> 40) & 0xFF), stream);
	//writeByte(((v >> 48) & 0xFF), stream);
	//writeByte(((v >> 56) & 0xFF), stream);
}

void StreamingUtils::writeDouble(double v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeDouble" << endl;
	qlonglong l = reinterpret_cast<qlonglong&>(v);
	writeLong(l, stream);
}

void StreamingUtils::writeByteArray(const char* v, int size,
		QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeByteArray" << endl;
	stream.writeRawData(v, size);
}

void StreamingUtils::writeByteArray(QByteArray& v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeByteArray" << endl;
	stream.writeRawData(v.constData(), v.size());
}

void StreamingUtils::writeTLBool(bool v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeTLBool" << endl;
	if (v) {
		writeInt(TLBoolTrue::CLASS_ID, stream);
	} else {
		writeInt(TLBoolFalse::CLASS_ID, stream);
	}
}

void StreamingUtils::writeTLString(QString v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeTLString" << endl;
	QByteArray utf = v.toUtf8();
	writeTLBytes(utf, stream);
}

void StreamingUtils::writeTLBytes(QByteArray& v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeTLBytes" << endl;
	int startOffset = 1;
	if (v.size() >= 254) {
		startOffset = 4;
		writeByte(254, stream);
		writeByte(v.size() & 0xFF, stream);
		writeByte((v.size() >> 8) & 0xFF, stream);
		writeByte((v.size() >> 16) & 0xFF, stream);
	} else {
		writeByte(v.size(), stream);
	}

	writeByteArray(v, stream);

	int offset = (v.size() + startOffset) % 4;
	if (offset != 0) {
		int offsetCount = 4 - offset;
		for (int i = 0; i < offsetCount; ++i) {
			writeByte(0, stream);
		}
	}
}

void StreamingUtils::writeTLObject(TLObject* v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeTLObject" << endl;
	v->serialize(stream);
}

void StreamingUtils::writeTLMethod(TLMethod* v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeTLMethod" << endl;
	writeTLObject(v, stream);
}

void StreamingUtils::writeTLVector(TLVector* v, QDataStream& stream) {
	//qDebug() << "StreamingUtils::writeTLVector" << endl;
	writeTLObject(v, stream);
}

int StreamingUtils::readInt(QDataStream& stream) {
	//qDebug() << "StreamingUtils::readInt" << endl;
	QDataStream::ByteOrder order = stream.byteOrder();
	stream.setByteOrder(QDataStream::LittleEndian);
	int v;
	stream >> v;
	stream.setByteOrder(order);
	return v;
}

qlonglong StreamingUtils::readLong(QDataStream& stream) {
	//qDebug() << "StreamingUtils::readLong" << endl;
	QDataStream::ByteOrder order = stream.byteOrder();
	stream.setByteOrder(QDataStream::LittleEndian);
	qlonglong v;
	stream >> v;
	stream.setByteOrder(order);
	return v;
}

double StreamingUtils::readDouble(QDataStream& stream) {
	//qDebug() << "StreamingUtils::readDouble" << endl;
	QDataStream::ByteOrder order = stream.byteOrder();
	stream.setByteOrder(QDataStream::LittleEndian);
	double v;
	stream >> v;
	stream.setByteOrder(order);
	return v;
}

QString StreamingUtils::readTLString(QDataStream& stream) {
	//qDebug() << "StreamingUtils::readTLString" << endl;
	return QString(readTLBytes(stream));
}

TLObject* StreamingUtils::readTLObject(QDataStream& stream,
		TLContext* context) {
	//qDebug() << "StreamingUtils::readTLObject" << endl;
	return context->deserializeMessage(stream);
}

TLMethod* StreamingUtils::readTLMethod(QDataStream& stream,
		TLContext* context) {
	//qDebug() << "StreamingUtils::readTLMethod" << endl;
	return qobject_cast<TLMethod*>(context->deserializeMessage(stream));
}

QByteArray StreamingUtils::readBytes(int count, QDataStream& stream) {
	//qDebug() << "StreamingUtils::readBytes" << endl;
	QByteArray res;
	char* temp = new char[count];
	int read = 0;
	while (read < count) {
		read += stream.readRawData(temp, count);
		res.append(temp, read);
	}
	delete[] temp;

	return res;
}

QByteArray StreamingUtils::readTLBytes(QDataStream& stream) {
	//qDebug() << "StreamingUtils::readTLBytes" << endl;
	int count = readByte(stream);
	int startOffset = 1;
	if (count >= 254) {
		count = readByte(stream) + (readByte(stream) << 8)
				+ (readByte(stream) << 16);
		startOffset = 4;
	}

	QByteArray raw = readBytes(count, stream);
	int offset = (count + startOffset) % 4;
	if (offset != 0) {
		int offsetCount = 4 - offset;
		stream.skipRawData(offsetCount);
	}

	return raw;
}

TLVector* StreamingUtils::readTLVector(QDataStream& stream,
		TLContext* context) {
	//qDebug() << "StreamingUtils::readTLVector" << endl;
	return context->deserializeVector(stream);
}

TLIntVector* StreamingUtils::readTLIntVector(QDataStream& stream,
		TLContext* context) {
	//qDebug() << "StreamingUtils::readTLIntVector" << endl;
	return context->deserializeIntVector(stream);
}

TLLongVector* StreamingUtils::readTLLongVector(QDataStream& stream,
		TLContext* context) {
	//qDebug() << "StreamingUtils::readTLLongVector" << endl;
	return context->deserializeLongVector(stream);
}

TLStringVector* StreamingUtils::readTLStringVector(QDataStream& stream,
		TLContext* context) {
	//qDebug() << "StreamingUtils::readTLStringVector" << endl;
	return context->deserializeStringVector(stream);
}

bool StreamingUtils::readTLBool(QDataStream& stream) {
	//qDebug() << "StreamingUtils::readTLBool" << endl;
	int v = readInt(stream);
	if (v == TLBoolTrue::CLASS_ID) {
		return true;
	} else if (v == TLBoolFalse::CLASS_ID) {
		return false;
	} else {
		QString error = "Not bool value: " + QString::number(v, 16);
		qDebug() << "Error:" << error << endl;
		throw error;
	}
}

int StreamingUtils::readByte(QDataStream& stream) {
	char* bytes = new char[1];
	int read = stream.readRawData(bytes, 1);
	if (read != 1) {
		QString error = "Could not read byte!";
		qDebug() << "Error:" << error << endl;
		throw error;
	}
	unsigned char byte = *bytes;
	delete[] bytes;
	return byte;
}

QByteArray StreamingUtils::bignumLongToByteArray(qlonglong v) {
	QByteArray res;
	QDataStream stream(&res, QIODevice::WriteOnly);
	int i = qToLittleEndian(v);
	stream << i;
	return res;
}

} /* namespace tl */
} /* namespace telegram */
