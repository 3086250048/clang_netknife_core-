ALL:netknife 

netknife: netknife.l netknife.y ./lib/netknife.h
		bison -d netknife.y
		flex -o netknife.lex.c netknife.l
		gcc -o $@ netknife.c netknife.tab.c netknife.lex.c -I ./lib -L ./lib -lnetknife

