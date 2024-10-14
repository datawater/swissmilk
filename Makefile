include config.mk

SWISSMILK_SOURCE_FILES = $(wildcard src/*.cpp)
SWISSMILK_OBJECT_FILES = $(patsubst %.cpp,%.o,$(SWISSMILK_SOURCE_FILES))
LIBSWISSMILK_OBJECT_FILES = $(filter-out src/main.o,$(SWISSMILK_OBJECT_FILES))

.PHONY: main
main: check_error swissmilk

.PHONY: test
test: workshy
	make -C ./tests

swissmilk: $(SWISSMILK_OBJECT_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

libswissmilk.a: $(LIBSWISSMILK_OBJECT_FILES)
	ar -crs $@ $^

.PHONY: workshy
workshy:
	make -C ./workshy

src/%.o: src/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: check_error
check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

.PHONY: clean
clean:
	-find . -type f -name "*.o" -delete
	-rm swissmilk
	-rm *.a

	-make -C ./workshy clean
	-make -C ./tests clean