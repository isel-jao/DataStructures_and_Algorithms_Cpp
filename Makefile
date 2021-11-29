
NAME	= lib

CCPP	= clang++
CFLAGS 	= -Wall -Werror -Wextra

INC_DIR	= ./include/
SRC_DIR	= ./src/
OBJ_DIR	= ./obj/


INC		= -i ${INC_DIR}

SRC		+= 

OBJ		=	$(addprefix $(OBJ_DIR),$(SRC:.c=.o))

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INC_DIR)*.h
	$(CCPP) $(CFLAGS) -c $< -o $@

all:
	mkdir -p $(OBJ_DIR)
	$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJ)
	$(AR) $(NAME) $?

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# test: all main.cpp
# 	@$(CCPP) main.c -I $(INC_DIR)  $(NAME)  \
# 	&& clear \
# 	&& echo "---------------- main --------------" \
# 	&& ./a.out \
# 	&& echo '---------------- end ---------------'
test:  main.cpp ${INC_DIR}*.hpp
	@$(CCPP) main.cpp -I $(INC_DIR)  \
	&& clear \
	&& echo "---------------- main --------------" \
	&& ./a.out \
	&& echo '---------------- end ---------------'