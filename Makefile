CC=gcc 
INCDIR :=-I./include/common \
	-I./include/domoticz \
	-I./include/hardware \
	-I./include/mqqt_client 

COMPILE.c   = $(CC)  $(CFLAGS) $(INCDIR) -MMD -c
LINK.c      = $(CC)  $(LDFLAGS) -lpthread -lrt 
.PHONY: all
%.o:%.c
	$(COMPILE.c) $< -o $@

SRC_FILE := \
	src/mqqt_client/MQTTClient.c \
	src/mqqt_client/MQTTLinux.c \
	src/domoticz/DomoticzMessageParser.c \
	src/hardware/HardwareControl.c \
	main.c
	
OBJS := $(addsuffix .o, $(basename $(SRC_FILE)))
DEPS :=$(OBJS:.o=.d)

all:zhimigatewayservice

zhimigatewayservice:$(OBJS)
	$(LINK.c) $(OBJS) -lpaho-embed-mqtt3c -o $@

clean:
	rm -f $(OBJS) zhimigatewayservice

distclean:clean
	rm -f $(DEPS)


-include $(DEPS)

