#-----------------------------------------------------------------------------
#
# sample-lightbulb
#
#-----------------------------------------------------------------------------

SET(SRC
        sample_lightbulb.c
        mysocket.h
        mysocket.c
        persistence/HapPersistenceImpl.h
        persistence/HapPersistenceImpl.c
        hap/AccessoryHost.h
        hap/AccessoryHost.c
        hap/AccessoryCategoryIdentifier.h
        hap/accessory/DeskLamp.h
        hap/accessory/DeskLamp.c
        hap/services/Lightbulb.h
        hap/services/Lightbulb.c
        hap/characteristics/On.h
        hap/characteristics/On.c
        )

ADD_EXECUTABLE(sample_lightbulb ${SRC})
TARGET_LINK_LIBRARIES(sample_lightbulb ${HOMEKIT_LIB})
