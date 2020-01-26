#pragma once

/******************************************************************************/

#include <corda-utils/include/types.h>

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/serialiser/ISerialisationContext.h"

/******************************************************************************
 *
 * c;ass ISerialisable
 *
 ******************************************************************************/

namespace amqp::serialisable {

    class ISerialisable {
        private :
            std::string m_fingerprint;

        public :
            /**
             * Main interface for serializable objects. It woule be expected
             * that this is invoked for objects obj.serialise (context)
             */
            uPtr<AMQPBlob>
            serialise (amqp::serialiser::ISerialisationContext & ctx_) const {
                return ctx_.serialize (*this);
            }

            virtual uPtr<AMQPBlob> serialiseImpl() const = 0;
    };

}
/******************************************************************************/
