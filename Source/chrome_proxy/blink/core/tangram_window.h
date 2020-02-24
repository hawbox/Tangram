// begin Add by TangramTeam
#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_WINDOW_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_WINDOW_H_

#include <map>

#include "third_party/blink/renderer/bindings/core/v8/script_value.h"
#include "third_party/blink/renderer/bindings/core/v8/serialization/transferables.h"
#include "third_party/blink/renderer/core/execution_context/context_lifecycle_observer.h"
#include "third_party/blink/renderer/core/dom/events/event_target.h"
#include "third_party/blink/renderer/core/event_type_names.h"

#include "third_party/blink/renderer/platform/heap/handle.h"
#include "third_party/blink/renderer/platform/wtf/assertions.h"
#include "third_party/blink/renderer/platform/wtf/forward.h"

namespace blink {

using namespace std;

class Document;
class ScriptState;
class TangramNode;
class ExceptionState;
class V8GeneralCallback;
class WebLocalFrameClient;
class SerializedScriptValue;

class CORE_EXPORT TangramWindow final : public EventTargetWithInlineData,
									  public DOMWindowClient {
  DEFINE_WRAPPERTYPEINFO();
  USING_GARBAGE_COLLECTED_MIXIN(TangramWindow);

 public:
  static TangramWindow* Create(LocalFrame* frame) { return MakeGarbageCollected<TangramWindow>(frame); }
  static TangramWindow* Create(LocalFrame* frame, const String& strName);

  void Trace(blink::Visitor*) override;

  // Called when an event listener has been successfully added.
  void AddedEventListener(const AtomicString& event_type,
                          RegisteredEventListener&) override;

  long windowhandle();
  String name();

  // Message method

  void addChannel(const String& channel);
  void removeChannel(const String& channel);
  void sendMessage(const String& id, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5);
  
  TangramNode* getNode(const String& nodeName);
  TangramNode* getNode(const long nodeHandle);

  DEFINE_ATTRIBUTE_EVENT_LISTENER(MessageReceived, kTangramwindow)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(MdiChildActivate, kMdichildactivate)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(NodeMouseActivate, kNodemouseactivate)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(TangramNodeCreated, kTangramnodecreated)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(TreeViewNodeAfterSelect, kTreeviewnodeafterselect)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(TreeViewNodeMouseDoubleClick, kTreeviewnodemousedoubleclick)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(ListViewItemSelectionChanged, kListviewitemselectionchanged)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(FormMenuItemClick, kFormmenuitemclick)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(FormButtonClick, kFormbuttonclick)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(WinFormCreated, kWinformcreated)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(WinFormClosed, kWinformclosed)
      DEFINE_ATTRIBUTE_EVENT_LISTENER(BindCLRCtrlEvent, kBindclrctrlevent)

  // EventTarget overrides:
  const AtomicString& InterfaceName() const override;
  ExecutionContext* GetExecutionContext() const override;

  TangramWindow(LocalFrame*);
  TangramWindow(LocalFrame*, const String& strWindowName);

  ~TangramWindow() override;

  long windowhandle_ = 0;
  mutable Member<TangramNode> m_pHostNode;
  WebLocalFrameClient* web_local_frame_client;
  map<long, TangramNode*> m_mapTangramNode;
  map<std::wstring, TangramNode*> m_mapTangramNode2;
private:
  String name_;
  String m_strWindowXml;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_WINDOW_H_
// end Add by TangramTeam
