include ../config.mk

TEST_SOURCE_FILES = $(wildcard ./*.cpp)
TEST_OBJECT_FILES = $(patsubst %.cpp,%.o,$(TEST_SOURCE_FILES))
WORKSHY_PATH = ../workshy
CXXFLAGS += -L$(WORKSHY_PATH) -L./ -L../

.PHONY: main
main: check_error run_tests

.PHONY: run_tests
run_tests: libswissmilk.a compile_tests

.PHONY: compile_tests
compile_tests: libtests.a
	$(CXX) $(CXXFLAGS) $^ -o run_tests -ltests -lworkshy -lswissmilk $(LIBS)

libtests.a: $(TEST_OBJECT_FILES)
	ar -crs $@ $^

libswissmilk.a:
	make -C ../ $@

./%.o: ./%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -c -fPIC -lworkshy -lswissmilk $(LIBS)

.PHONY: check_error
check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

.PHONY: clean
clean:
	-find . -type f -name "*.o" -delete
	-rm *.out
	-rm run_tests
	-rm *.a⏎    