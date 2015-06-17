INC_DIR:=./include/
SRC_DIR:=./src/
SRCS:=$(wildcard ./src/*.c)
LIBS:= -lpthread
CXX:=gcc
CXXFLAGS:= -Wall -g $(addprefix -I, $(INC_DIR) )
EXE:=./bin/main.o
$(EXE):$(SRCS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)


clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
