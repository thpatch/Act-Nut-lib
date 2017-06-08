NAME	=	a.out

CXXFLAGS =	-Wall -Wextra -Wno-multichar -g -I..

SRCS	=	main.cpp \
		SQObject.cpp \
		SQComplexObjects.cpp \
		SQInstruction.cpp \
		SQFunctionProto.cpp \
		../Utils.cpp

OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(NAME)

re: clean all
