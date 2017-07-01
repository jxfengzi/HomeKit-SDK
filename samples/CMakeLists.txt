CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(HomeKitSamples C)

SET(PROJ_NAME "HomeKitSamples")

#---------------------------------------------------------------------------------------
#
# for Static
#
#---------------------------------------------------------------------------------------
ADD_DEFINITIONS(-DTINY_STATIC)
ADD_DEFINITIONS(-DIOT_TYPEDEF_STATIC)
ADD_DEFINITIONS(-DIOT_CRYPTO_STATIC)
ADD_DEFINITIONS(-DIOT_THING_STATIC)
ADD_DEFINITIONS(-DNETTY_STATIC)
ADD_DEFINITIONS(-DBONJOUR_STATIC)
ADD_DEFINITIONS(-DHAP_ACCESSORY_STATIC)

#---------------------------------------------------------------------------------------
#
# for GCC
#
#---------------------------------------------------------------------------------------
ADD_DEFINITIONS(-Wno-multichar)
ADD_DEFINITIONS(-Wno-pointer-to-int-cast)
ADD_DEFINITIONS(-O3)
ADD_DEFINITIONS(-fPIC)
ADD_DEFINITIONS(-std=c99)

#---------------------------------------------------------------------------------------
#
# include dir
#
#---------------------------------------------------------------------------------------
SET(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/../include/homekit)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/TinyBase)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/TinyContainer)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/TinyStringUtil)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/TinyJson)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/TinyPortable)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/Netty)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotCrypto)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotTypedef)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotThingManager)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/Bonjour)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/HapSupport)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/HapAccessory)

#---------------------------------------------------------------------------------------
#
# link dir
#
#---------------------------------------------------------------------------------------
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../lib/linux-x86_64)

#---------------------------------------------------------------------------------------
#
# lib
#
#---------------------------------------------------------------------------------------
SET(HOMEKIT_LIB homekit)

#-------------------------------------------------------------------------------------
# output dir
#-------------------------------------------------------------------------------------
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output)
MESSAGE(STATUS "executable output:  ${EXECUTABLE_OUTPUT_PATH}")
MESSAGE(STATUS "library output: ${LIBRARY_OUTPUT_PATH}")

#-------------------------------------------------------------------------------------
# samples
#-------------------------------------------------------------------------------------
ADD_SUBDIRECTORY(test_http-message)
ADD_SUBDIRECTORY(test_ssdp)
ADD_SUBDIRECTORY(sample_http-server)
ADD_SUBDIRECTORY(sample_lightbulb)
