# 默认目标
all: release

# Debug 目标：添加调试标志
debug: CXXFLAGS += -g -O0
debug: myexp

# Release 目标：添加优化标志
release: CXXFLAGS += -O2 -DNDEBUG
release: myexp

logger.o: logger.cpp logger.h CS149intrin.h CS149intrin.cpp
	g++ $(CXXFLAGS) -c logger.cpp

CS149intrin.o: CS149intrin.cpp CS149intrin.h logger.cpp logger.h
	g++ $(CXXFLAGS) -c CS149intrin.cpp

myexp: CS149intrin.o logger.o main.cpp
	g++ $(CXXFLAGS) -I../common logger.o CS149intrin.o main.cpp -o myexp

clean:
	rm -f *.o myexp *~