NAME =		libftprintf.a
SRCS =		ft_printf.c
OBJS =		$(SRCS:.c=.o)
LIBFT_DIR =		../libft
LIBFT = 		$(LIBFT_DIR)/libft.a
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror -I ../headers -L $(LIBFT)
AR =			ar rcs

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			@$(AR) $(NAME) $(OBJS) $(LIBFT_DIR)/*.o

$(LIBFT):
			@make -C $(LIBFT_DIR)

%.o:		%.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJS)
			@make clean -C $(LIBFT_DIR)

fclean:		clean
			@rm -f $(NAME)
			@make fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re