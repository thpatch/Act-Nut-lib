NAME	=	a.out

CXXFLAGS =	-Wall -Wextra -Wno-multichar -g -Inut

SRCS	=	main.cpp \
		ActObject.cpp \
		ActEntry.cpp \
		nut/SQObject.cpp \
		nut/SQComplexObjects.cpp \
		nut/SQInstruction.cpp \
		nut/SQFunctionProto.cpp \
		Buffer.cpp \
		nut/utils.cpp

OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(NAME)

re: clean all
