#pragma once

/******************************************************************************/

#include <corda-utils/include/types.h>

#include "amqp/include/AMQPBlob.h"

/******************************************************************************
 *
 * Forward declarations
 *
 ******************************************************************************/

namespace amqp::serialiser {

    class ISerialisationContext;

}

/******************************************************************************
 *
 * c;ass ISerialisable
 *
 ******************************************************************************/

namespace amqp::serialisable {

    class ISerialisable {
        public :
            virtual uPtr<AMQPBlob> serialize (amqp::serialiser::ISerialisationContext &) const = 0;
    };

}
/******************************************************************************/
