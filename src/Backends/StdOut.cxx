///
/// \file StdOut.cxx
/// \author Adam Wegrzynek <adam.wegrzynek@cern.ch>
///

#include "StdOut.h"
#include "../MonLogger.h"
#include <iostream>

namespace o2
{
/// ALICE O2 Monitoring system
namespace monitoring
{
/// Monitoring backends
namespace backends
{

inline unsigned long StdOut::convertTimestamp(const std::chrono::time_point<std::chrono::system_clock>& timestamp)
{
  return std::chrono::duration_cast <std::chrono::milliseconds>(
    timestamp.time_since_epoch()
  ).count();
}

StdOut::StdOut() : mStream(std::cout)
{
  setVerbosisty(backend::Verbosity::Debug);
  MonLogger::Get() << "StdOut backend initialized" << MonLogger::End();
}

void StdOut::addGlobalTag(std::string name, std::string value)
{
  if (!tagString.empty()) {
    tagString += ",";
  }
  tagString += name + "=" + value;
}

void StdOut::send(std::vector<Metric>&& metrics) {
  for (auto& m : metrics) {
    send(m);
  }
}

void StdOut::sendMultiple(std::string measurement, std::vector<Metric>&& metrics)
{
  for (auto& metric : metrics) {
    std::string metricTags{};
    for (const auto& tag : metric.getTags()) {
      if (!metricTags.empty()) {
        metricTags += ",";
      }
      metricTags += tag.name + "=" + tag.value;
    }
    if (!metricTags.empty()) {
      metricTags = "," + metricTags;
    }
    mStream <<  "[METRIC] " << measurement << "/" << metric.getName() << "," << metric.getType() << " "
      << metric.getValue() << " " << convertTimestamp(metric.getTimestamp()) << " " << tagString
      << metricTags << "\n";
  }
}

void StdOut::send(const Metric& metric)
{
  std::string metricTags{};
  for (const auto& tag : metric.getTags()) {
    if (!metricTags.empty()) {
      metricTags += ",";
    }
    metricTags += tag.name + "=" + tag.value;
  }
  if (!metricTags.empty()) {
    metricTags = "," + metricTags;
  }
  mStream << "[METRIC] " << metric.getName() << "," << metric.getType() << " " << metric.getValue()
    << " " << convertTimestamp(metric.getTimestamp()) << " " << tagString << metricTags
    << "\n";
}

} // namespace backends
} // namespace monitoring
} // namespace o2