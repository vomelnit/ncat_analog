CC = g++ -std=c++11
TARGET_DIR =./release
TARGET = $(TARGET_DIR)/ncat_analog
CC = g++ -std=c++11
CFLAGS = -Wall -Wextra #-Werror
SRC = ./src/main.cpp \
	./src/cmd_argument_analyzer.cpp \
	./src/file_func.cpp \
	./src/server.cpp \

OBJ = $(SRC:.cpp=.o)
INCLUDES  = ./includes

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(CFLAGS) $(SRC) -I $(INCLUDES) #-ltermcap

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(TARGET)

re: fclean all
