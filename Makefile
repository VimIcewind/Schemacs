





install: emacs.c
	gcc -fPIC -shared emacs.c -o emacs.so
