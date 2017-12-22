CC=arm-hisiv400-linux-g++ -g -Wall -std=c++11
#CC=g++ -g -Wall -std=c++11

LDFLAGS = -L./arm_lib -I./include -I./

LIBS = -lcurl -lcrypto -lssl -lz -ljsoncppv1.8.3 -lthrift

HEADS = $(wildcard base/*.h) \
		$(wildcard boost/*.h)  \
		$(wildcard curl/*.h)  \
                $(wildcard include/json/*.h)  \
		$(wildcard openssl/*.h)  \
		$(wildcard thrift/*.h)

sources = $(wildcard *.c) 

S_OBJECTS = FaceIdentify.o   identify_types.o  \
		identify_constants.o  face_recognition.o

C_OBJECTS = FaceIdentify.o   identify_types.o  \
		identify_constants.o  Client.o

ALL_OBJECTS =$(S_OBJECTS)
ALL_OBJECTS +=Client.o


all:  dep  server  client
.PHONY: all


server:   $(S_OBJECTS)
	$(CC) -o $@  $(S_OBJECTS)  $(LIBS)  $(CFLAGS) $(LDFLAGS)


client:    $(C_OBJECTS)
	$(CC) -o $@  $(C_OBJECTS)  $(LIBS)  $(CFLAGS) $(LDFLAGS)



$(ALL_OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@
dep:
%.d : %.cpp
	rm -f $@; /
	$(CC) -MM  $< > $@
	sed 's,/($*/)/.o[ :]*,/1.o $@ : ,g' < $@
	rm -f $@

include $(sources:.c=.d)

.PHONY: clean

clean:
	-rm -f *.o  server  client
