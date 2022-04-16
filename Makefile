NAME_CLIENT	:=	client
NAME_SERVEUR	:=	serveur

CC	:=	gcc
CSAN	:=	fsanitize=address -g3
CFLAGS	:=	-Wall -Wextra -Werror

DIR_SRCS	:=	sources
DIR_OBJS	:=	.objs
DIR_INCS	:=	includes

DIR_LIBFT	:=	libft_me

LST_SRCS_CLIENT	:=	client.c
LST_SRCS_SERVEUR	:=	serveur.c
LST_OBJS_CLIENT	:=	$(LST_SRCS_CLIENT:.c=.o)
LST_OBJS_SERVEUR	:=	$(LST_SRCS_SERVEUR:.c=.o)
LST_INCS	:=	minitalk.h

SRCS_CLIENT	:=		$(addprefix $(DIR_SRCS)/,$(LST_SRCS_CLIENT))
SRCS_SERVEUR	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS_SERVEUR))
OBJS_CLIENT	:=		$(addprefix $(DIR_OBJS)/,$(LST_OBJS_CLIENT))
OBJS_SERVEUR	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS_SERVEUR))
INCS	:=			$(addprefix $(DIR_INCS)/,$(LST_INCS))

AR_LIBFT	:=	$(DIR_LIBFT)/libft.a

all	:	$(NAME_CLIENT) $(NAME_SERVEUR)

$(NAME_CLIENT)	:	$(AR_LIBFT) $(OBJS_CLIENT)
					$(CC) $(CFLAGS) $^ -o $@

$(NAME_SERVEUR)	:	$(AR_LIBFT) $(OBJS_SERVEUR)
					$(CC) $(CFLAGS) $^ -o $@

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
					$(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@

$(AR_LIBFT)	:
				$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJS)	:
				mkdir -p $(DIR_OBJS)

clean	:
			rm -rf $(DIR_OBJS)

fclean	:	clean
			rm -rf $(NAME_CLIENT) $(NAME_SERVEUR)

re	:	fclean all

.PHONY	:	all clean fclean re 