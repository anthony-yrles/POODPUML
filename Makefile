TARGET := POODPUML
CC := g++

SRCS_FOLDER := src
INCLUDE_FOLDER := include
PREREQUISITES_FOLDER := prerequisites
OBJS_FOLDER := objs
BIN_FOLDER := .

SDL_INCLUDE := -I./include

CFLAGS := -g -Wall -Wextra -flto -O1 -I$(INCLUDE_FOLDER) -I$(PREREQUISITES_FOLDER) $(SDL_INCLUDE) -MMD
LDFLAGS := -L./lib/ 

SRCS_RAW := main.cpp \
			VueCpp/Draw.cpp \
            VueCpp/GuiInGame.cpp \
            VueCpp/GuiMenu.cpp \
            VueCpp/GuiOptions.cpp \
			ModelCpp/Castle.cpp \
			ModelCpp/Enemy.cpp \
			ModelCpp/Map.cpp \
			ModelCpp/Observable.cpp \
			ModelCpp/Tower.cpp \
			ControllerCpp/MapController.cpp \
            ControllerCpp/Sound.cpp \

SRCS := $(addprefix $(SRCS_FOLDER)/, $(SRCS_RAW))
OBJS := $(SRCS:$(SRCS_FOLDER)/%.cpp=$(OBJS_FOLDER)/$(SRCS_FOLDER)/%.o)
DEPS := $(OBJS:.o=.d)
PREREQUISITES := $(wildcard $(PREREQUISITES_FOLDER)/*.cpp)

# Liste des sous-répertoires des sources
SRCS_SUBDIRS := $(sort $(dir $(SRCS)))
OBJS_SUBDIRS := $(addprefix $(OBJS_FOLDER)/, $(SRCS_SUBDIRS))

.PHONY: all clean re fclean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN_FOLDER)/$@ $^ -lSDL2 -lSDL2_ttf -lSDL2_image

$(OBJS_FOLDER)/$(SRCS_FOLDER)/%.o: $(SRCS_FOLDER)/%.cpp | $(OBJS_FOLDER) $(OBJS_SUBDIRS)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

# Créer le répertoire des objets et les sous-répertoires nécessaires
$(OBJS_FOLDER):
	mkdir -p $(OBJS_FOLDER)

$(OBJS_SUBDIRS):
	mkdir -p $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(BIN_FOLDER)/$(TARGET)

re: fclean all

test: all
	$(BIN_FOLDER)/$(TARGET).exe
