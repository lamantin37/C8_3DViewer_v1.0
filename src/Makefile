CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard parser.c transformations.c)
HEADERS = $(wildcard auxiliary_modules.h)
TESTS = $(wildcard test_3dviewer.c)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})

_UNAME_ := $(shell uname -s)

ifeq ($(_UNAME_), Linux)
	OPEN_CMD = xdg-open
	ADD_LIB := -lm -lcheck -lsubunit
	BREW = .
	BROWSER_APP = firefox 
endif

ifeq ($(_UNAME_), Darwin) # MacOS
	OPEN_CMD = open
	ADD_LIB = -lm -lcheck 
	BREW = ${HOME}/homebrew
	BROWSER_APP = /Applications/Google\ Chrome.app
endif

PATH := $(PATH):$(BREW)/bin
GCOV = --coverage
PROJECT_NAME := s21_3DViewer

all: clean style ${PROJECT_NAME}.a test gcov_report

$(PROJECT_NAME).a: ${SOURCE} ${HEADERS}
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build a static library 's21_3DViewer.a'  )
	$(info ----------------------------------------)
	$(CC) -c $(CFLAGS) $(SOURCE)
	ar rc $@ ${OBJECTS}
	ranlib $@	

test: $(TESTS) $(SOURCE)
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build tests                             )
	$(info ----------------------------------------)
	$(CC) $^ $(ADD_LIB) -o $@
	./$@

gcov_report: clean lcov ${SOURCE} ${TESTS} 
	$(info                                         )
	$(info ----------------------------------------)
	$(info Create tests coverage report            )
	$(info ----------------------------------------)
	mkdir report
	$(CC) -c $(CFLAGS) $(ADD_LIB) $(GCOV) ${SOURCE} 
	$(CC) -o $@ $(GCOV) $(OBJECTS) $(TESTS) $(ADD_LIB)
	./$@
	lcov -t $@ -o $@.info -c -d . --no-external
	genhtml -o report/ $@.info

ifeq ($(_UNAME_), Darwin) # MacOS
	open $(BROWSER_APP)./ report/src/index.html
else
	$(BROWSER_APP)./ report/src/index.html
endif

lcov:
ifeq ("", "$(shell PATH=$(PATH) which lcov)")
	$(error Need to install lcov)
endif

style:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Check for code style and formatting     )
	$(info ----------------------------------------)
	clang-format -style=Google -i *.c *.h 

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/

