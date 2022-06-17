#include <iostream>
#include <chrono>
#include <thread>

#include "Pattern.hpp"
#include "LogWrapper.h"
//#include "glog/logging.h"
//#include "rclcpp/rclcpp.hpp"
//#include "spdlog/stopwatch.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"
#include "gtest/gtest.h"


//using namespace google;
//using namespace rclcpp;

#if 0
void testRoslog(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    int i = 0;
    spdlog::stopwatch sw;
    while (i < 100 * 1000)
    {
        RCLCPP_INFO(rclcpp::get_logger("monitor"),"ROS logger");
        i++;
    }
    std::cout  << "roslog Elapsed " << sw.elapsed().count() << std::endl;
}

void testGlogThread()
{
    int i = 0;
    spdlog::stopwatch sw;
    while (i < 100 * 1000)
    {
        LOG(INFO) << "async logger";
        i++;
    }
    LOG(INFO) << "testGlog Elapsed " << sw.elapsed().count();
}

void testGlog()
{
    // Start google log system:
    FLAGS_log_dir = "./glog/";
    google::InitGoogleLogging("loglog");
    google::SetLogDestination(google::GLOG_INFO, "./glog/");
    google::SetStderrLogging(google::GLOG_FATAL);
    google::SetLogFilenameExtension("log_");

    FLAGS_colorlogtostderr = true;  // Set log color
    FLAGS_logbufsecs = 5;  // Set log output speed(s)
    FLAGS_max_log_size = 50;  // Set max log file size
    FLAGS_stop_logging_if_full_disk = true;  // If disk is full

    LOG(INFO) << "GLOG=============";
    std::thread* t = new std::thread(testGlogThread);

    //log in thread.
    t->join();

    google::ShutdownGoogleLogging();

}

void testSpdlog_Async()
{
    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger","logs/async_log.txt");
    async_file->set_pattern("[%Y-%m-%d %H:%M:%S.%f %z][%t][%n][%l]: %v");
    int i = 0;
    spdlog::stopwatch sw;
    while (i < 100 * 1000)
    {
        async_file->info("async logger");
        i++;
    }
    async_file->info("asyncExample Elapsed {:.7}",sw);
}

void testSpdlog_Sync()
{
    spdlog::info("create logger");
    auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic_log.txt");
    logger->info("create success");
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%f %z][%t][%n][%l]: %v");
    int i = 0;
    spdlog::stopwatch sw;
    while (i < 100 * 1000)
    {
        logger->info("basic_logger_mt logger");

        i++;
    }
    logger->info("syncExample Elapsed {:.7}", sw);
}

int testBaseGlog()
{
   //初始化参数
   FLAGS_logtostderr = false;  //TRUE:标准输出,FALSE:文件输出
   FLAGS_alsologtostderr = true;  //除了日志文件之外是否需要标准输出
   FLAGS_colorlogtostderr = false;  //标准输出带颜色
   FLAGS_logbufsecs = 0;   //设置可以缓冲日志的最大秒数，0指实时输出
   FLAGS_max_log_size = 10; //日志文件大小(单位：MB)
   FLAGS_stop_logging_if_full_disk = true; //磁盘满时是否记录到磁盘

   google::InitGoogleLogging("mqttserver");
   google::SetLogDestination(google::GLOG_INFO,"./glog/");

   VLOG(INFO) << "not display";
   LOG(INFO) << "this is log";
   LOG(WARNING) << "this is warnning";
   LOG(ERROR) << "this is error";
   
   google::ShutdownGoogleLogging();
   return 0 ;
}
#endif

TEST(LogWrapper, normalTest)
{
    //std::cout <<"spdlog is running..." << std::endl;
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
    

    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < 100000; ++i)
    {
        LOG_DEBUG("message: {}", i);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    LOG_INFO("Total: {}",elapsed_seconds.count());
    //std::cout << "Total: " << elapsed_seconds.count() << std::endl;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#if 0
    testBaseGlog();
    testRoslog(argc, argv);
    testGlog();
    testSpdlog_Async();
    testSpdlog_Sync();
#endif

}

