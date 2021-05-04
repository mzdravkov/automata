CC=g++
CFLAGS=-Wall -g
SOURCE=src
BUILD=build

executable: ${BUILD}/main.o ${BUILD}/state.o ${BUILD}/fsm.o ${BUILD}/custom_string.o ${BUILD}/automation_exception.o
	$(CC) $(CFLAGS) -o automata ${BUILD}/main.o ${BUILD}/state.o ${BUILD}/fsm.o ${BUILD}/custom_string.o ${BUILD}/automation_exception.o

${BUILD}/main.o: ${SOURCE}/main.cpp ${SOURCE}/state.h ${SOURCE}/fsm.h ${SOURCE}/custom_string.h
	$(CC) $(CFLAGS) -o ${BUILD}/main.o -c ${SOURCE}/main.cpp -I./src

${BUILD}/fsm.o: ${SOURCE}/fsm.h ${SOURCE}/fsm.cpp ${SOURCE}/automation_exception.h ${SOURCE}/state.h ${SOURCE}/custom_string.h
	$(CC) $(CFLAGS) -o ${BUILD}/fsm.o -c ${SOURCE}/fsm.cpp -I./src

${BUILD}/state.o: ${SOURCE}/state.h ${SOURCE}/state.cpp ${SOURCE}/custom_string.h
	$(CC) $(CFLAGS) -o ${BUILD}/state.o -c ${SOURCE}/state.cpp -I./src

${BUILD}/custom_string.o: ${SOURCE}/custom_string.h ${SOURCE}/custom_string.cpp
	$(CC) $(CFLAGS) -o ${BUILD}/custom_string.o -c ${SOURCE}/custom_string.cpp -I./src

${BUILD}/automation_exception.o: ${SOURCE}/automation_exception.h ${SOURCE}/automation_exception.cpp ${SOURCE}/custom_string.h
	$(CC) $(CFLAGS) -o ${BUILD}/automation_exception.o -c ${SOURCE}/automation_exception.cpp -I./src

clean:
	rm ${BUILD}/*
