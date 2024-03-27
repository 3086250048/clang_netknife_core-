src = $(wildcard *.c)

dst = $(patsubst %.c,%,$(src))

ALL:$(dst)

%:%.c
	gcc  $<  -I ../lib -L ../lib -l netknife -o $@ -g 


