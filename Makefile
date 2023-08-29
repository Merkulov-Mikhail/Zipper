COMPILER=g++ -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
BUILD_DIR=build
SOURCES=$(BUILD_DIR)/main.o $(BUILD_DIR)/coder.o

.PHONY: all mk_folder


all: mk_folder main.exe


mk_folder:
ifeq (,$(wildcard ./$(BUILD_DIR)))
	@mkdir $(BUILD_DIR)
endif

main.exe: $(SOURCES)
	$(COMPILER) $^ -o $@

$(BUILD_DIR)/main.o: main.cpp coder.h
	@$(COMPILER) -c $< -o $@

$(BUILD_DIR)/coder.o: coder.cpp coder.h
	@$(COMPILER) -c $< -o $@
