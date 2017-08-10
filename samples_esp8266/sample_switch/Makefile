#############################################################
# Required variables for each makefile
# Discard this section from all parent makefiles
# Expected variables (with automatic defaults):
#   CSRCS (all "C" files in the dir)
#   SUBDIRS (all subdirs with a Makefile)
#   GEN_LIBS - list of libs to be generated ()
#   GEN_IMAGES - list of object file images to be generated ()
#   GEN_BINS - list of binaries to be generated ()
#   COMPONENTS_xxx - a list of libs/objs in the form
#     subdir/lib to be extracted and rolled up into
#     a generated lib/image xxx.a ()
#
TARGET = eagle
#FLAVOR = release
FLAVOR = debug

#EXTRA_CCFLAGS += -u

ifndef PDIR # {
GEN_IMAGES= eagle.app.v6.out
GEN_BINS= eagle.app.v6.bin
SPECIAL_MKTARGETS=$(APP_MKTARGETS)
SUBDIRS= hap_accessory      \
         hap_persistence    \
         hap_user           \
         hap_wdc

endif # } PDIR

LDDIR = $(SDK_PATH)/ld

CCFLAGS += -Os -DESP -DLWIP_SOCKET -DLWIP_TIMEVAL_PRIVATE=1 -DICACHE_FLASH

TARGET_LDFLAGS =		\
	-nostdlib		\
	-Wl,-EL \
	--longcalls \
	--text-section-literals

ifeq ($(FLAVOR),debug)
    #TARGET_LDFLAGS += -g -O2
    TARGET_LDFLAGS += -O2
endif

ifeq ($(FLAVOR),release)
    #TARGET_LDFLAGS += -g -O0
    TARGET_LDFLAGS += -O0
endif

COMPONENTS_eagle.app.v6 = \
	hap_accessory/libhap_accessory.a        \
	hap_persistence/libhap_persistence.a    \
	hap_wdc/libhap_wdc.a                    \
	hap_user/libhap_user.a                  

LINKFLAGS_eagle.app.v6 = \
	-L$(SDK_PATH)/lib        \
	-L../../lib/esp8266      \
	-Wl,--gc-sections   \
	-nostdlib	\
    -T$(LD_FILE)   \
	-Wl,--no-check-sections	\
    -u call_user_start	\
	-Wl,-static						\
	-Wl,--start-group					\
	-lcirom \
	-lcrypto	\
	-lespconn	\
	-lespnow	\
	-lfreertos	\
	-lgcc					\
	-lhal					\
	-llwip	\
	-lmain	\
	-lmesh	\
	-lmirom	\
	-lnet80211	\
	-lnopoll	\
	-lphy	\
	-lpp	\
	-lpwm	\
	-lsmartconfig	\
	-lspiffs	\
	-lssl	\
	-lwpa	\
	-lwps		\
    -lhomekit   \
    -ldriver    \
	$(DEP_LIBS_eagle.app.v6)					\
	-Wl,--end-group

DEPENDS_eagle.app.v6 = \
                $(LD_FILE) \
                $(LDDIR)/eagle.rom.addr.v6.ld

#############################################################
# Configuration i.e. compile options etc.
# Target specific stuff (defines etc.) goes in here!
# Generally values applying to a tree are captured in the
#   makefile at its root level - these are then overridden
#   for a subtree within the makefile rooted therein
#

#UNIVERSAL_TARGET_DEFINES =		\

# Other potential configuration flags include:
#	-DTXRX_TXBUF_DEBUG
#	-DTXRX_RXBUF_DEBUG
#	-DWLAN_CONFIG_CCX
CONFIGURATION_DEFINES =	-DICACHE_FLASH

DEFINES +=				\
	$(UNIVERSAL_TARGET_DEFINES)	\
	$(CONFIGURATION_DEFINES)

DDEFINES +=				\
	$(UNIVERSAL_TARGET_DEFINES)	\
	$(CONFIGURATION_DEFINES)


#############################################################
# Recursion Magic - Don't touch this!!
#
# Each subtree potentially has an include directory
#   corresponding to the common APIs applicable to modules
#   rooted at that subtree. Accordingly, the INCLUDE PATH
#   of a module can only contain the include directories up
#   its parent path, and not its siblings
#
# Required for each makefile to inherit from the parent
#

INCLUDES := $(INCLUDES) -I $(PDIR)include               \
    -I $(PDIR)../../include/homekit/HapAccessory        \
    -I $(PDIR)../../include/homekit/HapSupport          \
    -I $(PDIR)../../include/homekit/IotCrypto           \
    -I $(PDIR)../../include/homekit/IotThingManager     \
    -I $(PDIR)../../include/homekit/IotTypedef          \
    -I $(PDIR)../../include/homekit/Netty               \
    -I $(PDIR)../../include/homekit/TinyBase            \
    -I $(PDIR)../../include/homekit/TinyContainer       \
    -I $(PDIR)../../include/homekit/TinyPortable

# INCLUDES := $(INCLUDES) -I $(PDIR)include               \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/HapAccessory        \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/HapSupport          \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/IotCrypto           \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/IotThingManager     \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/IotTypedef          \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/Netty               \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/TinyBase            \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/TinyContainer       \
# 	    -I /home/ouyang/extdisk/github.ouyang/iot/sdk/c/source/src/TinyPortable

sinclude $(SDK_PATH)/Makefile

.PHONY: FORCE
FORCE:
