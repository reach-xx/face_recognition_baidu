all:
	arm-hisiv400-linux-g++ -std=c++11 -o face_recognition face_recognition.cpp -lcurl -lcrypto -lssl -lz -ljsoncppv1.8.3 -L/home/reach/Hi-R11/glibs -I./include -I./
