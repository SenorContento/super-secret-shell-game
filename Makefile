ifndef prefix
	prefix=.
endif

# https://stackoverflow.com/a/4590779/6828099
export ROOT=$(realpath $(dir $(lastword $(MAKEFILE_LIST))))

make:
	gcc ${ROOT}/src/shell.c -lreadline -DREADLINE_LIBRARY -o ${prefix}/shell

noreadline:
	gcc ${ROOT}/src/shell.c -o ${prefix}/shell