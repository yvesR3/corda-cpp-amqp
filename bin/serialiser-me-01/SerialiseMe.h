#pragma once

/******************************************************************************/

#include "amqp/include/serializable/ISerializable.h"

/******************************************************************************/

class SerialiseMe : amqp::serialisable::ISerialisable {
    private :
        int m_a;

    public :
        SerialiseMe (int a_) : m_a { a_ } { }

        uPtr<amqp::AMQPBlob> serialize (amqp::serialiser::ISerialisationContext &) const;
};

/******************************************************************************/
