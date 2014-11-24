BUILDTYPE ?=Release
N2O_TARGET =build/$(BUILDTYPE)/n2o.node
NODE_GYP_OPTS =

ifeq ($(BUILDTYPE),Debug)
	NODE_GYP_OPTS+= --debug
endif

all: $(N2O_TARGET)

test: $(N2O_TARGET) node_modules
	npm test

clean:
	rm -rf {build,node_modules}
	rm -rf test/build
	rm -rf samples/hello_world/{build,node_modules}
	rm -rf samples/sandbox/{build,node_modules}
	find . -name npm-debug.log -exec rm -rf {} \;

xcode:
	node-gyp configure --debug -- -f xcode
	node-gyp configure --debug -C test -- -f xcode
	node-gyp configure --debug -C samples/sandbox -- -f xcode
	open n2o.xcodeproj

.PHONY: all test clean xcode

#==============================================================================

build/Makefile:
	node-gyp configure $(NODE_GYP_OPTS)

$(N2O_TARGET): build/Makefile
	node-gyp build $(NODE_GYP_OPTS)

node_modules:
	npm link

