/*
 * TLGzipObject.cpp
 *
 *  Created on: Feb 12, 2014
 *      Author: dustin
 */

#include "TLGzipObject.hpp"

#include "StreamingUtils.hpp"

namespace telegram {
namespace tl {

void TLGzipObject::serializeBody(QDataStream& stream) const {
	StreamingUtils::writeTLBytes(mPackedData, stream);
}

void TLGzipObject::deserializeBody(QDataStream& stream, TLContext* context) {
	mPackedData = StreamingUtils::readTLBytes(stream);
	Q_UNUSED(context)
}

} /* namespace tl */
} /* namespace telegram */
