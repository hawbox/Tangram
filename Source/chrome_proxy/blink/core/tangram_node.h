// begin Add by TangramTeam
#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_NODE_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_NODE_H_

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

class Tangram;
class TangramWindow;
class TangramWinform;
class TangramControl;

class Document;
class ScriptState;
class ExceptionState;
class V8GeneralCallback;
class WebLocalFrameClient;
class SerializedScriptValue;

class CORE_EXPORT TangramNode final : public EventTargetWithInlineData,
									  public DOMWindowClient {
  DEFINE_WRAPPERTYPEINFO();
  USING_GARBAGE_COLLECTED_MIXIN(TangramNode);
  //USING_PRE_FINALIZER(TangramNode, Dispose);

 public:
  static TangramNode* Create(LocalFrame* frame) { return MakeGarbageCollected<TangramNode>(frame); }
  static TangramNode* Create(LocalFrame* frame, const String& strHandle);

  void Trace(blink::Visitor*) override;

  // Called when an event listener has been successfully added.
  void AddedEventListener(const AtomicString& event_type,
                          RegisteredEventListener&) override;

  long row();
  long col();
  long rows();
  long cols();
  long nodehandle();

  TangramWindow* parentWindow();
  TangramWinform* parentForm();

  String name();

  // Message method

  void addChannel(const String& channel);
  void removeChannel(const String& channel);
  void sendMessage(const String& id, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5);
  
  // Data Dictionary:
  void setVal(const String& strKey, const String& val);
  String getVal(const String& strKey);
  void clearData();

  //Control Bind API:
  void setControlVal(const String& CtrlID, long CtrlHandle, const String& strVal);
  void BindControlEvent(const String& CtrlID, long CtrlHandle, long EventID, const String& strBindID);

  // Node API:
  TangramNode* getChild(long nIndex);
  TangramNode* getChild(const String& strName);
  TangramControl* getControl(const String& strCtrlName);

  DEFINE_ATTRIBUTE_EVENT_LISTENER(MessageReceived, kTangram)
  DEFINE_ATTRIBUTE_EVENT_LISTENER(MdiChildActivate, kMdichildactivate)
  DEFINE_ATTRIBUTE_EVENT_LISTENER(NodeMouseActivate, kNodemouseactivate)
  DEFINE_ATTRIBUTE_EVENT_LISTENER(TangramNodeCreated, kTangramnodecreated)
  DEFINE_ATTRIBUTE_EVENT_LISTENER(TangramControlCreated, kTangramcontrolcreated)
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

  TangramNode(LocalFrame*);
  TangramNode(LocalFrame*, const String& strNodeXml);
  TangramNode* AddChild(long nHandle, const String& strNodeName, blink::Tangram*);
  TangramControl* AddCtrl(long nCtrlHandle, const String& strCtrlName, const String& strWebPageID, blink::Tangram*);

  ~TangramNode() override;

  long nHandle = 0;
  long row_ = 0;
  long col_ = 0;
  long rows_ = 0;
  long cols_ = 0;
  long nodehandle_ = 0;

  String name_;

  WebLocalFrameClient* web_local_frame_client;
  mutable Member<TangramWindow> m_pParentWnd;
  mutable Member<TangramWinform> m_pParentForm;

  HeapHashMap<long, Member<TangramControl>> m_mapChildControl;
  HeapHashMap<String, Member<TangramControl>> m_mapChildControl2;
  HeapHashMap<int, Member<TangramNode>> m_mapChildNode;
  HeapHashMap<String, Member<TangramNode>> m_mapChildNode2;

private:
  String m_strNodeXml;
  map<std::wstring, String> m_mapVal;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_NODE_H_
// end Add by TangramTeam
