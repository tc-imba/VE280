#variable definition

CC = g++

HEADERS = card.h deck.h hand.h player.h rand.h
MAINSRCS = blackjack.cpp
OTHSRCS = card.cpp deck.cpp hand.cpp player.cpp rand.cpp

HANDSRCS = test-hand.cpp
HANDOTHS = card.cpp hand.cpp

DECKSRCS = test-deck.cpp
DECKOTHS = card.cpp deck.cpp

SIMPLESRCS = test-simple.cpp
COUNTINGSRCS = test-counting.cpp
PLAYEROTHS = card.cpp hand.cpp player.cpp

SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(MAINSRCS:.cpp=)

HSRCS = $(HANDSRCS) $(HANDOTHS)
HOBJS = $(HSRCS:.cpp=.o)
HTARGETS = $(HANDSRCS:.cpp=)

DSRCS = $(DECKSRCS) $(DECKOTHS)
DOBJS = $(DSRCS:.cpp=.o)
DTARGETS = $(DECKSRCS:.cpp=)

SSRCS = $(SIMPLESRCS) $(PLAYEROTHS)
SOBJS = $(SSRCS:.cpp=.o)
STARGETS = $(SIMPLESRCS:.cpp=)

CSRCS = $(COUNTINGSRCS) $(PLAYEROTHS)
COBJS = $(CSRCS:.cpp=.o)
CTARGETS = $(COUNTINGSRCS:.cpp=)

CFLAGS = -g -Wall

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

#$(HOBJS): $(HSRCS)
#	$(CC) $(CFLAGS) -o $@ -c $<

all: $(TARGETS) $(HTARGETS) $(DTARGETS) $(STARGETS) $(CTARGETS) $(MAINSRCS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

$(HTARGETS): $(HOBJS)
	$(CC) $(CFLAGS) -o $(HTARGETS) $(HOBJS)

$(DTARGETS): $(DOBJS)
	$(CC) $(CFLAGS) -o $(DTARGETS) $(DOBJS)

$(STARGETS): $(SOBJS)
	$(CC) $(CFLAGS) -o $(STARGETS) $(SOBJS)

$(CTARGETS): $(COBJS)
	$(CC) $(CFLAGS) -o $(CTARGETS) $(COBJS)
clean:
	rm -f $(OBJS) $(TARGETS) $(HOBJS) $(HTARGETS) $(DTARGETS) $(STARGETS) $(CTARGETS)

tags: $(SRCS) $(HEADERS)
	ctags $^

.PHONY: all clean tags 
