#ifndef LOG_WRAPPER__H_
#define LOG_WRAPPER__H_
#include <string>
#include "spdlog/spdlog.h"  //version > 1.5 
#include "Pattern.hpp"

//LOG LEVEL ENUM
enum LOG_LEVEL_ENUM: int
{
    LOG_TRACE_E = 0,
    LOG_DEBUG_E,
    LOG_INFO_E,
    LOG_WARN_E,
    LOG_ERROR_E,
    LOG_CRITICAL_E,
    LOG_MAX_E
};

class LogWrapper
{
public:
    friend class Singleton<LogWrapper>;
    void initial();
    void setLogPath(const char*);
    void setLevel(LOG_LEVEL_ENUM);
    void setModel(const char*);
    std::shared_ptr<spdlog::logger> getLogger();
private:
    LogWrapper();
    ~LogWrapper();
    std::shared_ptr<spdlog::logger> logger_;
    std::string filePath_;
    LOG_LEVEL_ENUM level_;
    std::string model_;
};

#define LOGGER Singleton<LogWrapper>::createInstance()->getLogger()

//set log  configure
#define SET_MODEL_NAME Singleton<LogWrapper>::createInstance()->setModel
#define SET_LOG_PATH Singleton<LogWrapper>::createInstance()->setLogPath
#define SET_LOG_LEVEL Singleton<LogWrapper>::createInstance()->setLevel

// LOG LEVEL
#define LOG_TRACE LOGGER->trace
#define LOG_DEBUG LOGGER->debug
#define LOG_INFO  LOGGER->info
#define LOG_ERROR LOGGER->error
#define LOG_CRITICAL LOGGER->critical

#endif //!LOG_WRAPPER__H_