NAME	=	a.out

CXXFLAGS =	-Wall -Wextra -Wno-multichar -g -I.

SRCS	=	main.cpp \
		Object.cpp \
		Utils.cpp \
		act/Object.cpp \
		act/File.cpp \
		act/Entry.cpp \
		act/Entries.cpp \
		nut/SQObject.cpp \
		nut/SQComplexObjects.cpp \
		nut/SQInstruction.cpp \
		nut/SQFunctionProto.cpp \
		nut/Stream.cpp

OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(NAME)

re: clean all
