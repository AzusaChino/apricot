# apricot

a project built with c/c++

## Contents

- some practices from TLPI
- some practices from other sources

## install cmake in centos

1. `yum install -y gcc gcc-c++ make automake`
2. `yum install -y wget`
3. download latest or the version you need src pack. check [here](https://cmake.org/download/)
4. `tar -zxvf cmake-xxx.tar`
5. `./bootstrap`
6. `make`
7. `make install`

## install ninaja in centos

### install autoconf (helpers)

`yum install autoconf automake libtool`

### install `re2c`

download tar package from [releases](https://github.com/skvadrik/re2c/releases)

```sh
tar -xf re2c-3.0.tar.xz
cd re2c-3.0
autoreconf -i -W all
./configure
make && make install
```

### install `ninja`

```sh
git clone git@github.com:ninja-build/ninja.git
cd ninja
python3 configure.py --bootstrap
cp ninja /usr/bin
```

## Problems

### command-line error language modes specified are incompatible

check `c_cpp_properties.json`, get rid of `"configurationProvider": "ms-vscode.cmake-tools"`
