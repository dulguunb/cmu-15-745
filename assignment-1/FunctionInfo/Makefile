all: FunctionInfo.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0 -fPIC

%.so: %.o
	$(CXX) -dylib -fPIC -shared $^ -o $@
clean:
	rm -f *.o *~ *.so