// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

///
/// \file KafkaConsumer.h
/// \author Adam Wegrzynek <adam.wegrzynek@cern.ch>
///

#ifndef ALICEO2_MONITORING_TRANSPORTS_KAFKA_H
#define ALICEO2_MONITORING_TRANSPORTS_KAFKA_H

#include "TransportInterface.h"

#include <chrono>
#include <string>
#include <librdkafka/rdkafkacpp.h>

namespace o2
{
/// ALICE O2 Monitoring system
namespace monitoring
{
/// Monitoring transports
namespace transports
{

/// \brief Transport that sends string formatted metrics via Kafka
class KafkaConsumer : public TransportInterface
{
 public:
  /// Creates producer
  /// \param hostname      Hostname
  /// \param port          Port number
  /// \param topic 	   Kafka topic
  KafkaConsumer(const std::string& host, unsigned int port, const std::vector<std::string>& topic);

  /// Deletes producer
  ~KafkaConsumer();

  void send(std::string&&/* message*/) override {
    throw MonitoringException("Transport", "This transport does not implement sending");
  }

  /// Sends metric via Kafka
  /// \param message   r-value string formated
  std::vector<std::string> receive() override;
 private:
  /// Kafka producer instance
  RdKafka::KafkaConsumer* mConsumer;

  /// Kafka topic
  std::vector<std::string> mTopics;
};

} // namespace transports
} // namespace monitoring
} // namespace o2

#endif // ALICEO2_MONITORING_TRANSPORTS_KAFKA_H
