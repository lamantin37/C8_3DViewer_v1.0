CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard parser.c transformations.c)
HEADERS = $(wildcard auxiliary_modules.h)
TESTS = $(wildcard test_3dviewer.c)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
QMAKE_PATH = /home/jexwerquez/Qt5.12.12/5.12.12/gcc_64/bin/qmake
BUILD_SRC = /build-3DViewer-Desktop_Qt_5_12_12_GCC_64bit-Debug/
CFLAGS_TEST =`pkg-config --cflags --libs check`
CFLAGS_GCOV =-fprofile-arcs -ftest-coverage
DIR = report/tests

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
PROJECT_NAME := 3DViewer

all: clean style ${PROJECT_NAME}.a test gcov_report

tests: $(TESTS) $(SOURCE)
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build tests                             )
	$(info ----------------------------------------)
	$(CC) $^ $(ADD_LIB) -o $@
	./$@

pro:
	mkdir build
	${QMAKE_PATH} -o ./build/qMakefile
	cd build

install: clean pro
	$(info                                         )
	$(info ----------------------------------------)
	$(info Install the project                     )
	$(info ----------------------------------------)
	cd build/ && make -f qMakefile
	cd build/ && ./3DViewer

uninstall:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Uninstall the project                   )
	$(info ----------------------------------------)
	make clean
	-rm -rf ../${BUILD_SRC}


gcov_report: clean
	mkdir report
	@$(CC) $(CFLAGS) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(SOURCE) $(TESTS) -o $(DIR) $(ADD_LIB)
	@$(DIR)
	@gcov tests
	@lcov --capture --directory report --output-file report/main_coverage.info
	@genhtml report/main_coverage.info --output-directory report/lcov_report/index.html

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
	clang-format -style=Google -i *.c *.h *.cpp 

dvi:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Generate DVI file                       )
	$(info ----------------------------------------)
	open dvi.txt

dist: clean pro
	$(info                                         )
	$(info ----------------------------------------)
	$(info Create a distribution package           )
	$(info ----------------------------------------)
	cd build/ && make -f qMakefile
	tar cvzf Archive_3DViewer_v1.0.tgz build
	-rm -rf ./build

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf qMakefile
	-rm -rf ./build
	-rm -rf Archive_3DViewer_v1.0.tgz
	-rm -rf tests