CXX      := clang++

CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion \
            -Wcast-align -Wcast-qual -Wold-style-cast -Woverloaded-virtual \
            -Wnon-virtual-dtor -Wnull-dereference -Wdouble-promotion -Wformat=2 \
            -Wimplicit-fallthrough -Wmisleading-indentation -std=c++23 -g \
            -Wno-old-style-cast

LDFLAGS  := -lGL -lGLU -lglut

BINDIR   := bin
TARGET   := main
SRCDIR   := src
SRC      := $(shell fd -e cpp . $(SRCDIR))

$(TARGET): $(SRC)
	@make -s format
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)

run: $(TARGET)
	@./$(BINDIR)/$(TARGET)

format:
	clang-format -i $(shell fd -e cpp -e h . $(SRCDIR))

watch:
	@while inotifywait -qq -re CLOSE_WRITE $(SRCDIR); do \
		clear; \
		make -s run; \
	done

clean:
	@make -s format
	rm -rf $(BINDIR)
