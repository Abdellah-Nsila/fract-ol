NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
INCLUDES = -I./includes -I./Libft/includes
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	$(SRC_DIR)/fractol.c $(SRC_DIR)/fractol_struct.c $(SRC_DIR)/fractol_events.c \
		$(SRC_DIR)/fractol_plan.c $(SRC_DIR)/fractol_utils.c $(SRC_DIR)/fractol_sq_equations.c \
		$(SRC_DIR)/fractol_parsing.c $(SRC_DIR)/fractol_cub_equations.c \
	
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c ./includes/fractol.h ./includes/settings.h ./includes/structs.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
