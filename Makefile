CC := /usr/bin/gcc
IDir := ./include/
SDir := ./src/
BDir := ./.build/

all: create_dir First

First:
	@$(CC) -o $(BDir)exe $(SDir)*

create_dir:
	@./create_dir.sh

clean:
	@rm -rf .build
