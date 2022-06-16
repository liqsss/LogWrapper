## LogWrapper
#编译步骤：
1，修改CMakeLists.txt文件，指定本地的spdlog的include文件目录
2，mkdir build && cd build && cmake ../ && make -j
3，./logWrapper 即可运行日志打印示例程序。
4，该工程中有glog, roslog日志系统的使用示例及性能比较分析，如需使用，自行配置。


如果需要在其他项目中使用该日志系统
1，指定spdlog的include文件目录
2，拷贝该项目中的include/ src/两个文件目录到目的项目中，修改CMakeLists配置文件
