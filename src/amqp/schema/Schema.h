#pragma once

/******************************************************************************/

#include <map>
#include <iosfwd>

#include "types.h"
#include "Composite.h"
#include "Descriptor.h"

#include "amqp/AMQPDescribed.h"

/******************************************************************************/

namespace amqp::internal::schema {

    /*
     * A Corda AMQP Scehma Composite type has:
     *
     * val name: String,
     * val label: String?,
     * val provides: List<String>,
     * val descriptor: Descriptor,
     * val fields: List<Field>
     */
    class Schema : public AMQPDescribed {
        public :
            friend std::ostream & operator << (std::ostream &, const Schema &);

        private :
            upStrMap_t<AMQPTypeNotation> m_types;
            std::map<std::string, std::string> m_descriptorToType;

        public :
            Schema (std::map<std::string, std::unique_ptr<AMQPTypeNotation>> & types_);

            const std::map<std::string, std::unique_ptr<AMQPTypeNotation>> & types() const;

            decltype (m_types)::const_iterator fromType (const std::string &) const;
            decltype (m_types)::const_iterator fromDescriptor (const std::string &) const;
            decltype (m_types)::const_iterator end() const;
            decltype (m_types)::const_iterator begin() const;
    };

}

/******************************************************************************/
