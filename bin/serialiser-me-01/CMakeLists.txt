include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)
link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/proton-wrapper)

set (target serialise-me)

add_executable (${target} main SerialiseMe.cxx)

target_link_libraries (${target} amqp proton-wrapper qpid-proton)
