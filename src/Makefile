CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard parser.c transformations.c)
HEADERS = $(wildcard auxiliary_modules.h)
TESTS = $(wildcard test_3dviewer.c)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
QMAKE_PATH = /home/jexwerquez/Qt5.12.12/5.12.12/gcc_64/bin/qmake
BUILD_SRC = /build-3DViewer-Desktop_Qt_5_12_12_GCC_64bit-Debug/

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
	$(info Build a static library '3DViewer.a'  )
	$(info ----------------------------------------)
	$(CC) -c $(CFLAGS) $(SOURCE)
	ar rc $@ ${OBJECTS}
	ranlib $@	

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

install: pro
	$(info                                         )
	$(info ----------------------------------------)
	$(info Install the project                     )
	$(info ----------------------------------------)
	cd build/ && make -f qMakefile
	cd ..${BUILD_SRC} && ./3DViewer

uninstall:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Uninstall the project                   )
	$(info ----------------------------------------)
	make clean
	-rm -rf ../${BUILD_SRC}

gcov_report: clean lcov $(TESTS)
	$(info                                         )
	$(info ----------------------------------------)
	$(info Create tests coverage report            )
	$(info ----------------------------------------)
	mkdir report
	$(CC) -c $(CFLAGS) $(ADD_LIB) $(GCOV) $(SOURCE)
	$(CC) -o $@ $(GCOV) $(OBJECTS) $(TESTS) $(ADD_LIB)
	./$@
	lcov -t $@ -o $@.info -c -d . --no-external
	genhtml -o report/ $@.info
	# rm -rf *.gcda
	# rm -rf *.gcno
	# rm -rf *.info


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
