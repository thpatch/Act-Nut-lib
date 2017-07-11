NAME	=	libactnut.so
BIN_NAME=	print-act-nut

CXXFLAGS=	-Wall -Wextra -Wno-multichar -g -I. -fPIC

SRCS	=	Object.cpp \
		Utils.cpp \
		exports.cpp \
		act/Object.cpp \
		act/File.cpp \
		act/Entry.cpp \
		act/Entries.cpp \
		nut/SQObject.cpp \
		nut/SQComplexObjects.cpp \
		nut/SQInstruction.cpp \
		nut/SQFunctionProto.cpp \
		nut/Stream.cpp

BIN_SRCS=	main.cpp

OBJS	=	$(SRCS:.cpp=.o)
BIN_OBJS=	$(BIN_SRCS:.cpp=.o)

all: $(NAME) $(BIN_NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS) -shared

$(BIN_NAME): $(NAME) $(BIN_OBJS)
	$(CXX) $(BIN_OBJS) -o $(BIN_NAME) $(LDFLAGS) -L. -lactnut -Wl,-rpath=.

clean:
	rm -f $(OBJS) $(BIN_OBJS) $(NAME) $(BIN_NAME)

re: clean all
