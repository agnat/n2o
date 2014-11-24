BUILDTYPE?=Release
N2O_TARGET=build/$(BUILDTYPE)/n2o.node

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
	node-gyp configure

$(N2O_TARGET): build/Makefile
	node-gyp build

node_modules:
	npm link

