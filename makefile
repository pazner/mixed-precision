ENABLED_PRECISIONS=FP32 FP64
DEFAULT_PRECISION=FP64

LIB_SOURCES=vector.cpp
BUILD_DIRS=$(foreach PRECISION, $(ENABLED_PRECISIONS), build/$(PRECISION))
OBJECTS=$(foreach BUILD_DIR, $(BUILD_DIRS), $(LIB_SOURCES:%.cpp=$(BUILD_DIR)/%.o))
LIB=libexample.a

APP_SOURCE=main.cpp
APP=main

BASE_FLAGS=-std=c++11 -DDEFAULT_PRECISION=$(DEFAULT_PRECISION)
ENABLE_PRECISION_FLAGS=$(foreach PRECISION, $(ENABLED_PRECISIONS), -DENABLE_$(PRECISION)=YES)

APP_FLAGS=$(BASE_FLAGS) $(ENABLE_PRECISION_FLAGS)

.PHONY: clean

$(APP): $(LIB) $(APP_SOURCE)
	c++ $(APP_FLAGS) $(APP_SOURCE) $(LIB) -o $@

$(LIB): $(OBJECTS)
	ar crv $@ $(OBJECTS)

define generate_rules

BUILD_DIR_$(1) := build/$(1)
CPP_FLAGS_$(1) := $$(BASE_FLAGS) -DUSE_$(1)=YES

$$(BUILD_DIR_$(1))/%.o: %.cpp | $$(BUILD_DIR_$(1))
	c++ $$(CPP_FLAGS_$(1)) $$< -c -o $$@

$$(BUILD_DIR_$(1)):
	mkdir -p $$@

endef

$(foreach PRECISION, $(ENABLED_PRECISIONS), $(eval $(call generate_rules,$(PRECISION))))

clean:
	rm -rf build $(LIB)
