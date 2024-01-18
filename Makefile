define HEADER

                                ..                                
                              ...                                 
                      ..........................                  
                   ................................               
                     .................................            
                   .....................................          
                  ........................................        
                .............................................     
               ................................................   
              ...............................................     
              ................................................    
              ................................................    
              .................................................   
              ....................................-............   
              ...................--...............+#...........   
              ...................##...............###...........  
             ...................+###.............+###+..........  
                ...............+#####...........-+####-....... .. 
                 ..+##........+##+++--...............-#.......    
                  .####......+#-....--#-......+-.....+#-......    
 ...---           .+####+.....#-.......#+..#.##-++-+-###.....     
 .++++-..+-.........+######...##-+++++-#########..-+####.. .      
 -+++++++..............-++####+#########################-                           _
.+++++++.....................-##############+####+-..-+++-                         | |            __
.++++++-.........................-++#########+-+-++++++++.        _______ __ __  __| | ____      |__| ____   ______
.++++++-...............................++.....-+++++++++-         \_  __ \  |  \/ __ |/ __ \_____|  |/ __ \ /  ___/ 
 .+++++-......................................++++++++++.          |  | \/  |  / /_/ \  ___/_____/  \  ___/ \___ \  
    .-++.....................................++++++++++.           |__|  |____/\____ |\___  >/\__|  |\___  >____  > 
         ..................................#-+++++++++-                             \/    \/ \______|    \/     \/          

=======================================================================================================================
endef
export HEADER

define LIB_HEADER
 

                             __ __ __                  __ __ __                     __              
 .----.-----.--------.-----.|__|  |__|.-----.-----.   |  |__|  |--.----.---.-.----.|__|.-----.-----.
 |  __|  _  |        |  _  ||  |  |  ||     |  _  |   |  |  |  _  |   _|  _  |   _||  ||  -__|__ --|
 |____|_____|__|__|__|   __||__|__|__||__|__|___  |   |__|__|_____|__| |___._|__|  |__||_____|_____|
                     |__|                   |_____|                                                 

endef
export LIB_HEADER

define APP_HEADER

                             __ __ __                                   __                    
 .----.-----.--------.-----.|__|  |__|.-----.-----.   .-----.-----.    |  |.-----.-----.-----.
 |  __|  _  |        |  _  ||  |  |  ||     |  _  |   |__ --|  _  |    |  ||  _  |     |  _  |
 |____|_____|__|__|__|   __||__|__|__||__|__|___  |   |_____|_____|____|__||_____|__|__|___  |
                     |__|                   |_____|              |______|              |_____|
                                                                                                                                                                                                                                                                                                   
endef
export APP_HEADER

define BONUS_HEADER


                             __ __ __                   __                            
 .----.-----.--------.-----.|__|  |__|.-----.-----.    |  |--.-----.-----.--.--.-----.
 |  __|  _  |        |  _  ||  |  |  ||     |  _  |    |  _  |  _  |     |  |  |__ --|
 |____|_____|__|__|__|   __||__|__|__||__|__|___  |    |_____|_____|__|__|_____|_____|
                     |__|                   |_____|                                   

endef
export BONUS_HEADER

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OS =

MINILIBX_MACOS_PATH = libs/minilibx_opengl/
MINILIBX_LINUX_PATH = libs/minilibx-linux/
MINILIBX_LIB = libmlx.a
MINILIBX_PATH =

UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CFLAGS += -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MINILIBX_PATH = $(MINILIBX_LINUX_PATH)
	OS = linux
endif

ifeq ($(UNAME_S),Darwin)
	CFLAGS += -framework OpenGL -framework AppKit
	MINILIBX_PATH = $(MINILIBX_MACOS_PATH)
	OS = macos
endif

MINILIBX_LIB := $(MINILIBX_PATH:%=%$(MINILIBX_LIB))

BETTERFT_PATH = libs/betterft/
BETTERFT_LIB = $(BETTERFT_PATH:%=%betterft.a)

SRC = 	so_long \
		utils/entities \
		utils/entity_builder \
		utils/exit_handler_$(OS) \
		utils/game_renderer \
		utils/map_checker \
		utils/map_parser \
		utils/path_checker \


CFILES = $(SRC:%=src/%.c)

