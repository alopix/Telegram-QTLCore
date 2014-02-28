/*
 * TLContext.hpp
 *
 *  Created on: Feb 2, 2014
 *      Author: dustin
 */

#ifndef TLCONTEXT_HPP_
#define TLCONTEXT_HPP_

#include <QObject>

namespace telegram {
namespace tl {
class TLObject;
class TLVector;
class TLIntVector;
class TLLongVector;
class TLStringVector;
}
}

namespace telegram {
namespace tl {

class TLContext: public QObject {
Q_OBJECT

public:
	TLContext(QObject* parent = 0);

	virtual ~TLContext();

	bool isSupportedObject(TLObject& object);
	bool isSupportedObject(int classId);

	void registerClass(int classId, const QMetaObject& metaObject);
	void registerCompatClass(int classId, const QMetaObject& metaObject);
	TLObject* convertCompatClass(TLObject* src);

	TLObject* deserializeMessage(QByteArray& data);
	TLObject* deserializeMessage(int classId, QDataStream& stream);
	TLObject* deserializeMessage(QDataStream& data);
	TLVector* deserializeVector(QDataStream& stream);
	TLIntVector* deserializeIntVector(QDataStream& stream);
	TLLongVector* deserializeLongVector(QDataStream& stream);
	TLStringVector* deserializeStringVector(QDataStream& stream);

protected:
	TLObject* convertCompatClass(TLObject& src);

private:
	static QByteArray gUncompress(const QByteArray& data);

	QMap<int, const QMetaObject*> mRegisteredClasses;
	QMap<int, const QMetaObject*> mRegisteredCompatClasses;
};

} /* namespace tl */
} /* namespace telegram */
#endif /* TLCONTEXT_HPP_ */
