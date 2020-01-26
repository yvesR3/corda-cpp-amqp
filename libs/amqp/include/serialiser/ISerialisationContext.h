#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "corda-utils/include/types.h"

/******************************************************************************/

namespace amqp::serialisable {

    class ISerialisable;

}

/******************************************************************************/

namespace amqp::serialiser {

    class ISerialisationContext {
        public :
            virtual uPtr<AMQPBlob> serialize (const amqp::serialisable::ISerialisable &) const = 0;
    };

}

/******************************************************************************/
