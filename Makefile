# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++11 -I/root/projects/project-lib/rocksdb/include

# Linker flags
LDFLAGS = -L/root/projects/project-lib/rocksdb -lrocksdb -lpthread -lz -lbz2 -lsnappy -llz4 -lzstd

# Source files
SRCS = main.cc

# Output executable
TARGET = apricot

# Build target
$(TARGET): $(SRCS)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean target
clean:
    rm -f $(TARGET)