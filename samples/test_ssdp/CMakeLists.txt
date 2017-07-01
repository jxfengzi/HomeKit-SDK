#-----------------------------------------------------------------------------
#
# test-ssdp
#
#-----------------------------------------------------------------------------

SET(SRC ExampleSsdpHandler.h
        ExampleSsdpHandler.c
        test_ssdp.c
        )

ADD_EXECUTABLE(test_ssdp ${SRC})
TARGET_LINK_LIBRARIES(test_ssdp ${HOMEKIT_LIB})
