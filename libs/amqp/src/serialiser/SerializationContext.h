#pragma once

/******************************************************************************/

#include "amqp/include/serialiser/ISerialisationContext.h"

/******************************************************************************/

/**
 * Purposfully *not* on the internal namesapce as this is one part of the implementation
 * we're going to need to expse
 */
namespace amqp::serialiser {

    class SerializationContext : public amqp::serialiser::ISerialisationContext {
        uPtr<AMQPBlob> serialize (const amqp::serialisable::ISerialisable &) const override;
    };

}

/******************************************************************************/
