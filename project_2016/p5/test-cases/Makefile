# variable definition

CC = g++

DEFS =
LIBS =
INCLUDES = -I.
HEADERS = dlist.h
TEMPLATES = dlist.cpp
MAINSRCS = call.cpp calc.cpp test-all.cpp test-exception.cpp
OTHSRCS =
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(MAINSRCS:.cpp=)

CFLAGS = -g -Wall $(INCLUDES) $(DEFS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

# $(TARGETS): $(OBJS)
# 	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS) $(LIBS)
call: $(OBJS)
	$(CC) $(CFLAGS) -o $@ call.o $(LIBS)

calc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ calc.o $(LIBS)

test-all: $(OBJS)
	$(CC) $(CFLAGS) -o $@ test-all.o $(LIBS)

depend:
	makedepend -Y $(INCLUDES) $(SRCS)

memcheck: $(TARGETS)
	@valgrind --leak-check=full ./$(TARGETS) < complex-sample

tags: $(SRCS) $(HEADERS) $(TEMPLATES)
	ctags $^

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all depend memcheck tags clean 
# DO NOT DELETE

testl.o: dlist.h dlist.cpp 
