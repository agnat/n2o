BUILDTYPE ?=Release
N2O_TARGET =build/$(BUILDTYPE)/n2o.node
NODE_GYPE_OPTS =

ifeq ($(BUILDTYPE),Debug)
	NODE_GYPE_OPTS+= --debug
endif

all: $(N2O_TARGET)

test: $(N2O_TARGET) node_modules
	npm test

clean:
	node-gyp clean
	rm -rf node_modules
	node-gyp clean -C test
	node-gyp clean -C samples/hello_world
	rm -rf samples/hello_world/node_modules
	find . -name npm-debug.log -exec rm -rf {} \;

xcode:
	node-gyp configure -- -f xcode
	node-gyp configure -C test -- -f xcode
	node-gyp configure -C samples/hello_world -- -f xcode
	node-gyp configure -C samples/sandbox -- -f xcode
	open n2o.xcodeproj

.PHONY: all test clean xcode

#==============================================================================

build/Makefile:
	node-gyp configure $(NODE_GYPE_OPTS)

$(N2O_TARGET): build/Makefile
	node-gyp build $(NODE_GYPE_OPTS)

node_modules:
	npm link

