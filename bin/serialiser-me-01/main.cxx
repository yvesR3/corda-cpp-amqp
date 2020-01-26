#include <cstdlib>

/******************************************************************************/

#include "SerialiseMe.h"
#include "amqp/src/serialiser/SerializationContext.h"

/******************************************************************************/

int
main (int argc, char **argv) {
    amqp::serialiser::SerializationContext ctx;

    SerialiseMe serialiseMe (100);

    serialiseMe.serialise (ctx);

    return EXIT_SUCCESS;
}

/******************************************************************************/
