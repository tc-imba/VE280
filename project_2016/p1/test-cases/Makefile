#variable definition

CC = g++

MAINSRCS = p1.cpp
OTHSRCS = 
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(MAINSRCS:.cpp=)

CFLAGS = -g -Wall

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all clean 
