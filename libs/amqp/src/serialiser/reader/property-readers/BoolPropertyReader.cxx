#include "BoolPropertyReader.h"

#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************
 *
 * BoolPropertyReader statics
 *
 ******************************************************************************/

const std::string
amqp::internal::serialiser::reader::
BoolPropertyReader::m_name { // NOLINT
        "Bool Reader"
};

/******************************************************************************/

const std::string
amqp::internal::serialiser::reader::
BoolPropertyReader::m_type { // NOLINT
        "bool"
};

/******************************************************************************
 *
 * BoolPropertyReader
 *
 ******************************************************************************/

std::any
amqp::internal::serialiser::reader::
BoolPropertyReader::read (pn_data_t * data_) const {
    return std::any (proton::readAndNext<bool> (data_));
}

/******************************************************************************/

std::string
amqp::internal::serialiser::reader::
BoolPropertyReader::readString (pn_data_t * data_) const {
    return std::to_string (proton::readAndNext<bool> (data_));
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
BoolPropertyReader::dump (
        const std::string & name_,
        pn_data_t * data_,
        const amqp::schema::ISchema & schema_) const
{
    return std::make_unique<TypedPair<std::string>> (
            name_,
            std::to_string (proton::readAndNext<bool> (data_)));
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
BoolPropertyReader::dump (
        pn_data_t * data_,
        const amqp::schema::ISchema & schema_) const
{
    return std::make_unique<TypedSingle<std::string>> (
            std::to_string (proton::readAndNext<bool> (data_)));
}

/******************************************************************************/

const std::string &
amqp::internal::serialiser::reader::
BoolPropertyReader::name() const {
    return m_name;
}

/******************************************************************************/

const std::string &
amqp::internal::serialiser::reader::
BoolPropertyReader::type() const {
    return m_type;
}

/******************************************************************************/