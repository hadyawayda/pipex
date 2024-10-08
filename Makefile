NAME =			pipex
BONUS =			pipex_bonus
CC =			gcc
AR =			ar rcs
CFLAGS =		-g $(INCLUDES)
INCLUDES=		-I ./src/utils/headers -I /usr/include/c++/11 -I /usr/include/x86_64-linux-gnu/c++/11 -L /usr/lib/gcc/x86_64-linux-gnu/11
LIBFT_DIR =		src/utils/libft
LIBFT =			$(LIBFT_DIR)/libft.a
PRINTF_DIR =	src/utils/ft_printf
PRINTF =		$(PRINTF_DIR)/libftprintf.a

SRCS =			src/helpers/handlers.c \
				src/commands/execute.c \
				src/commands/find.c \

SRC =			src/main.c \

BONUS_SRC =		src/main_bonus.c \

OBJS =			$(SRCS:.c=.o) $(SRC:.c=.o)

BONUS_OBJ =		$(BONUS_SRC:.c=.o) $(SRCS:.c=.o)

all:			$(NAME)

bonus:			$(BONUS)

$(NAME):		$(OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

$(BONUS):		$(BONUS_OBJ) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(PRINTF) -o $(BONUS)

$(LIBFT):
				@make --no-print-directory -C $(LIBFT_DIR)

$(PRINTF):		$(LIBFT)
				@make --no-print-directory -C $(PRINTF_DIR)

%.o:			%.c
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@rm -f $(OBJS) $(BONUS_OBJ)
				@make --no-print-directory clean -C $(LIBFT_DIR)
				@make --no-print-directory clean -C $(PRINTF_DIR)

fclean:			clean
				@rm -f $(NAME) $(BONUS)
				@make --no-print-directory fclean -C $(LIBFT_DIR)
				@make --no-print-directory fclean -C $(PRINTF_DIR)

re:				fclean all