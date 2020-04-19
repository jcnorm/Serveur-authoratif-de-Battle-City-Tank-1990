PROJECT_NAME = Tanks

BUILD = build
BIN = $(BUILD)/bin
RESOURCES_DIR = resources

CC = g++
INCLUDEPATH =
LFLAGS = -O
CFLAGS = -c -Wall -std=c++17
ALT_CFLAGS = -std=c++17
LIBS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
APP_RESOURCES = font/prstartk.ttf png/texture.png levels
RESOURCES = $(APP_RESOURCES)

SERVER_FILE_NAME = Server

MODULES = engine app_state objects
SERVER_MODULES = remote_server remote_server/state_validators
SRC_DIRS = src $(addprefix src/,$(MODULES))
SERVER_SRC_DIRS = $(addprefix src/,$(SERVER_MODULES))
BUILD_DIRS = $(BUILD) $(BIN) $(addprefix $(BUILD)/,$(MODULES))
SERVER_BUILD_DIRS = $(BUILD) $(BIN) $(addprefix $(BUILD)/,$(SERVER_MODULES))

SOURCES = $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.cpp))
SERVER_SOURCES = $(foreach sdir,$(SERVER_SRC_DIRS),$(filter-out src/remote_server/$(SERVER_FILE_NAME).cpp, $(wildcard $(sdir)/*.cpp)))
SERVER_EXEC_SOURCES = $(foreach sdir,$(SERVER_SRC_DIRS),$(wildcard $(sdir)/$(SERVER_FILE_NAME).cpp))
OBJS = $(patsubst src/%.cpp,$(BUILD)/%.o,$(SOURCES))
SERVER_OBJS = $(patsubst src/%.cpp,$(BUILD)/%.o,$(SERVER_SOURCES))
SERVER_EXEC = $(patsubst src/%.cpp,$(BUILD)/%,$(SERVER_EXEC_SOURCES))

vpath %.cpp $(SRC_DIRS)

all: print $(SERVER_BUILD_DIRS) $(BUILD_DIRS) $(RESOURCES) compile

print:
	@echo
	@echo OS: $(OS)
	@echo MODULES: $(MODULES)
	@echo SRC_DIRS: $(SRC_DIRS)
	@echo BUILD_DIRS: $(BUILD_DIRS)
	@echo SERVER_SOURCES: $(SERVER_SOURCES)
	@echo SERVER_EXEC_SOURCES: $(SERVER_EXEC_SOURCES)
	@echo SOURCES: $(SOURCES)
	@echo RESOURCES: $(RESOURCES)
	@echo OBJS: $(OBJS)
	@echo INCLUDEPATH: $(INCLUDEPATH)
	@echo LIBSPATH: $(LIBSPATH)
	@echo LIBS: $(LIBS)
	@echo LFLAGS: $(LFLAGS)
	@echo

$(SERVER_BUILD_DIRS):
	mkdir -p $@

$(BUILD_DIRS):
	mkdir -p $@

compile: $(OBJS)  $(SERVER_OBJS) $(SERVER_EXEC)
	$(CC) $(OBJS) $(INCLUDEPATH) $(LIBSPATH) $(LIBS) $(LFLAGS) -o $(BIN)/$(PROJECT_NAME)

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDEPATH) $< -o $@

build/%: src/%.cpp
	$(CC) $(SERVER_OBJS) $(ALT_CFLAGS) $(INCLUDEPATH) $< -o $@

$(APP_RESOURCES):
	cp -R $(RESOURCES_DIR)/$@ $(BIN)

clean:
	rm -rf $(BUILD)
	rm -rf doc

doc:
	doxywizard Doxyfile
	doxygen