.PHONY: all clean

# The program to build
NAME	:= multicam
LIBPATH	:= /usr/lib/x86_64-linux-gnu

# Build tools and flags
LD			:= $(CXX)
LDFLAGS		:= $(shell $(LIBPATH) --libs-rpath)
LIBS		:= $(shell pkg-config opencv --cflags --libs) -lboost_system -lboost_thread
	
# this target will compile all the file
all: $(NAME)

$(NAME): $(NAME).o
		g++ -o $(NAME) $(NAME).o $(LDFLAGS) $(LIBS)

$(NAME).o: $(NAME).cpp
	g++ -c -o $@ $<

clean:
		$(RM) $(NAME).o $(NAME)
