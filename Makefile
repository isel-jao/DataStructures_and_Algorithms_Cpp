
NAME	= ft.lib

CCPP	= clang++ -I ./include/
CFLAGS 	= -Wall -Werror -Wextra

AR = ar rcs

INC_DIR	= ./include/
SRC_DIR	= ./src/
OBJ_DIR	= ./obj/


INC		= -i ${INC_DIR}

SRC		+= utils.cpp

OBJ		=	$(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))


$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INC_DIR)*.hpp
	@$(CCPP) $(CFLAGS) -c $< -o $@

all:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJ)
	@$(AR) $(NAME) $?

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) a.out

re: fclean all

test: all main.cpp
	@clear
	@$(CCPP) main.cpp   $(NAME)  \
	&& echo "---------------- main --------------" \
	&& ./a.out \
	&& echo '---------------- end ---------------'
# test:  main.cpp ${INC_DIR}*.hpp
# 	@$(CCPP) main.cpp -I $(INC_DIR)  \
# 	&& clear \
# 	&& echo "---------------- main --------------" \
# 	&& ./a.out \
# 	&& echo '---------------- end ---------------'