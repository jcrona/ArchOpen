MEDIOS_SRC_PATH_TMP = $(shell pwd)
export MEDIOS_SRC_PATH = $(MEDIOS_SRC_PATH_TMP)/../..

include $(MEDIOS_SRC_PATH)/Makefile.conf

BUILD_DIR = ./

LIBS = $(MEDIOS_SRC_PATH)/lib/libmedios.a
LDFLAGS = $(MEDIOS_SRC_PATH)/lib/apps_start.o $(MEDIOS_SRC_PATH)/lib/apps_stop.o -L$(MEDIOS_SRC_PATH)/lib -lmedios --emit-relocs

TARGET = pacman

all: $(LIBS) do_build
	@$(LD)  *.o -o $(TARGET).med $(LDFLAGS)
	@cp -f $(TARGET).med ../

$(LIBS):
	@make -C $(MEDIOS_SRC_PATH) --no-print-directory medios_lib

include $(MEDIOS_SRC_PATH)/default.rule