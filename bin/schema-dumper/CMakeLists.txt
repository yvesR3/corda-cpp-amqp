include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)
link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/proton-wrapper)

add_executable (schema-dumper main SchemaDumper.cxx)

target_link_libraries (schema-dumper amqp proton-wrapper qpid-proton)
