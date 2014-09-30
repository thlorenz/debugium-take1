// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_TRACING_HANDLER_H_
#define CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_TRACING_HANDLER_H_

#include <set>
#include <string>

#include "base/debug/trace_event.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/devtools/devtools_protocol.h"
#include "content/public/browser/tracing_controller.h"

namespace base {
class RefCountedString;
class Timer;
}

namespace content {

// This class bridges DevTools remote debugging server with the trace
// infrastructure.
class DevToolsTracingHandler : public DevToolsProtocol::Handler {
 public:
  enum Target { Browser, Renderer };
  explicit DevToolsTracingHandler(Target target);
  virtual ~DevToolsTracingHandler();

  void OnClientDetached();

  void OnTraceDataCollected(const std::string& trace_fragment);
  void OnTraceComplete();

 private:
  void OnRecordingEnabled(scoped_refptr<DevToolsProtocol::Command> command);
  void OnBufferUsage(float usage);

  scoped_refptr<DevToolsProtocol::Response> OnStart(
      scoped_refptr<DevToolsProtocol::Command> command);
  scoped_refptr<DevToolsProtocol::Response> OnEnd(
      scoped_refptr<DevToolsProtocol::Command> command);

  scoped_refptr<DevToolsProtocol::Response> OnGetCategories(
      scoped_refptr<DevToolsProtocol::Command> command);

  void OnCategoriesReceived(scoped_refptr<DevToolsProtocol::Command> command,
                            const std::set<std::string>& category_set);

  base::debug::TraceOptions TraceOptionsFromString(const std::string& options);

  void SetupTimer(double usage_reporting_interval);

  void DisableRecording(bool abort);

  scoped_ptr<base::Timer> buffer_usage_poll_timer_;
  Target target_;
  bool is_recording_;

  static const char* kDefaultCategories;
  static const double kDefaultReportingInterval;
  static const double kMinimumReportingInterval;

  base::WeakPtrFactory<DevToolsTracingHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DevToolsTracingHandler);
};

}  // namespace content

#endif  // CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_TRACING_HANDLER_H_
