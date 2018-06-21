CLI_NAME = packtoring
DAEMON_NAME = daemon
CC = gcc
FLAGS = -Wall -Wextra 
#-Werror

DAEMONDIR = ./src/daemon/

CLIDIR = ./src/cli/

CLIFILES = main.c validation.c show_info.c deletion.c

DAEMONFILES = main.c initing_daemon.c read_write_files.c log_file.c sniff.c utils.c ft_itoa.c pid_file.c

INCLUDE = includes
HEADER_RELATION = includes/header.h

BINDIR_DAEMON = ./objDaemon/
BIN_DAEMON = $(addprefix $(BINDIR_DAEMON), $(DAEMONFILES:.c=.o))

DAEMONFILES_FORCLI = $(BINDIR_DAEMON)initing_daemon.o $(BINDIR_DAEMON)read_write_files.o $(BINDIR_DAEMON)log_file.o $(BINDIR_DAEMON)sniff.o $(BINDIR_DAEMON)utils.o $(BINDIR_DAEMON)ft_itoa.o $(BINDIR_DAEMON)pid_file.c

BINDIR_CLI = ./objCli/
BIN_CLI = $(addprefix $(BINDIR_CLI), $(CLIFILES:.c=.o)) $(DAEMONFILES_FORCLI)

all: $(DAEMON_NAME) $(CLI_NAME)

$(CLI_NAME): $(BINDIR_CLI) $(BIN_CLI) 
	$(CC) $(FLAGS) -lpcap -o $(CLI_NAME) $(BIN_CLI) -I $(INCLUDE)

$(BINDIR_CLI):
	@if [ ! -d "$(BINDIR_CLI)" ]; then mkdir $(BINDIR_CLI); fi

$(BINDIR_CLI)%.o: $(CLIDIR)%.c $(HEADER_RELATION)
	$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE)


$(DAEMON_NAME): $(BINDIR_DAEMON) $(BIN_DAEMON)
	$(CC) $(FLAGS) -lpcap -o $(DAEMON_NAME) $(BIN_DAEMON) -I $(INCLUDE)

$(BINDIR_DAEMON):
	@if [ ! -d "$(BINDIR_DAEMON)" ]; then mkdir $(BINDIR_DAEMON); fi

$(BINDIR_DAEMON)%.o: $(DAEMONDIR)%.c $(HEADER_RELATION)
	$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE)

clean:
	@if [ -d "$(BINDIR_DAEMON)" ]; then rm -rf $(BINDIR_DAEMON); fi
	@if [ -d "$(BINDIR_CLI)" ]; then rm -rf $(BINDIR_CLI); fi
	@echo "\033[32;1mCleaned\033[0m"

fclean: clean
	@if [ -f "$(NAME)" ]; then rm -rf $(NAME); fi

re: fclean all
