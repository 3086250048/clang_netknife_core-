ALL:test

test:test.c 
		gcc $< -L ./lib -lnetknife -I ./lib -o $@

