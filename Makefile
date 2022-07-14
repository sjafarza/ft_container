NAME		=	test

VPATH		=	src
OBJDIR		=	obj
INCLDIR		=	inc 

SRC 		=	main.cpp

OBJ 		=  	$(SRC:%.cpp=$(OBJDIR)/%.o)

CC			=	c++
CFLAG		=	-Wall -Wextra -Werror -std=c++98
HEADER			=	-I.
INCFLAGS	=	./containers/vector.hpp header_utils.hpp

RM			=	rm -rf
UNAME           :=      $(shell uname -s)

all:			$(NAME)
$(OBJDIR)/%.o:	%.cpp $(INCFLAGS) | $(OBJDIR)
					@c++ $(HEADER) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				@echo "\033[032m\n\nCompiling canon... "
				@c++ $(CFLAGS) -o $@ $^ $(LFLAGS)
				@echo "\n\033[0mDone !"

$(OBJDIR):
				@echo "\033[0;33mGenerating bin folder "
				mkdir $(OBJDIR)


clean:
				@echo "\033[0;31m\nDeleting objects ..."
				@rm -rf $(OBJ)
				@echo "\033[0m"

fclean:			clean
				@rm -rf $(NAME) $(OBJDIR)
				@echo "\033[0;31m\nDone !"

re:				fclean all

.PHONY:			all clean fclean re
