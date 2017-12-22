CC=arm-hisiv400-linux-g++ -g -Wall -std=c++11
#CC=g++ -g -Wall -std=c++11

LDFLAGS = -L/home/reach/Hi-R11/glibs -I./include -I./

LIBS = -lcurl -lcrypto -lssl -lz -ljsoncppv1.8.3 -lthrift

face_recognition:
	$(CC) -o $@ FaceIdentify.cpp identify_types.cpp  identify_constants.cpp   face_recognition.cpp  $(LIBS)  $(CFLAGS) $(LDFLAGS) 
face_client:
	$(CC) -o $@ FaceIdentify.cpp identify_types.cpp  identify_constants.cpp   Client.cpp  $(LIBS)  $(CFLAGS) $(LDFLAGS) 

all:  face_recognition face_client

	
clean:
	rm -f ./*.o face_recognition face_client
