//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include "profiler.h"

namespace rperf {

std::string TracePoint::capture() {
  // std::ofstream file;
  // file.open(file_path, std::ios::app);
  // file << m_channel.get_log_dir() << std::endl;
  // file.close();
  if (running != Status::CAPTURE) {
    return "";
  }
  running = Status::STOP;
  std::ostringstream stream;

  if (m_channel->is_enabled()) {
    stream << m_channel->get_channel_name() << " - " 
           << trace_label << " - ";
  }

  stream << "start: " << start_time.time_since_epoch().count() << " "
         << "start ms: " << start_time_ms << " "
         << "end: " << end_time.time_since_epoch().count() << " "
         << "end ms: " << end_time_ms << " "
         << "duration: " << duration_time.count() << " ms";
  std::string msg = stream.str();

  if (m_channel->is_enabled()) {
    m_channel->get_logger()->log(msg);
  }

  return msg;
};
}  // namespace rperf
