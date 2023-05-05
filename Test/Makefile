TARGET = unittest
SRC = ./*.cpp
INCLUDE = -I ../Include/
FLAGS = -lgtest -lpthread -std=c++1z -g

$(TARGET) : $(SRC)
	g++ $(SRC) -o $(TARGET) $(INCLUDE) $(FLAGS)

clean:
	rm -rf $(TARGET)