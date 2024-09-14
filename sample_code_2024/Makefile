TARGET=./build/execution
CXX=g++
CXXFLAGS= -O2 -Wall -std=c++17
BUILD_DIR=build
SRC_DIR=src
SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(subst $(SRC_DIR),$(BUILD_DIR),$(SRCS:.cpp=.o))
CVINC=`pkg-config --cflags opencv`
CVLIB=`pkg-config --libs opencv`
CXXFLAGS += $(shell pkg-config --cflags opencv4)
LDFLAGS += $(shell pkg-config --libs opencv4)

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ ${CVINC} ${CVLIB} -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ ${CVINC} ${CVLIB} -o $@

clean:
	sudo rm -rf $(BUILD_DIR) $(TARGET)
	sudo chmod -R 777 ./results
