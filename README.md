# PicrossSAT
Solve picross (nonogram) puzzles using MiniSat.

## Requirements
MiniSat with CMake integration, for example master-keyring's fork of `minisat`:
```
git clone https://github.com/master-keying/minisat/
```

For testing, Google Test.

## Building
Verified for `g++ 10.1.0` and `clang 10.0.0`:
```
mkdir build && cd build
cmake .. && make picrosssat
./picrosssat [file]
```

For testing, `make test && ./test`
