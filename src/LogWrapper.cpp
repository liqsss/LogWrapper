#include "LogWrapper.h"
#include "spdlog/sinks/rotating_file_sink.h"

void LogWrapper::initial()
{
    logger_ = spdlog::rotating_logger_mt("novabot", filePath_, 1048576 * 5, 3);
    spdlog::set_default_logger(logger_);
    std::string temp = "[%H:%M:%S.%e--%x][%l][%t][";
    temp += model_;
    temp += "] %v";
    spdlog::set_pattern(temp);
    spdlog::set_level(spdlog::level::level_enum(level_));
}

void LogWrapper::setLogPath(const char* path)
{
    filePath_ = path;
    filePath_ += "/";
    filePath_ += model_;
    filePath_ += "/novabot-logs.txt";
    initial();
}

void LogWrapper::setLevel(LOG_LEVEL_ENUM level)
{
    level_ = level;
    spdlog::set_level(spdlog::level::level_enum(level_));
}

void LogWrapper::setModel(const char* model)
{
    model_ = model;
}

std::shared_ptr<spdlog::logger> LogWrapper::getLogger()
{
    return logger_;
}

LogWrapper::LogWrapper()
    : filePath_("logs/novabot-logs.txt")
    , level_(LOG_INFO_E)
    , model_("Main")
{
}

LogWrapper::~LogWrapper()
{
}