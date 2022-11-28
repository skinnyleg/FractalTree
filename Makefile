CC = cc

CFILES = main.c\

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

INC = includes/FractalTree.h

LFLAGS = -lmlx -framework OpenGL  -Ofast  -framework AppKit

INCMLX=/usr/include

INCLIB=$(INCMLX)/../lib

HFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

NAME = FractalTree

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OFILES)
	@$(CC) $(LFLAGS) $(OFILES) -o $(NAME)
	@echo "done for FractalTree"

debug : $(OBJ_DIR) $(OFILES)
	@$(CC) -fsanitize=address $(LFLAGS) $(OFILES) -o $(NAME)
	@echo "done for FractalTree (debug mode)"

pc : $(OBJ_DIR) $(OFILES)
	@$(CC) $(OFILES) $(HFLAGS) -o $(NAME)
	@echo "done for FractalTree"

$(OBJ_DIR) :
	@mkdir obj

$(OFILES) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	@$(CC) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
