# AntiPirateScreen - Makefile
# Version: 2.0.0
# Author: TIBI624
# Branch: tibi624

.PHONY: all clean test build-c build-cpp build-python build-js build-cs build-java install

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

BUILD_DIR = build
SRC_C_DIR = src/c
SRC_CPP_DIR = src/cpp
SRC_PYTHON_DIR = src/python
SRC_JS_DIR = src/javascript
SRC_CS_DIR = src/csharp
SRC_JAVA_DIR = src/java

all: build-c build-cpp build-python build-js build-cs build-java

build-c:
	@echo "Building C library..."
	@mkdir -p $(BUILD_DIR)/c
	@cmake -S $(SRC_C_DIR) -B $(BUILD_DIR)/c
	@cmake --build $(BUILD_DIR)/c

build-cpp:
	@echo "Building C++ library..."
	@mkdir -p $(BUILD_DIR)/cpp
	@cmake -S $(SRC_CPP_DIR) -B $(BUILD_DIR)/cpp
	@cmake --build $(BUILD_DIR)/cpp

build-python:
	@echo "Building Python package..."
	@pip install -r $(SRC_PYTHON_DIR)/requirements.txt
	@python -m build $(SRC_PYTHON_DIR)

build-js:
	@echo "Building JavaScript package..."
	@cd $(SRC_JS_DIR) && npm ci && npm run build

build-cs:
	@echo "Building C# library..."
	@cd $(SRC_CS_DIR) && dotnet restore && dotnet build --configuration Release

build-java:
	@echo "Building Java library..."
	@cd $(SRC_JAVA_DIR) && mvn clean package

test:
	@echo "Running tests..."
	@cd tests/c && ./run_tests.sh
	@cd tests/cpp && ./run_tests.sh
	@cd tests/python && pytest
	@cd tests/javascript && npm test
	@cd tests/csharp && dotnet test
	@cd tests/java && mvn test

clean:
	@echo "Cleaning build directories..."
	@rm -rf $(BUILD_DIR)
	@rm -rf cmake-build-*
	@rm -rf node_modules
	@rm -rf __pycache__
	@cd $(SRC_JAVA_DIR) && mvn clean

install:
	@echo "Installing AntiPirateScreen..."
	@cmake --install $(BUILD_DIR)/c
	@cmake --install $(BUILD_DIR)/cpp

help:
	@echo "AntiPirateScreen Build System"
	@echo "Author: TIBI624"
	@echo "Branch: tibi624"
	@echo "Available targets:"
	@echo "  all        - Build all libraries"
	@echo "  build-c    - Build C library"
	@echo "  build-cpp  - Build C++ library"
	@echo "  build-python - Build Python package"
	@echo "  build-js   - Build JavaScript package"
	@echo "  build-cs   - Build C# library"
	@echo "  build-java - Build Java library"
	@echo "  test       - Run tests"
	@echo "  clean      - Clean build directories"
	@echo "  install    - Install libraries"