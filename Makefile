N2O_TARGET=build/Release/n2o.node

all: $(N2O_TARGET)

build/Makefile:
	node-gyp configure

$(N2O_TARGET): build/Makefile
	node-gyp build

node_modules:
	npm link

test: $(N2O_TARGET) node_modules
	npm test

clean:
	rm -rf build node_modules
	rm -rf test/build
	rm -rf samples/hello_world/{build,node_modules}
	find . -name npm-debug.log -exec rm -rf {} \;


.PHONY: all test clean distclean
