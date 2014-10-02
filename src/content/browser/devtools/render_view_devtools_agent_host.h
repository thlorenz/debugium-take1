// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVTOOLS_RENDER_VIEW_DEVTOOLS_AGENT_HOST_H_
#define CONTENT_BROWSER_DEVTOOLS_RENDER_VIEW_DEVTOOLS_AGENT_HOST_H_

#include <map>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/devtools/ipc_devtools_agent_host.h"
#include "content/browser/devtools/protocol/input_handler.h"
#include "content/browser/devtools/protocol/page_handler.h"
#include "content/common/content_export.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_contents_observer.h"

namespace cc {
class CompositorFrameMetadata;
}

namespace content {

class DevToolsPowerHandler;
class DevToolsProtocolHandlerImpl;
class DevToolsTracingHandler;
class RendererOverridesHandler;
class RenderViewHost;
class RenderViewHostImpl;

#if defined(OS_ANDROID)
class PowerSaveBlockerImpl;
#endif

class CONTENT_EXPORT RenderViewDevToolsAgentHost
    : public IPCDevToolsAgentHost,
      private WebContentsObserver,
      public NotificationObserver {
 public:
  static void OnCancelPendingNavigation(RenderViewHost* pending,
                                        RenderViewHost* current);

  RenderViewDevToolsAgentHost(RenderViewHost*);

  void SynchronousSwapCompositorFrame(
      const cc::CompositorFrameMetadata& frame_metadata);

  // DevTooolsAgentHost overrides.
  virtual void DisconnectWebContents() OVERRIDE;
  virtual void ConnectWebContents(WebContents* web_contents) OVERRIDE;
  virtual WebContents* GetWebContents() OVERRIDE;
  virtual Type GetType() OVERRIDE;
  virtual std::string GetTitle() OVERRIDE;
  virtual GURL GetURL() OVERRIDE;
  virtual bool Activate() OVERRIDE;
  virtual bool Close() OVERRIDE;

 private:
  friend class DevToolsAgentHost;
  virtual ~RenderViewDevToolsAgentHost();

  // IPCDevToolsAgentHost overrides.
  virtual void DispatchProtocolMessage(const std::string& message) OVERRIDE;
  virtual void SendMessageToAgent(IPC::Message* msg) OVERRIDE;
  virtual void OnClientAttached() OVERRIDE;
  virtual void OnClientDetached() OVERRIDE;

  // WebContentsObserver overrides.
  virtual void AboutToNavigateRenderView(RenderViewHost* dest_rvh) OVERRIDE;
  virtual void RenderViewHostChanged(RenderViewHost* old_host,
                                     RenderViewHost* new_host) OVERRIDE;
  virtual void RenderViewDeleted(RenderViewHost* rvh) OVERRIDE;
  virtual void RenderProcessGone(base::TerminationStatus status) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message,
                                 RenderFrameHost* render_frame_host) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidAttachInterstitialPage() OVERRIDE;
  virtual void DidDetachInterstitialPage() OVERRIDE;
  virtual void TitleWasSet(NavigationEntry* entry, bool explicit_set) OVERRIDE;
  virtual void NavigationEntryCommitted(
      const LoadCommittedDetails& load_details) OVERRIDE;

  // NotificationObserver overrides:
  virtual void Observe(int type,
                       const NotificationSource& source,
                       const NotificationDetails& details) OVERRIDE;

  void DisconnectRenderViewHost();
  void ConnectRenderViewHost(RenderViewHost* rvh);
  void ReattachToRenderViewHost(RenderViewHost* rvh);

  bool DispatchIPCMessage(const IPC::Message& message);

  void SetRenderViewHost(RenderViewHost* rvh);
  void ClearRenderViewHost();

  void RenderViewCrashed();
  void OnSwapCompositorFrame(const IPC::Message& message);
  bool OnSetTouchEventEmulationEnabled(const IPC::Message& message);

  void OnDispatchOnInspectorFrontend(const std::string& message);
  void OnSaveAgentRuntimeState(const std::string& state);

  void ClientDetachedFromRenderer();

  void InnerOnClientAttached();
  void InnerClientDetachedFromRenderer();

  RenderViewHostImpl* render_view_host_;
  scoped_ptr<devtools::input::InputHandler> input_handler_;
  scoped_ptr<devtools::page::PageHandler> page_handler_;
  scoped_ptr<DevToolsProtocolHandlerImpl> handler_impl_;
  scoped_ptr<RendererOverridesHandler> overrides_handler_;
  scoped_ptr<DevToolsTracingHandler> tracing_handler_;
  scoped_ptr<DevToolsPowerHandler> power_handler_;
#if defined(OS_ANDROID)
  scoped_ptr<PowerSaveBlockerImpl> power_save_blocker_;
#endif
  std::string state_;
  NotificationRegistrar registrar_;
  bool reattaching_;

  DISALLOW_COPY_AND_ASSIGN(RenderViewDevToolsAgentHost);
};

}  // namespace content

#endif  // CONTENT_BROWSER_DEVTOOLS_RENDER_VIEW_DEVTOOLS_AGENT_HOST_H_
