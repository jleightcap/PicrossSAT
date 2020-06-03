# PicrossSAT
Solve picross (nonogram) puzzles using MiniSat.

## Dependencies
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
```

## Usage
```
./picrosssat [ROW] [COL]
```

For example,
```
$ ./picrosssat "[1] [3] [1]" "[1] [3] [1]"
===SAT===
x█x
███
x█x
```

Or for file input,

```
./picrosssat [FILE]
```

First line of file is row restriction, second is column restriction:

```
$ cat test.dat
[1] [3] [1]
[1] [3] [1]
$ ./picrosssat test.dat
===SAT===
x█x
███
x█x
```
