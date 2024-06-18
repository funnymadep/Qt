# qt menu(linux环境)

## 环境

```text
    sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
    sudo apt-get install qtcreator 
```

## 编译

**CMakeLists.txt所在目录**

```text
    sudo rm -r build
    mkdir build && cd build
    cmake .. && make
```