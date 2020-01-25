#include "CompositeReader.h"

#include <string>
#include <iostream>
#include <assert.h>

#include <proton/codec.h>
#include <sstream>
#include "corda-utils/include/debug.h"
#include "Reader.h"
#include "serialiser/reader/IReader.h"
#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************/

const std::string
amqp::internal::serialiser::reader::
CompositeReader::m_name { // NOLINT
    "Composite Reader"
};

/******************************************************************************
 *
 *
 ******************************************************************************/

amqp::internal::serialiser::reader::
CompositeReader::CompositeReader (
        std::string type_,
        sVec<std::weak_ptr<Reader>> & readers_
) : m_readers (readers_)
  , m_type (std::move (type_))
{
    DBG ("MAKE CompositeReader: " << m_type << ": " << m_readers.size() << std::endl); // NOLINT
    for (auto const & reader : m_readers) {
        assert (reader.lock());
        if (auto r = reader.lock()) {
            DBG ("  prop: " << r->name() << " " << r->type() << std::endl); // NOLINT
        }
    }
}

/******************************************************************************/

const std::string &
amqp::internal::serialiser::reader::
CompositeReader::name() const {
    return m_name;
}

/******************************************************************************/

const std::string &
amqp::internal::serialiser::reader::
CompositeReader::type() const  {
    return m_type;
}

/******************************************************************************/

std::any
amqp::internal::serialiser::reader::
CompositeReader::read (pn_data_t * data_) const {
    return std::any(1);
}

/******************************************************************************/

std::string
amqp::internal::serialiser::reader::
CompositeReader::readString (pn_data_t * data_) const {
    pn_data_next (data_);
    proton::auto_enter ae (data_);

    return "Composite";
}

/******************************************************************************/

sVec<uPtr<amqp::serialiser::reader::IValue>>
amqp::internal::serialiser::reader::
CompositeReader::_dump (
        pn_data_t * data_,
        const amqp::schema::ISchema & schema_
) const {
    DBG ("Read Composite: "
        << m_name
        << " : "
        << type()
        << std::endl); // NOLINT

    proton::is_described (data_);
    proton::auto_enter ae (data_);

    const auto & it = schema_.fromDescriptor (
            proton::get_symbol<std::string>(data_));

    auto & fields = dynamic_cast<const schema::Composite &> (
            it).fields();

    assert (fields.size() == m_readers.size());

    pn_data_next (data_);

    sVec<uPtr<amqp::serialiser::reader::IValue>> read;
    read.reserve (fields.size());

    proton::is_list (data_);
    {
        proton::auto_enter ae2 { data_ };

        for (size_t i (0) ; i < m_readers.size() ; ++i) {
            if (auto l =  m_readers[i].lock()) {
                DBG (fields[i]->name() << " "
                    << (l ? "true" : "false") << std::endl); // NOLINT

                read.emplace_back (l->dump (fields[i]->name(), data_, schema_));
            } else {
                std::stringstream s;
                s << "null field reader: " << fields[i]->name();
                throw std::runtime_error (s.str());
            }
        }
    }

    return read;
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
CompositeReader::dump (
    const std::string & name_,
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_) const
{
    proton::auto_next an (data_);

    return std::make_unique<TypedPair<sVec<uPtr<amqp::serialiser::reader::IValue>>>> (
        name_,
        _dump(data_, schema_));
}

/******************************************************************************/

/**
 *
 */
uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
CompositeReader::dump (
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_) const
{
    proton::auto_next an (data_);

    return std::make_unique<TypedSingle<sVec<uPtr<amqp::serialiser::reader::IValue>>>> (
        _dump (data_, schema_));
}

/******************************************************************************/
