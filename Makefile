# Source files
MAIN	=	src/main.cpp\

SRCS	=	src/Core/Gameboy.cpp\
			src/Components/Screen/Screen.cpp\
			src/Components/MMU/MMU.cpp\
			src/Components/CPU/CPU.cpp\
			src/Components/CPU/CPUInstructions.cpp\
			src/Components/CPU/Cycles.cpp

SRC	= $(MAIN) $(SRCS)

OBJ_DEBUG	=	$(SRC:%.cpp=./obj/debug/%.o)
OBJ_RELEASE	=	$(SRC:%.cpp=./obj/release/%.o)

# Compilation parameters
COMPILER	=	g++
LINKER	=	g++
LINKER_COMMON_FLAGS	=	-lraylib
COMPILER_COMMON_FLAGS	=	-std=c++23 -I./src
COMPILER_FLAGS_DEBUG	=	$(COMPILER_COMMON_FLAGS) -g -Wall -Wextra -D_DEV_MODE
COMPILER_FLAGS_RELEASE	=	$(COMPILER_COMMON_FLAGS) -O3 -march=native -flto=auto
LINKER_FLAGS_DEBUG	=	$(LINKER_COMMON_FLAGS) -g
LINKER_FLAGS_RELEASE	=	$(LINKER_COMMON_FLAGS) -O3 -march=native -flto=auto
MAKEFLAGS	+=	-j$(shell nproc) --silent --no-print-directory

N_FILES	:=	$(words $(SRC))
CURRENT_FILE	:=	0
NAME	= gameboy

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
RESET=\033[0m

# Main rule
all:	$(NAME)

# Compilation of the main binary
$(NAME):
	@echo -ne "[$(YELLOW)$(NAME)$(RESET)] "
	@echo -ne "Compiling all objects files...\n"
	@echo ""
	@make $(OBJ_RELEASE)
	@echo -ne "\n"
	@echo ""
	@echo -ne "--------------------------------------------\n"
	@echo ""
	@echo -ne "[$(YELLOW)$(NAME)$(RESET)] "
	@echo -ne "Compiling main program...\n"
	@$(LINKER) -o $(NAME) $(OBJ_RELEASE) $(LINKER_FLAGS_RELEASE)
	@echo ""
	@echo -ne "[$(YELLOW)$(NAME)$(RESET)] "
	@echo -ne "Main program successfully compiled in release mode!\n"

# Debug rule
dev:
	@make fclean
	@echo -ne "[$(YELLOW)$(NAME)$(RESET)] "
	@echo -ne "Compiling all objects files...\n"
	@echo ""
	@make $(OBJ_DEBUG)
	@echo -ne "\n"
	@echo ""
	@echo -ne "--------------------------------------------\n"
	@echo ""
	@echo -ne "[$(YELLOW)$(NAME)$(RESET)] "
	@echo -ne "Compiling main program...\n"
	@$(LINKER) -o $(NAME) $(OBJ_DEBUG) $(LINKER_FLAGS_DEBUG)
	@echo ""
	@echo -ne "[$(YELLOW)$(NAME)$(RESET)] "
	@echo -ne "Main program successfully compiled in debug mode!\n"

# Rule to compile objects files in debug mode
$(OBJ_RELEASE): ./obj/release/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo -ne "\033[2K\r"
	@echo -ne "[$(BLUE)COMPILATION$(RESET)] "
	@echo -ne "($(shell expr $(CURRENT_FILE) + 1)/$(N_FILES)) $@"
	@$(COMPILER) -c $< -o $@ $(COMPILER_FLAGS_RELEASE)
	@$(eval CURRENT_FILE := $(shell expr $(CURRENT_FILE) + 1))

# Rule to compile objects files in debug mode
$(OBJ_DEBUG): ./obj/debug/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo -ne "\033[2K\r"
	@echo -ne "[$(BLUE)COMPILATION$(RESET)] "
	@echo -ne "($(shell expr $(CURRENT_FILE) + 1)/$(N_FILES)) $@"
	@$(COMPILER) -c $< -o $@ $(COMPILER_FLAGS_DEBUG)
	@$(eval CURRENT_FILE := $(shell expr $(CURRENT_FILE) + 1))

# Rule to remove all object files
clean:
	@echo -ne "[$(RED)REMOVE$(RESET)] "
	@echo -ne "Removing all object files...\n"
	@rm -f $(OBJ_DEBUG)
	@rm -f $(OBJ_RELEASE)
	@echo -ne "[$(RED)REMOVE$(RESET)] "
	@echo -ne "Removing all unit tests files...\n"
	@rm -f *.gcno
	@rm -f *.gcda
	@echo -ne "[$(RED)REMOVE$(RESET)] "
	@echo -ne "All objects files successfully removed!\n"

# Rule to remove all binary files
fclean:
	@make clean
	@echo -ne "[$(RED)REMOVE$(RESET)] "
	@echo -ne "Removing main binary...\n"
	@rm -f $(NAME)
	@rm -f unit_tests
	@echo -ne "[$(RED)REMOVE$(RESET)] "
	@echo -ne "Main binary successfully removed!\n"
	@echo ""
	@echo -ne "[$(RED)REMOVE$(RESET)] "
	@echo -ne "Repository successfully cleaned!\n"

# Rule to fully recompile the prgram
re:
	@make fclean
	@echo ""
	@echo -ne "--------------------------------------------\n"
	@echo ""
	@echo -ne "[$(YELLOW)$(NAME)$(RESET)] "
	@echo -ne "Recompiling the program\n"
	@echo ""
	@echo -ne "--------------------------------------------\n"
	@echo ""
	@make

.PHONY: all dev clean fclean re
