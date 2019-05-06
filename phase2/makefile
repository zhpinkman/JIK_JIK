CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
JEEK = server/jeekjeek

all: $(BUILD_DIR) server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/server_main.o: server/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/server_main.o

server.out: $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o $(BUILD_DIR)/jeeker.o $(BUILD_DIR)/user.o $(BUILD_DIR)/text.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/jeek.o $(BUILD_DIR)/interface.o $(BUILD_DIR)/func.o $(BUILD_DIR)/notification.o
	$(CC) $(CF) $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o  $(BUILD_DIR)/jeeker.o $(BUILD_DIR)/user.o $(BUILD_DIR)/text.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/jeek.o $(BUILD_DIR)/interface.o $(BUILD_DIR)/func.o $(BUILD_DIR)/notification.o  -o server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null



$(BUILD_DIR)/notification.o: $(JEEK)/notification.cpp
	g++ -c $(JEEK)/notification.cpp -o $(BUILD_DIR)/notification.o
$(BUILD_DIR)/func.o: $(JEEK)/func.cpp
	g++ -c $(JEEK)/func.cpp  -o $(BUILD_DIR)/func.o
$(BUILD_DIR)/jeeker.o: $(JEEK)/jeeker.cpp
	g++ -std=c++11 -c $(JEEK)/jeeker.cpp  -o $(BUILD_DIR)/jeeker.o
$(BUILD_DIR)/user.o: $(JEEK)/user.cpp
	g++ -c $(JEEK)/user.cpp -o $(BUILD_DIR)/user.o
$(BUILD_DIR)/text.o: $(JEEK)/text.cpp
	g++ -c $(JEEK)/text.cpp -o $(BUILD_DIR)/text.o
$(BUILD_DIR)/comment.o: $(JEEK)/comment.cpp
	g++ -c $(JEEK)/comment.cpp -o $(BUILD_DIR)/comment.o
$(BUILD_DIR)/jeek.o : $(JEEK)/jeek.cpp
	g++ -c $(JEEK)/jeek.cpp -o $(BUILD_DIR)/jeek.o
$(BUILD_DIR)/interface.o : $(JEEK)/interface.cpp
	g++ -c $(JEEK)/interface.cpp -o $(BUILD_DIR)/interface.o
