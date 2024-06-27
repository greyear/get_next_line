CFILES = get_next_line.c get_next_line_utils.c
CBONUS = get_next_line_bonus.c get_next_line_utils_bonus.c
OFILES = $(CFILES:.c=.o)
OBONUS = $(CBONUS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = get_next_line.a

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
all: $(NAME)
$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)
clean:
	rm -f $(OFILES) $(OBONUS) .bonus
fclean: clean 
	rm -f $(NAME)
re: fclean all
bonus: .bonus
.bonus: $(OFILES) $(OBONUS)
	ar rcs $(NAME) $(OFILES) $(OBONUS)
	@touch .bonus
.PHONY: all clean fclean re bonus
