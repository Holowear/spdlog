/*
 * android_sink.h
 *
 *  Created on: Aug 22, 2015
 *      Author: chetan
 */

#ifndef EXTERNAL_SPDLOG_INCLUDE_SPDLOG_SINKS_ANDROID_SINK_H_
#define EXTERNAL_SPDLOG_INCLUDE_SPDLOG_SINKS_ANDROID_SINK_H_

#pragma once

#include <string>
#include <mutex>
#include <android/log.h>

#include "../details/null_mutex.h"
#include "./base_sink.h"

namespace spdlog
{
namespace sinks
{
namespace
{
	const android_LogPriority level_to_android_priorities[] =
	{
			ANDROID_LOG_VERBOSE,
			ANDROID_LOG_DEBUG,
			ANDROID_LOG_INFO,
			ANDROID_LOG_INFO,
			ANDROID_LOG_WARN,
			ANDROID_LOG_ERROR,
			ANDROID_LOG_ERROR,
			ANDROID_LOG_ERROR,
			ANDROID_LOG_FATAL,
			ANDROID_LOG_SILENT
	};
}

template <class Mutex>
class android_sink : public base_sink<Mutex>
{
public:
	explicit android_sink() {}
	android_sink(const android_sink&) = delete;
	android_sink& operator =(const android_sink&) = delete;
	virtual ~android_sink() = default;
protected:
	void _sink_it(const details::log_msg& msg) override
	{
		android_LogPriority priority = level_to_android_priorities[static_cast<int>(msg.level)];
		__android_log_write(priority, msg.logger_name.c_str(), msg.formatted.data());
	}
	void flush() override {}
};

typedef android_sink<std::mutex> android_sink_mt;
typedef android_sink<details::null_mutex> android_sink_st;
}
}



#endif /* EXTERNAL_SPDLOG_INCLUDE_SPDLOG_SINKS_ANDROID_SINK_H_ */
