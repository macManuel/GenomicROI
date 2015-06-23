TARGET = GenomicROI
PREFIX =  /usr/local

HEADER_PATH = $(PREFIX)/include/
LIB_PATH = $(PREFIX)/lib/

HEADER = GenomicROI.h GenomicROIPromoter.h
OBJECTS = GenomicROI.o GenomicROIPromoter.o
LIBS = libFastScience.dylib

CC = g++
CFLAGS = -std=c++11 -Wall -I$(HEADER_PATH)

$(TARGET): $(OBJECTS) $(HEADERS) main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB_PATH)/$(LIBS) $(OBJECTS) main.cpp

GenomicROI.o : GenomicROI.cpp GenomicROI.h
	$(CC) $(CFLAGS) -c -o GenomicROI.o GenomicROI.cpp 

GenomicROIPromoter.o : GenomicROIPromoter.cpp GenomicROIPromoter.h
	$(CC) $(CFLAGS) -c -o GenomicROIPromoter.o GenomicROIPromoter.cpp


install:
	cp -p $(TARGET) $(PREFIX)/bin/

clean:
	rm -r $(OBJECTS)
	rm -r $(TARGET)