TARGET = native

CONTIKI_PROJECT =  helloworld
all: $(CONTIKI_PROJECT)

BLINKLED_DIR = ./
BLINKLED_SRC = blinkled.c 

SENSORES_DIR = ./
SENSORES_SRC = sensores.c 


PROJECTDIRS += $(BLINKLED_DIR) $(SENSORES_DIR)
PROJECT_SOURCEFILES += $(BLINKLED_SRC) $(SENSORES_SRC) 

CONTIKI = ../../contiki-ng
include $(CONTIKI)/Makefile.include
