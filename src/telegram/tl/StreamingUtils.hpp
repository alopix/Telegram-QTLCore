/*
 * StreamingUtils.hpp
 *
 *  Created on: Feb 2, 2014
 *      Author: dustin
 */

#ifndef STREAMINGUTILS_HPP_
#define STREAMINGUTILS_HPP_

#include <QtCore>

namespace telegram {
namespace tl {
class TLObject;
class TLMethod;
class TLVector;
class TLIntVector;
class TLLongVector;
class TLStringVector;
class TLContext;
}
}

namespace telegram {
namespace tl {

class StreamingUtils {
public:
	static void writeByte(char v, QDataStream& stream);
	static void writeInt(int v, QDataStream& stream);
	static void writeLong(qlonglong v, QDataStream& stream);
	static void writeDouble(double v, QDataStream& stream);
	static void writeByteArray(const char* v, int size, QDataStream& stream);
	static void writeByteArray(const QByteArray& v, QDataStream& stream);
	static void writeTLBool(bool v, QDataStream& stream);
	static void writeTLString(const QString v, QDataStream& stream);
	static void writeTLBytes(const QByteArray& v, QDataStream& stream);
	static void writeTLObject(const TLObject* v, QDataStream& stream);
	static void writeTLMethod(const TLMethod* v, QDataStream& stream);
	static void writeTLVector(const TLVector* v, QDataStream& stream);

	static int readByte(QDataStream& stream);
	static int readInt(QDataStream& stream);
	static qlonglong readLong(QDataStream& stream);
	static double readDouble(QDataStream& stream);
	static QString readTLString(QDataStream& stream);
	static TLObject* readTLObject(QDataStream& stream, TLContext* context);
	static TLMethod* readTLMethod(QDataStream& stream, TLContext* context);
	static QByteArray readBytes(int count, QDataStream& stream);
	static QByteArray readTLBytes(QDataStream& stream);
	static TLVector* readTLVector(QDataStream& stream, TLContext* context);
	static TLIntVector* readTLIntVector(QDataStream& stream,
			TLContext* context);
	static TLLongVector* readTLLongVector(QDataStream& stream,
			TLContext* context);
	static TLStringVector* readTLStringVector(QDataStream& stream,
			TLContext* context);
	static bool readTLBool(QDataStream& stream);

	static QByteArray bignumLongToByteArray(qlonglong v);

private:
	StreamingUtils() {
	}
};

} /* namespace tl */
} /* namespace telegram */
#endif /* STREAMINGUTILS_HPP_ */
