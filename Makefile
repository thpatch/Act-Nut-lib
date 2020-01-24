ifneq ($(OS), Windows_NT)
NAME		=	libactnut.so
NAME_64		=	libactnut64.so
BIN_NAME	=	print-act-nut
BIN_NAME_64	=	print-act-nut-64
else
NAME		=	libactnut.dll
NAME_64		=	libactnut64.dll
BIN_NAME	=	print-act-nut.exe
BIN_NAME_64	=	print-act-nut-64.exe
endif

SHARED		=	1
ifeq ($(SHARED), 1)
LDFLAGS		=	-shared
BIN_LDFLAGS	+=	-Wl,-rpath=.
else
NAME		=	libactnut.a
NAME_64		=	libactnut64.a
BIN_LDFLAGS	+=	-static
endif

CXXFLAGS	+=	-Wall -Wextra -Wno-multichar -g -I. -fPIC
CXXFLAGS_64	+=	-DSQ_INT64=1

SRCS		=	Object.cpp \
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

BIN_SRCS	=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)
OBJS_64		=	$(SRCS:.cpp=.64.o)
BIN_OBJS	=	$(BIN_SRCS:.cpp=.o)
BIN_OBJS_64	=	$(BIN_SRCS:.cpp=.64.o)

# This rule should be identical to the default one, but I want to make sure
# it's almost identical to the %.64.o one.
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS)	-c -o $@ $< 

%.64.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -DSQ_INT64=1	-c -o $@ $< 

all: $(NAME) $(BIN_NAME) $(BIN_NAME_64)

$(NAME): $(OBJS)
ifeq ($(SHARED), 1)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
else
	ar rc $(NAME) $(OBJS)
endif

$(NAME_64): $(OBJS_64)
ifeq ($(SHARED), 1)
	$(CXX) $(OBJS_64) -o $(NAME_64) $(LDFLAGS)
else
	ar rc $(NAME_64) $(OBJS_64)
endif

$(BIN_NAME): $(NAME) $(BIN_OBJS)
	$(CXX) $(BIN_OBJS)    -o $(BIN_NAME)    $(BIN_LDFLAGS) -L. -lactnut

$(BIN_NAME_64): $(NAME_64) $(BIN_OBJS_64)
	$(CXX) $(BIN_OBJS_64) -o $(BIN_NAME_64) $(BIN_LDFLAGS) -L. -lactnut64

clean:
	rm -f $(OBJS)    $(BIN_OBJS)    $(NAME)    $(BIN_NAME)
	rm -f $(OBJS_64) $(BIN_OBJS_64) $(NAME_64) $(BIN_NAME_64)

re: clean all
