src = $(wildcard *.c)

dst1 = $(patsubst %.c,%.o,$(src))

ALL:libnetknife.a

libnetknife.a:${dst1}
		ar rcs  $@ $^  
%.o:%.c
	gcc -c $< -o $@ -DOUTSTEP -g


