FLAGS = -W -O3
CC = gcc
SRC_DIR = src
BUILD_DIR = build

PY_LEXER = $(SRC_DIR)/lexer.py
PY_PARSER = $(SRC_DIR)/parser.py
PY_MAIN = $(SRC_DIR)/main.py
PY_LEXER_BUILD = $(BUILD_DIR)/lexer.py
PY_PARSER_BUILD = $(BUILD_DIR)/parser.py
PY_MAIN_BUILD = $(BUILD_DIR)/main.py

.PHONY = all clean

all: $(BUILD_DIR)/calculator.exe python-build

$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

$(BUILD_DIR)/calculator.exe: $(SRC_DIR)/calculator.y $(SRC_DIR)/calculator.l | $(BUILD_DIR)
	bison -d -o $(BUILD_DIR)/calculator.tab.c $(SRC_DIR)/calculator.y
	flex -o$(BUILD_DIR)/lex.yy.c $(SRC_DIR)/calculator.l
	$(CC) $(FLAGS) -o $(BUILD_DIR)/calculator.exe $(BUILD_DIR)/calculator.tab.c $(BUILD_DIR)/lex.yy.c -lm

python-build:
	cp $(PY_LEXER) $(PY_LEXER_BUILD)
	cp $(PY_PARSER) $(PY_PARSER_BUILD)
	cp $(PY_MAIN) $(PY_MAIN_BUILD)

run-calculator:
	./$(BUILD_DIR)/calculator.exe

run-zad2: python-build
	python3 $(PY_MAIN_BUILD)

clean:
	rm -rf $(BUILD_DIR)/*.c $(BUILD_DIR)/*.h $(BUILD_DIR)/lexer.py $(BUILD_DIR)/parser.py $(BUILD_DIR)/parser.out $(BUILD_DIR)/parsetab.py $(BUILD_DIR)/__pycache__ $(BUILD_DIR)/calculator.exe $(BUILD_DIR)/main.py
	rm -rf $(BUILD_DIR)/__pycache__