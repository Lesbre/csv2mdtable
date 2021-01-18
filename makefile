# =============================
# Variables
# =============================

ansi = on

SOURCE = ./src
BUILD = ./build
CMAKE_SRC = .
EXE = csv2mdtable

# =============================
# makefile code and variable setting
# =============================

ifeq ($(ansi),on)
	# Bold orange text
	color_s=\033[33;1m
	color_e=\033[38;22m
else
	color_s=
	color_e=
endif

# ====================
# Default target
# ====================

default:

# ====================
# Specific rules
# ====================

$(BUILD)/Makefile: $(CMAKE_SRC)/CMakeLists.txt
	echo "$(color_s)Running cmake$(color_e)"
	cmake -DCMAKE_BUILD_TYPE=Debug -S $(CMAKE_SRC) -B $(BUILD)

$(BUILD)/$(EXE): $(BUILD)/Makefile $(SOURCE)/*
	echo "$(color_s)Running cmake's makefile with target $(EXE)$(color_e)"
	$(MAKE) -C $(BUILD) $(EXE)

./$(EXE): $(BUILD)/$(EXE)
	echo "$(color_s)Copying executable$(color_e)"
	cp $(BUILD)/$(EXE) ./$(EXE)

# =============================
# Special Targets
# =============================

# No display of executed commands.
$(VERBOSE).SILENT:

.PHONY: clean clean-all default

default: ./$(EXE)

clean:
	echo "$(color_s)Removing build files$(color_e)"
	$(MAKE) -C $(BUILD) clean
	rm -f $(SOURCE)/project.hpp

clean-all:
	echo "$(color_s)Removing build files, cmake files and executable$(color_e)"
	rm -rf $(BUILD)
	rm -f ./$(EXE)
