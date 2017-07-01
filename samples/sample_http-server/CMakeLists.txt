#-----------------------------------------------------------------------------
#
# example-httpserver
#
#-----------------------------------------------------------------------------

SET(SRC ExampleHandler.h
        ExampleHandler.c
        sample_http_server.c
        )

ADD_EXECUTABLE(sample_http_server ${SRC})
TARGET_LINK_LIBRARIES(sample_http_server ${HOMEKIT_LIB})
