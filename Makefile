CXX = g++
CXXFLAGS = `pkg-config --cflags --libs opencv4`
TARGET = imageBrowser
OBJS = imageBrowser.o imageUtils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

imageBrowser.o: imageBrowser.cpp imageUtils.h
	$(CXX) -c $< $(CXXFLAGS)

imageUtils.o: imageUtils.cpp imageUtils.h
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)