BONUS_SRC =	so_long_bonus \


BONUS_CFILES = $(BONUS_SRC:%=src/%.c)

NAME = so_long
BONUS_NAME = so_long_bonus

all: $(NAME)

debug: fclean $(CFILES) $(BETTERFT_LIB) $(MINILIBX_LIB)
	@echo "$$APP_HEADER"
	@printf "\t🤖 Compiling $(NAME)...\r"
	@$(CC) -g3 -fsanitize=address $(CFILES) $(BETTERFT_LIB) $(MINILIBX_LIB) $(CFLAGS) -o $(NAME)
	@printf "\33[2K"
	@echo "\t[INFO]\t[$(NAME)]\t$(NAME) is compiled ✅"
	@echo "\nThe programm was compiled with debug sanitizer set to address\nDo not forget to use \"leak -atExit -- $(NAME)\" in order to check for potential leaks.\nNote that it won't work with the debug version.\n\nFor better debug, you can use \"lldb $(name) <args>\" after using debug rule.\n\n"
	@echo $(shell norminette)

clean: $(BETTERFT_PATH)Makefile $(MINILIBX_PATH)Makefile
	@$(MAKE) -C $(BETTERFT_PATH) fclean --no-print-directory
	@$(MAKE) -C $(MINILIBX_PATH) clean --no-print-directory 1>/dev/null
	@echo "\t[INFO]\t[$(MINILIBX_LIB)]\t$(MINILIBX_LIB) is fully deleted 🗑️"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@echo "\t[INFO]\t[$(NAME)]\t$(NAME) is fully deleted 🗑️"
	@echo "\t[INFO]\t[$(NAME)]\t$(BONUS_NAME) is fully deleted 🗑️"

re: fclean all

bonus: $(BONUS_NAME)

help:
	@echo "$$HEADER"
	@echo "all		-	Build $(NAME)"
	@echo "bonus		-	Build $(BONUS_NAME)"
	@echo "clean		-	Clean temporary files"
	@echo "fclean		-	Clean the whole build"
	@echo "debug		-	Runs the program with g3 fsanitize=address"
	@echo "$(NAME)	-	Build the $(NAME) with necessary libs"
	@echo "$(BONUS_NAME)		-	Build the $(BONUS_NAME) with necessary libs"
	@echo "$(BETTERFT_LIB)	-	Build the lib $(BETTERFT_LIB)"

$(CFILES): header

$(BONUS_CFILES): header

%.o: %.c
	@printf "\t🤖 Compiling $<...\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\33[2K"

$(NAME): $(CFILES) $(BETTERFT_LIB) $(MINILIBX_LIB)
	@echo "$$APP_HEADER"
	@printf "\t🤖 Compiling $(NAME)...\r"
	@$(CC) $(CFILES) $(BETTERFT_LIB) $(MINILIBX_LIB) $(CFLAGS) -o $(NAME)
	@printf "\33[2K"
	@echo "\t[INFO]\t[$(NAME)]\t$(NAME) is compiled ✅\n"

$(BETTERFT_LIB): $(BETTERFT_PATH)Makefile
	@echo "$$LIB_HEADER"
	@make -C $(BETTERFT_PATH) all --no-print-directory

$(MINILIBX_LIB): $(MINILIBX_PATH)Makefile
	@echo "$$LIB_HEADER"
	@echo "\t🤖 Compiling $(MINILIBX_LIB)..."
	@make -C $(MINILIBX_PATH) all --no-print-directory 1>/dev/null
	@echo "\t[INFO]\t[$(MINILIBX_LIB)]\t$(MINILIBX_LIB) is compiled ✅\n"

$(BONUS_NAME): $(BONUS_CFILES) $(BETTERFT_LIB)
	@echo "$$BONUS_HEADER"
	@printf "\t🤖 Compiling $(BONUS_NAME) 🌟...\r"
	@$(CC) $(CFLAGS) $(BONUS_CFILES) $(BETTERFT_LIB) -o $(NAME)
	@printf "\33[2K"
	@echo "\t[INFO]\t[$(BONUS_NAME)]\t$(NAME) ($(BONUS_NAME)) 🌟 is compiled ✅\n"

header:
	@echo "$$HEADER"

.PHONY = all clean fclean re bonus header help
