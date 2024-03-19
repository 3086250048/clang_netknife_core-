src = $(wildcard *.c)

dst = $(patsubst %.c,%,$(src))

ALL:$(dst)

%:%.c 
		gcc $< -L ../lib -lnetknife -I ../lib -o $@

