CC=gcc -g
CFLAGS = -c -Wall -Werror -Wextra -std=c11
SOURCES_GREP = .
SRC_GREP := $(wildcard $(SOURCES_GREP)/*.c)
OBJS_GREP := $(SRC_GREP:$(SOURCES_GREP)/%.c=%.o)

all: s21_grep

$(OBJS_GREP): %.o : $(SOURCES_GREP)/%.c
	$(CC) $(CFLAGS) -c $< -o $(SOURCES_GREP)/$@


s21_grep: $(OBJS_GREP)
	$(CC) $(SOURCES_GREP)/*.o -o $(SOURCES_GREP)/s21_grep

clean:
	@rm -rf $(SOURCES_GREP)/*.o
	@rm -rf $(SOURCES_GREP)/s21_grep


