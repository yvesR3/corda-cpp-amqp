#include "EnvelopeDescriptor.h"

#include "described-types/Schema.h"
#include "described-types/Envelope.h"
#include "proton-wrapper/include/proton_wrapper.h"

#include "corda-utils/include/types.h"
#include "corda-utils/include/debug.h"

#include <sstream>

/******************************************************************************/

namespace {

    const std::string
    consumeBlob (pn_data_t * data_) {
        proton::is_described (data_);
        proton::auto_enter p (data_);
        return proton::get_symbol<std::string> (data_);
    }

}

/******************************************************************************
 *
 * amqp::internal::schema::descriptors::EnvelopeDescriptor
 *
 ******************************************************************************/

/*
 * Described types are a pair of a key and a list of elements. Having
 * parsed this as such a type we should be in the stack at the point
 * where we found the list and don't expect to have entered it before
 * calling this
 */
void
amqp::internal::schema::descriptors::
EnvelopeDescriptor::readRaw (
    pn_data_t * data_,
    std::stringstream & ss_,
    const AutoIndent & ai_
) const {
    // lets just make sure we haven't entered this already
    proton::is_list (data_);

    {
        AutoIndent ai { ai_ };
        proton::auto_enter p (data_);

        ss_ << ai << "1]" << std::endl;
        AMQPDescriptorRegistory[pn_data_type(data_)]->readRaw (
                (pn_data_t *)proton::auto_next (data_), ss_, AutoIndent { ai });


        ss_ << ai << "2]" << std::endl;
        AMQPDescriptorRegistory[pn_data_type(data_)]->readRaw (
                (pn_data_t *)proton::auto_next(data_), ss_, AutoIndent { ai });
    }
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
EnvelopeDescriptor::readAvro (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const {
    DBG ("readAvro::Envelope" << std::endl);

    // lets just make sure we haven't entered this already
    proton::is_list (data_);

    {
        // skip the first element of the envelope as that's the data
        // portion, for this we only care abot the schema
        proton::auto_enter p (data_, true /* enter and move to next */);

        AMQPDescriptorRegistory[pn_data_type(data_)]->readAvro (
                (pn_data_t *)proton::auto_next(data_), ss_, ai_);
    }
}

/******************************************************************************/

amqp::internal::schema::descriptors::
EnvelopeDescriptor::EnvelopeDescriptor (
    std::string symbol_,
    int val_
) : AMQPDescriptor (std::move (symbol_), val_) {

}

/******************************************************************************/

uPtr<amqp::schema::ISchemaElement>
amqp::internal::schema::descriptors::
EnvelopeDescriptor::build (pn_data_t * data_) const {
    DBG ("ENVELOPE" << std::endl); // NOLINT

    validateAndNext(data_);

    proton::auto_enter p (data_);

    /*
     * The actual blob... if this was java we would use the type symbols
     * in the blob to look up serialisers in the cache... but we don't
     * have any so we are actually going to need to use the schema
     * which we parse *after* this to be able to read any data!
     */
    std::string outerType = consumeBlob(data_);

    pn_data_next (data_);

    /*
     * The schema
     */
    auto schema = descriptors::dispatchDescribed<schema::Schema> (data_);

    pn_data_next(data_);

    /*
     * The transforms schema
     */
    // Skip for now
    // dispatchDescribed (data_);

    return std::make_unique<schema::Envelope> (schema::Envelope (schema, outerType));
}

/******************************************************************************/

