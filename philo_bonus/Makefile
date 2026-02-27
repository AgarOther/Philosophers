# Compilation
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror

# Names
NAME				=	philo_bonus

# Sources & Includes
SRCS				=	srcs_bonus/main_bonus.c \
						srcs_bonus/free_bonus.c \
						srcs_bonus/ft_safe_atoi_bonus.c \
						srcs_bonus/parsing_bonus.c \
						srcs_bonus/utils_bonus.c \
						srcs_bonus/routine_bonus.c
OBJ_FOLDER			=	objs
INCLUDES			=	-I includes_bonus

# Objects
OBJS				=	$(patsubst %.c, $(OBJ_FOLDER)/%.o, $(SRCS))

# Custom Makefile Flags
MAKEFLAGS			+=	--no-print-directory --silent

# Custom Colors
PURPLE				=	\033[1;35m
LIGHT_GREEN			=	\033[1;32m
RESET				=	\033[0m

# Custom messages
EXE_DONE			=	@echo "🎉$(PURPLE) $(NAME) compiled! 🎉$(RESET)\n"
ALL_CLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all : $(NAME)

bonus : all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(EXE_DONE)

$(OBJ_FOLDER)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

re : fclean all

.PHONY: all clean fclean re
