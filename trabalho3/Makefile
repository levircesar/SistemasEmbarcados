TARGET = native

CONTIKI_PROJECT =  helloworld
all: $(CONTIKI_PROJECT)

BLINKLED_DIR = ./
BLINKLED_SRC = blinkled.c 


PROJECTDIRS += $(BLINKLED_DIR) 
PROJECT_SOURCEFILES += $(BLINKLED_SRC) 

CONTIKI = ../../contiki-ng
include $(CONTIKI)/Makefile.include
