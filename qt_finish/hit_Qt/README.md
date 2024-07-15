# qt hit(linux环境)

## 环境

```text
    sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools \
        libqt5multimedia5-plugins qtmultimedia5-dev
    sudo apt-get install qtcreator 
```

## 编译

**CMakeLists.txt所在目录**

```text
    sudo rm -r build
    mkdir build && cd build
    cmake .. && make
```