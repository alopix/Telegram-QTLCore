/*
 * TLContext.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: dustin
 */

#include "TLContext.hpp"

#include <QMetaObject>
#include <QMetaClassInfo>
#include "TLObject.hpp"
#include "TLBoolTrue.hpp"
#include "TLBoolFalse.hpp"
#include "TLVector.hpp"
#include "TLIntVector.hpp"
#include "TLLongVector.hpp"
#include "TLStringVector.hpp"
#include "StreamingUtils.hpp"
#include "TLGzipObject.hpp"
#include "zlib.h"
#include <QDebug>

namespace telegram {
namespace tl {

TLContext::TLContext(QObject* parent) :
		QObject(parent) {
}

TLContext::~TLContext() {
}

bool TLContext::isSupportedObject(TLObject& object) {
	return isSupportedObject(object.classId());
}

bool TLContext::isSupportedObject(int classId) {
	return mRegisteredClasses.contains(classId);
}

void TLContext::registerClass(int classId, const QMetaObject& metaObject) {
	mRegisteredClasses.insert(classId, &metaObject);
}

void TLContext::registerCompatClass(int classId,
		const QMetaObject& metaObject) {
	mRegisteredCompatClasses.insert(classId, &metaObject);
}

TLObject* TLContext::convertCompatClass(TLObject* src) {
	return src;
}

TLObject* TLContext::deserializeMessage(QByteArray& data) {
	QDataStream stream(data);
	return deserializeMessage(stream);
}

TLObject* TLContext::deserializeMessage(int classId, QDataStream& stream) {
	qDebug() << "TLContext::deserializeMessage" << QString::number(classId, 16)
			<< endl;
	if (classId == TLGzipObject::CLASS_ID) {
		TLGzipObject* obj = new TLGzipObject();
		obj->deserializeBody(stream, this);
		QByteArray gzipData = TLContext::gUncompress(obj->packedData());
		QDataStream gzipStream(gzipData);
		int innerClassId = StreamingUtils::readInt(gzipStream);
		TLObject* result = deserializeMessage(innerClassId, gzipStream);
		delete obj;
		return result;
	}

	if (classId == TLBoolTrue::CLASS_ID) {
		return new TLBoolTrue();
	}

	if (classId == TLBoolFalse::CLASS_ID) {
		return new TLBoolFalse();
	}

	if (mRegisteredCompatClasses.contains(classId)) {
		const QMetaObject* metaObject = mRegisteredCompatClasses.value(classId);
		TLObject* message = qobject_cast<TLObject*>(metaObject->newInstance());
		message->deserializeBody(stream, this);
		return message;
	}

	if (!mRegisteredClasses.contains(classId)) {
		QString error = "Unsupported class: #" + QString::number(classId, 16);
		qDebug() << "Error:" << error << endl;
		throw error;
	}
	const QMetaObject* metaObject = mRegisteredClasses.value(classId);
	TLObject* message = qobject_cast<TLObject*>(metaObject->newInstance());
	message->deserializeBody(stream, this);
	return message;
}

TLObject* TLContext::deserializeMessage(QDataStream& stream) {
	int classId = StreamingUtils::readInt(stream);
	return deserializeMessage(classId, stream);
}

TLVector* TLContext::deserializeVector(QDataStream& stream) {
	int classId = StreamingUtils::readInt(stream);
	if (classId == TLVector::CLASS_ID) {
		TLVector* res = new TLVector();
		res->deserializeBody(stream, this);
		return res;
	} else if (classId == TLGzipObject::CLASS_ID) {
		TLGzipObject* obj = new TLGzipObject();
		obj->deserializeBody(stream, this);
		QByteArray gzipData = TLContext::gUncompress(obj->packedData());
		QDataStream gzipStream(gzipData);
		TLVector* res = deserializeVector(gzipStream);
		delete obj;
		return res;
	} else {
		QString error = "Unable to deserialize vector";
		qDebug() << "Error:" << error << endl;
		throw error;
	}
}

TLIntVector* TLContext::deserializeIntVector(QDataStream& stream) {
	int classId = StreamingUtils::readInt(stream);
	if (classId == TLVector::CLASS_ID) {
		TLIntVector* res = new TLIntVector();
		res->deserializeBody(stream, this);
		return res;
	} else if (classId == TLGzipObject::CLASS_ID) {
		TLGzipObject* obj = new TLGzipObject();
		obj->deserializeBody(stream, this);
		QByteArray gzipData = TLContext::gUncompress(obj->packedData());
		QDataStream gzipStream(gzipData);
		TLIntVector* res = deserializeIntVector(gzipStream);
		delete obj;
		return res;
	} else {
		QString error = "Unable to deserialize vector";
		qDebug() << "Error:" << error << endl;
		throw error;
	}
}

TLLongVector* TLContext::deserializeLongVector(QDataStream& stream) {
	int classId = StreamingUtils::readInt(stream);
	if (classId == TLVector::CLASS_ID) {
		TLLongVector* res = new TLLongVector();
		res->deserializeBody(stream, this);
		return res;
	} else if (classId == TLGzipObject::CLASS_ID) {
		TLGzipObject* obj = new TLGzipObject();
		obj->deserializeBody(stream, this);
		QByteArray gzipData = TLContext::gUncompress(obj->packedData());
		QDataStream gzipStream(gzipData);
		TLLongVector* res = deserializeLongVector(gzipStream);
		delete obj;
		return res;
	} else {
		QString error = "Unable to deserialize vector";
		qDebug() << "Error:" << error << endl;
		throw error;
	}
}

TLStringVector* TLContext::deserializeStringVector(QDataStream& stream) {
	int classId = StreamingUtils::readInt(stream);
	if (classId == TLVector::CLASS_ID) {
		TLStringVector* res = new TLStringVector();
		res->deserializeBody(stream, this);
		return res;
	} else if (classId == TLGzipObject::CLASS_ID) {
		TLGzipObject* obj = new TLGzipObject();
		obj->deserializeBody(stream, this);
		QByteArray gzipData = TLContext::gUncompress(obj->packedData());
		QDataStream gzipStream(gzipData);
		TLStringVector* res = deserializeStringVector(gzipStream);
		delete obj;
		return res;
	} else {
		QString error = "Unable to deserialize vector";
		qDebug() << "Error:" << error << endl;
		throw error;
	}
}

QByteArray TLContext::gUncompress(const QByteArray& data) {
	qDebug() << "Reached Guncompress" << "size=" << data.size() << endl;
	if (data.size() <= 4) {
		qWarning("gUncompress: Input data is truncated");
		return QByteArray();
	}

	QByteArray result;

	int ret;
	z_stream strm;
	static const int CHUNK_SIZE = 1024;
	char out[CHUNK_SIZE];

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = data.size();
	strm.next_in = (Bytef*) (data.data());

	ret = inflateInit2(&strm, 15 + 32); // gzip decoding
	if (ret != Z_OK) {
		return QByteArray();
	}

	// run inflate()
	do {
		strm.avail_out = CHUNK_SIZE;
		strm.next_out = (Bytef*) (out);

		ret = inflate(&strm, Z_NO_FLUSH);
		Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

		switch (ret) {
		case Z_NEED_DICT:
			ret = Z_DATA_ERROR;
			// no break

		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
			(void) inflateEnd(&strm);
			return QByteArray();
		}

		result.append(out, CHUNK_SIZE - strm.avail_out);
	} while (strm.avail_out == 0);

	// clean up and return
	inflateEnd(&strm);
	return result;
}

} /* namespace tl */
} /* namespace telegram */
