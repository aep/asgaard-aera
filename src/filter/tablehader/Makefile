TOP=$(shell pwd)/../../..

CLAYI=$(TOP)/src/shared/clay/

$(TOP)/plugins/libaera1.filter.tableheader.so:main.clay $(CLAYI)/aera/generated.clay $(CLAYI)/aera/aera.clay $(CLAYI)/aera/primitives.clay
	clay -I$(CLAYI) -g -shared main.clay -o $@

include $(CLAYI)/aera/clay.mk
