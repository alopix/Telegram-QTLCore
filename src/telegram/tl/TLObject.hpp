/*
 * TLObject.hpp
 *
 *  Created on: Feb 2, 2014
 *      Author: dustin
 */

#ifndef TLOBJECT_HPP_
#define TLOBJECT_HPP_

#include <QObject>

namespace telegram {
namespace tl {
class TLContext;
}
}

namespace telegram {
namespace tl {

class TLObject: public QObject {
Q_OBJECT

Q_PROPERTY(int classId READ classId CONSTANT)
public:
	TLObject(QObject* parent = 0) :
			QObject(parent) {
	}

	virtual ~TLObject() {
	}

	virtual int classId() const = 0;

	QByteArray serialize();
	void serialize(QDataStream& stream);
	void deserialize(QDataStream& stream, TLContext* context);

	virtual void serializeBody(QDataStream& stream);
	virtual void deserializeBody(QDataStream& stream, TLContext* context);
};

} /* namespace tl */
} /* namespace telegram */
Q_DECLARE_METATYPE(telegram::tl::TLObject*)

#endif /* TLOBJECT_HPP_ */
