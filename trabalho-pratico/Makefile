# COMPILER

CC := gcc
LIBS := -ltermcap
CFLAGS := -Wall -Wextra -pedantic-errors -O2 -Iinclude

# OBJECT CODE

OBJS_UTILS := $(patsubst %.c, %.o, $(wildcard src/*.c))
OBJS_PARSER := $(patsubst %.c, %.o, $(wildcard src/parsing/*.c))
OBJS_QUERIES := $(patsubst %.c, %.o, $(wildcard src/queries/*.c))

OBJS_ALL := $(OBJS_UTILS) $(OBJS_PARSER) $(OBJS_QUERIES)

# TARGETS

TARGET := programa-principal


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


$(OBJS_PARSER): src/src/parsing/%.o : src/src/parsing/%.c
	$(CC) $(CFLAGS) -c $< -o $@



test_1:
	./$(TARGET_TESTS) $(CSV_REGULAR) inputs/input.txt exemplos_de_queries/tests_1


test_2:
	./$(TARGET_TESTS) $(CSV_REGULAR) inputs/input2.txt exemplos_de_queries/tests_2



# REMOVE FILES

clean:
	rm $(OBJS_ALL)
	rm $(TARGET)
	rm $(TARGET_TESTS)
	rm -r $(PATH_RESULTS)/

