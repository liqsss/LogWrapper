# LogWrapper  
## 编译步骤：  
1，修改CMakeLists.txt文件，指定本地的spdlog的include文件目录  
2，mkdir build && cd build && cmake ../ && make -j  
3，./logWrapper 即可运行日志打印示例程序。  
4，该工程中有glog, roslog日志系统的使用示例及性能比较分析，如需使用，自行配置。  
  
  
如果需要在其他项目中使用该日志系统  
1，指定spdlog的include文件目录  
2，拷贝该项目中的include/ src/两个文件目录到目的项目中，修改CMakeLists配置文件  
  
## 使用方法：  
```cpp
SET_MODEL_NAME("TestModel");  
SET_LOG_PATH("./");  
SET_LOG_LEVEL(LOG_INFO_E);  
LOG_DEBUG("This message should not be displayed!");  
SET_LOG_LEVEL(LOG_TRACE_E);  
LOG_TRACE("This message is trace");  
LOG_DEBUG("This message should be displayed..");   
LOG_INFO("{}-----{:7}",1,222.22);  
LOG_ERROR("log error: {}", -1);  
LOG_CRITICAL("This message is critical");  
```  
## 输出  
[09:39:25.221--06/16/22][trace][14856][TestModel] This message is trace  
[09:39:25.221--06/16/22][debug][14856][TestModel] This message should be displayed..  
[09:39:25.221--06/16/22][info][14856][TestModel] 1----- 222.22  
[09:39:25.221--06/16/22][error][14856][TestModel] log error: -1  
[09:39:25.221--06/16/22][critical][14856][TestModel] This message is critical  
  
## 引用
[spdlog库](https://github.com/gabime/spdlog)  
[glog库](https://github.com/google/glog)  
[ros2log库](https://github.com/ros2/rclcpp)  
