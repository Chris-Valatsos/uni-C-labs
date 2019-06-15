CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi -O2 -lm
INCS = 1_external_libraries/neillsdl2.h
SOURCES =  $(TARGET).c 2_source_code/neillsdl2.c
LIBS =  `sdl2-config --libs` -lm

# The following files can be used to test both the parser and the interpreter
# Test files for paser and interpreter
TEST_DATA_1 = 3_test_files/data1.txt
TEST_DATA_2 = 3_test_files/data2.txt
TEST_DATA_3 = 3_test_files/data3.txt
TEST_DATA_4 = 3_test_files/data4.txt

# Test files for paser and interpreter
TEST_DATA_11 = 3_test_files/data11.txt
TEST_DATA_12 = 3_test_files/data12.txt

# False Test files for parser, interpreter and extension
TEST_DATA_5 = 3_test_files/data5.txt
TEST_DATA_6 = 3_test_files/data6.txt
TEST_DATA_7 = 3_test_files/data7.txt
TEST_DATA_8 = 3_test_files/data8.txt
TEST_DATA_9 = 3_test_files/data9.txt
TEST_DATA_10 = 3_test_files/data10.txt

all: parse test_parser interp test_interpreter extension

test_parser: 2_source_code/parser.c 2_source_code/test_parser.c 1_external_libraries/parser.h
	clang 2_source_code/parser.c 2_source_code/test_parser.c -o $@ $(CFLAGS)

parse: 2_source_code/main_parser.c 2_source_code/parser.c 1_external_libraries/parser.h
	clang 2_source_code/main_parser.c 2_source_code/parser.c -o $@ $(CFLAGS)

test_interpreter: 2_source_code/test_interpreter.c 2_source_code/interpreter.c 1_external_libraries/interpreter.h
	clang 2_source_code/interpreter.c 2_source_code/test_interpreter.c -o $@ $(CFLAGS)

interp: 2_source_code/main_interpreter.c 2_source_code/interpreter.c 1_external_libraries/interpreter.h $(INCS)
	clang 2_source_code/main_interpreter.c 2_source_code/interpreter.c 2_source_code/neillsdl2.c -o $@ $(CFLAGS) `sdl2-config --cflags` $(LIBS)

extension: 2_source_code/main_extension.c 2_source_code/extension.c 1_external_libraries/extension.h $(INCS)
	clang 2_source_code/main_extension.c 2_source_code/extension.c 2_source_code/neillsdl2.c -o $@ $(CFLAGS) `sdl2-config --cflags` $(LIBS)

clean:
	rm -fr parse test_parser interp test_interpreter extension

run: all
	./parse $(TEST_DATA_1)
	./parse $(TEST_DATA_2)
	./parse $(TEST_DATA_3)
	./parse $(TEST_DATA_4)
	./test_parser
	./interp $(TEST_DATA_1)
	./interp $(TEST_DATA_2)
	./interp $(TEST_DATA_3)
	./interp $(TEST_DATA_4)
	./test_interpreter
	./extension $(TEST_DATA_11)
	./extension $(TEST_DATA_12)

.PHONY: clean run all
