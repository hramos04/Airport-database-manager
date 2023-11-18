# COMPILER

CC := gcc
LIBS := 
CFLAGS := -Wall -Wextra -pedantic-errors -O2 -Iinclude

# OBJECT CODE

OBJS_UTILS := $(patsubst %.c, %.o, $(wildcard src/*.c))
OBJS_TESTS := $(patsubst %.c, %.o, $(wildcard src/tests/*.c))
#OBJS_FETCH := $(patsubst %.c, %.o, $(wildcard src/fetch/*.c))
OBJS_PARSER := $(patsubst %.c, %.o, $(wildcard src/parsing/*.c))
#OBJS_QUERIES := $(patsubst %.c, %.o, $(wildcard src/queries/*.c))
OBJS_CATALOGS := $(patsubst %.c, %.o, $(wildcard src/user/*.c))
#OBJS_INTERACTIVE := $(patsubst %.c, %.o, $(wildcard src/interactive/*.c))
OBJS_ALL := $(OBJS_UTILS) $(OBJS_TESTS) $(OBJS_FETCH) $(OBJS_PARSER) $(OBJS_QUERIES) $(OBJS_CATALOGS) $(OBJS_INTERACTIVE)

# TARGETS

TARGET := programa-principal
TARGET_TESTS := programa-testes

# Folders

PATH_RESULTS := Resultados
CSV_LARGE := csv/data-large
CSV_REGULAR := csv/data-regular
CSV_REGULAR_ERRORS := csv/data-regular-errors


# BUILDING

all: $(TARGET) $(TARGET_TESTS)
	@mkdir -p $(PATH_RESULTS)


# LINKING

$(TARGET): $(filter-out src/tests/main.o, $(OBJS_ALL))
	$(CC) -o $@ $^ $(LIBS)


$(TARGET_TESTS): $(filter-out src/main.o, $(OBJS_ALL))
	$(CC) -o $@ $^ $(LIBS)


# COMPILING

$(OBJS_UTILS): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJS_TESTS): src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJS_PARSER): src/src/parsing/%.o : src/src/parsing/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJS_CATALOGS): src/src/Catalog/%.o : src/src/Catalog/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 																	\
$(OBJS_FETCH): src/fetch/%.o : src/fetch/%.c						\
	$(CC) $(CFLAGS) -c $< -o $@										\
																	\
																	\
$(OBJS_QUERIES): src/queries/%.o : src/queries/%.c					\
	$(CC) $(CFLAGS) -c $< -o $@										\
																	\
																	\
$(OBJS_INTERACTIVE): src/interactive/%.o : src/interactive/%.c		\
	$(CC) $(CFLAGS) -c $< -o $@										\

# TESTS

test_1:
	./$(TARGET_TESTS) $(CSV_REGULAR) inputs/input.txt exemplos_de_queries/tests_1


test_2:
	./$(TARGET_TESTS) $(CSV_REGULAR) inputs/input2.txt exemplos_de_queries/tests_2


test_3:
	./$(TARGET_TESTS) $(CSV_REGULAR_ERRORS) inputs/input3.txt exemplos_de_queries/tests_3


test_4:
	./$(TARGET_TESTS) $(CSV_LARGE) inputs/input4.txt exemplos_de_queries/tests_4


# REMOVE FILES

clean:
	rm $(OBJS_ALL)
	rm $(TARGET)
	rm $(TARGET_TESTS)
	rm -r $(PATH_RESULTS)/
