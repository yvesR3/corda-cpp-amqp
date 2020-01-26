#pragma once

/******************************************************************************/

#include "amqp/include/serializable/ISerializable.h"

/******************************************************************************/

class SerialiseMe : public amqp::serialisable::ISerialisable {
    private :
        int m_a;

    public :
        explicit SerialiseMe (int a_) : m_a { a_ } { }

        uPtr<amqp::AMQPBlob> serialiseImpl() const override;

//        uPtr<amqp::AMQPBlob> serialize (const amqp::serialiser::ISerialisationContext &) const override;
};

/******************************************************************************/
