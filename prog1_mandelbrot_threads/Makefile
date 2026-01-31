
CXX=g++ -m64
CXXFLAGS=-I../common -Iobjs/ -O3 -std=c++11 -Wall -fPIC

APP_NAME=mandelbrot
OBJDIR=objs
BINDIR=bin
COMMONDIR=../common

PPM_CXX=$(COMMONDIR)/ppm.cpp
PPM_OBJ=$(addprefix $(OBJDIR)/, $(subst $(COMMONDIR)/,, $(PPM_CXX:.cpp=.o)))


default: dirs $(BINDIR)/$(APP_NAME)

.PHONY: dirs clean

dirs:
		/bin/mkdir -p $(OBJDIR) $(BINDIR)

clean:
		/bin/rm -rf $(OBJDIR) $(BINDIR) *.ppm *~

OBJS=$(OBJDIR)/main.o $(OBJDIR)/mandelbrotSerial.o $(OBJDIR)/mandelbrotThread.o $(PPM_OBJ)

$(BINDIR)/$(APP_NAME): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -lm -lpthread

$(OBJDIR)/%.o: %.cpp
		$(CXX) $< $(CXXFLAGS) -c -o $@

$(OBJDIR)/%.o: $(COMMONDIR)/%.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

$(OBJDIR)/main.o: $(COMMONDIR)/CycleTimer.h

