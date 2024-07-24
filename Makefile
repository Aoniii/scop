-include ./configuration/Sources.mk
-include ./configuration/Includes.mk

NAME		=	scop
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDES_DIR) -I$(INCLUDES_DIR)/objects
LDFLAGS		=	-lGL -lGLU -lglut -lGLEW -lglfw
OBJS		=	$(SRCS:.cpp=.o)
OBJS_DIR	=	objects
OBJS_PATH	=	$(addprefix $(OBJS_DIR)/, $(OBJS))

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)
	@printf "\033[2K\r\033[3;35m$<: \033[3;36mloading..\033[0m"

$(NAME): $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(OBJS_PATH) -o $(NAME) $(LDFLAGS)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;32mCompiled [√]\033[0m\n"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf parsingChecker
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;31mObject Delete \033[1;32m[√]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;31m$(NAME) Delete \033[1;32m[√]\033[0m\n"

re: fclean all

.PHONY: all clean fclean re