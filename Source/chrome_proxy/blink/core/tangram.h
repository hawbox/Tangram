// begin Add by TangramTeam
#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_H_

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <regex>

#include "third_party/blink/renderer/bindings/core/v8/script_value.h"
#include "third_party/blink/renderer/bindings/core/v8/serialization/transferables.h"
#include "third_party/blink/renderer/core/execution_context/context_lifecycle_observer.h"
#include "third_party/blink/renderer/core/dom/events/event_target.h"
#include "third_party/blink/renderer/core/event_type_names.h"

#include "third_party/blink/renderer/platform/heap/handle.h"
#include "third_party/blink/renderer/platform/wtf/assertions.h"
#include "third_party/blink/renderer/platform/wtf/forward.h"
#include "third_party/blink/renderer/platform/wtf/uuid.h"

#define IPC_CLR_CONTROL_CREARED							20200220
#define IPC_CLR_CONTROL_CREARED_ID						_T("Tangram_CLR_Control_Created")
#define IPC_NODE_CREARED								20200221
#define IPC_NODE_CREARED_ID								_T("Tangram_WndNode_Created")
#define IPC_NODE_ONMOUSEACTIVATE						20200222
#define IPC_NODE_ONMOUSEACTIVATE_ID						_T("Tangram_WndNode_OnMouseActivate")
#define IPC_WINFORM_TREEVIEW_NODE_ONAFTERSELECT			20200223
#define IPC_WINFORM_TREEVIEW_NODE_ONAFTERSELECT_ID		_T("WinForm_TreeView_Node_OnAfterSelect")
#define IPC_MDIWINFORM_ACTIVEMDICHILD					20200224
#define IPC_MDIWINFORM_ACTIVEMDICHILD_ID				_T("MdiWinForm_ActiveMdiChild")
#define IPC_BIND_CLR_CTRL_EVENT							20200225
#define IPC_BIND_CLR_CTRL_EVENT_ID						_T("BIND_CLR_CTRL_EVENT")
#define IPC_BUTTON_CLICK_EVENT							20200226
#define IPC_BUTTON_CLICK_EVENT_ID						_T("WINFORM_BUTTON_CLICK")
#define IPC_TANGRAM_CREATE_WIN_FORM_MESSAGE				20200227
#define IPC_TANGRAM_CREATE_WIN_FORM_MESSAGE_ID			_T("TANGRAM_CREATE_WIN_FORM_MESSAGE")
#define IPC_TANGRAM_CREATE_TANGRAM_WINDOW_MESSAGE		20200228
#define IPC_TANGRAM_CREATE_TANGRAM_WINDOW_MESSAGE_ID	_T("IPC_TANGRAM_CREATE_TANGRAM_WINDOW_MESSAGE")
#define CREATE_CHILD_TANGRAM_NODE               		20200229
#define CREATE_CHILD_TANGRAM_NODE_ID	                _T("CREATE_CHILD_TANGRAM_NODE")

namespace blink {

	using namespace std;
	class Element;
	class LocalFrame;
	class ExceptionState;
	class Document;
	class ScriptState;
	class SerializedScriptValue;
	class V8GeneralCallback;
	class TangramNode;
	class TangramWindow;
	class TangramWinform;
	class TangramCompositor;
	class WebLocalFrameClient;

	class CORE_EXPORT Tangram final : public EventTargetWithInlineData,
		public DOMWindowClient{
DEFINE_WRAPPERTYPEINFO();
USING_GARBAGE_COLLECTED_MIXIN(Tangram);

public:
 static Tangram* Create(LocalFrame* frame) { return MakeGarbageCollected<Tangram>(frame); }
 static bool CanTransferArrayBuffersAndImageBitmaps() { return true; }

 void Trace(blink::Visitor*) override;

 // Called when an event listener has been successfully added.
 void AddedEventListener(const AtomicString& event_type,
						 RegisteredEventListener&) override;

 DEFINE_ATTRIBUTE_EVENT_LISTENER(MessageReceived, kTangram)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(MdiChildActivate, kMdichildactivate)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(NodeMouseActivate, kNodemouseactivate)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(TangramNodeCreated, kTangramnodecreated)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(TangramWindowCreated, kTangramwindowcreated)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(TreeViewNodeAfterSelect, kTreeviewnodeafterselect)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(TreeViewNodeMouseDoubleClick, kTreeviewnodemousedoubleclick)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(ListViewItemSelectionChanged, kListviewitemselectionchanged)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(FormMenuItemClick, kFormmenuitemclick)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(FormButtonClick, kFormbuttonclick)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(WinFormCreated, kWinformcreated)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(WinFormClosed, kWinformclosed)
 DEFINE_ATTRIBUTE_EVENT_LISTENER(BindCLRCtrlEvent, kBindclrctrlevent)

	 // User level message

	 void addChannel(const String& channel);
	 void removeChannel(const String& channel);
	 void sendMessage(const String& id, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5);
	 void sendNodeMessage(const String& domid, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5);

	 // DOM method

	 void defineElement(const String& tagName, const String& html);
	 void renderElement(const String& tagName, const String& html);

	 void setVal(const String& strKey, const String& val);
	 String getVal(const String& strKey);
	 void clearData();

	 //Control Bind API:
	 void setControlVal(const String& CtrlID, long CtrlHandle, const String& strVal);
	 void BindControlEvent(const String& CtrlID, long CtrlHandle, long EventID, const String& strBindID);
	 TangramWinform* createWinForm(const String& strFormXml, const long FormType);

	 //TangramNode API
	 TangramNode* createTangramNode(const long nHandle, const String& strNodeName, const long nPHandle, const long nWndHandle);
	 TangramNode* getNode(const String& nodeName);
	 TangramNode* getNode(const long nodeHandle);

	 TangramWindow* createTangramWindow(const long nHandle, const String& strWndName);
	 TangramWindow* getWindow(const String& wndName);
	 TangramWindow* getWindow(const long wndHandle);
	 // Non-js method

	 void waitMessage();
	 void releaseMessage();

	 // EventTarget overrides:
	 const AtomicString& InterfaceName() const override;
	 ExecutionContext* GetExecutionContext() const override;

	 explicit Tangram(LocalFrame*);
	 ~Tangram() override;

	 WebLocalFrameClient* web_local_frame_client;
	 HeapHashMap<long, Member<TangramNode>> m_mapTangramNode;
	 HeapHashMap<long, Member<TangramWindow>> m_mapTangramWindow;
	 HeapHashMap<String, Member<TangramWindow>> m_mapTangramWindow2;
	 HeapHashMap<String, Member<TangramNode>> m_mapTangramNode2;
	 HeapHashMap<long, Member<TangramWinform>> m_mapWinForm;
	 HeapHashMap<long, Member<TangramCompositor>> m_mapTangramCompositor;
   private:
	   bool is_pending_;
	   Vector<String> pending_messages_;
	   map<std::wstring, String> m_mapVal;
	};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_TANGRAM_H_
		// end Add by TangramTeam
