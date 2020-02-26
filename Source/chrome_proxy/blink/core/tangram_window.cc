// begin Add by TangramTeam
#include "tangram.h"
#include "tangram_node.h"
#include "tangram_window.h"
#include "tangram_event.h"
#include "tangram_winform.h"
#include "tangram_compositor.h"

#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/html/html_element.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/public/web/web_local_frame_client.h"
#include "third_party/blink/renderer/core/frame/web_local_frame_impl.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_general_callback.h"

namespace blink {

	TangramWindow::TangramWindow(LocalFrame* frame) : DOMWindowClient(frame) {
		web_local_frame_client = nullptr;
	}

	TangramWindow::~TangramWindow() {
	}

	TangramWindow* TangramWindow::Create(LocalFrame* frame, const String& strWindowName) {
		return MakeGarbageCollected<TangramWindow>(frame, strWindowName);
	}

	TangramWindow::TangramWindow(LocalFrame* frame, const String& strWindowName) : DOMWindowClient(frame)
	{
		name_ = strWindowName;
	}

	void TangramWindow::Trace(blink::Visitor* visitor) {
		EventTargetWithInlineData::Trace(visitor);
		ScriptWrappable::Trace(visitor);
		DOMWindowClient::Trace(visitor);
		visitor->Trace(m_pHostNode);
		visitor->Trace(m_mapTangramNode);
		visitor->Trace(m_mapTangramNode2);
	}

	void TangramWindow::AddedEventListener(const AtomicString& event_type,
		RegisteredEventListener& registered_listener) {
		EventTargetWithInlineData::AddedEventListener(event_type,
			registered_listener);
	}

	String TangramWindow::name() {
		return name_;
	}

	long TangramWindow::windowhandle() {
		return windowhandle_;
	}

	TangramNode* TangramWindow::getNode(const String& nodeName)
	{
		auto it = m_mapTangramNode2.find(nodeName);
		if (it != m_mapTangramNode2.end())
			return it->value;
		return nullptr;
	}

	TangramNode* TangramWindow::getNode(const long nodeHandle)
	{
		auto it = m_mapTangramNode.find(nodeHandle);
		if (it != m_mapTangramNode.end())
			return it->value;
		return nullptr;
	}

	void TangramWindow::addChannel(const String& channel) {
	}

	void TangramWindow::removeChannel(const String& channel) {
	}

	void TangramWindow::sendMessage(const String& id, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5) {
		WebLocalFrameImpl* web_local_frame_impl = WebLocalFrameImpl::FromFrame(GetFrame());
		// Null when opening a new tab.
		if (web_local_frame_impl != nullptr) {
			WebLocalFrameClient* web_local_frame_client = web_local_frame_impl->Client();
			if (web_local_frame_client) {
				WebString webstr = id;
				std::wstring u16_id = webstr.Utf16();
				webstr = param1;
				std::wstring u16_param1 = webstr.Utf16();
				webstr = param2;
				std::wstring u16_param2 = webstr.Utf16();
				webstr = param3;
				std::wstring u16_param3 = webstr.Utf16();
				webstr = param4;
				std::wstring u16_param4 = webstr.Utf16();
				webstr = param5;
				std::wstring u16_param5 = webstr.Utf16();
				web_local_frame_client->SendTangramMessage(u16_id, u16_param1, u16_param2, u16_param3, u16_param4, u16_param5);
			}
		}
	}

	const AtomicString& TangramWindow::InterfaceName() const {
		return event_target_names::kTangramWindow;
	}

	ExecutionContext* TangramWindow::GetExecutionContext() const {
		return DomWindow()->document();
	}

}  // namespace blink
// end Add by TangramTeam
