ifneq ($(OS), Windows_NT)
NAME	=	libactnut.so
BIN_NAME=	print-act-nut
else
NAME	=	libactnut.dll
BIN_NAME=	print-act-nut.exe
endif

SHARED = 1
ifeq ($(SHARED), 1)
LDFLAGS	=	-shared
BIN_LDFLAGS=	-Wl,-rpath=.
else
NAME	=	libactnut.a
BIN_LDFLAGS=	-static
endif

CXXFLAGS+=	-Wall -Wextra -Wno-multichar -g -I. -fPIC
BIN_LDFLAGS+=	-L. -lactnut

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
ifeq ($(SHARED), 1)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
else
	ar rc $(NAME) $(OBJS)
endif

$(BIN_NAME): $(NAME) $(BIN_OBJS)
	$(CXX) $(BIN_OBJS) -o $(BIN_NAME) $(BIN_LDFLAGS)

clean:
	rm -f $(OBJS) $(BIN_OBJS) $(NAME) $(BIN_NAME)

re: clean all
