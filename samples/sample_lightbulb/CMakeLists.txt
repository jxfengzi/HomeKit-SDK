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
        hap/services/AccessoryInformation.h
        hap/services/AccessoryInformation.c
        hap/characteristics/Identify.h
        hap/characteristics/Identify.c
        hap/characteristics/Manufacturer.h
        hap/characteristics/Manufacturer.c
        hap/characteristics/Model.h
        hap/characteristics/Model.c
        hap/characteristics/Name.h
        hap/characteristics/Name.c
        hap/characteristics/On.h
        hap/characteristics/On.c
        hap/characteristics/SerialNumber.h
        hap/characteristics/SerialNumber.c
        hap/characteristics/FirmwareRevision.h
        hap/characteristics/FirmwareRevision.c
        )

ADD_EXECUTABLE(sample_lightbulb ${SRC})
TARGET_LINK_LIBRARIES(sample_lightbulb ${HOMEKIT_LIB})
