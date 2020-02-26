// begin Add by TangramTeam
#include "tangram.h"
#include "tangram_node.h"
#include "tangram_event.h"
#include "tangram_winform.h"
#include "tangram_window.h"
#include "tangram_control.h"
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

TangramNode::TangramNode(LocalFrame* frame) : DOMWindowClient(frame) {
	web_local_frame_client = nullptr;
}

TangramNode::~TangramNode() {
}

TangramNode* TangramNode::Create(LocalFrame* frame, const String& strNodeName) {
	return MakeGarbageCollected<TangramNode>(frame, strNodeName);
}

TangramNode::TangramNode(LocalFrame* frame, const String& strNodeName) : DOMWindowClient(frame)
{
	name_ = strNodeName;
}

String TangramNode::name() {
	return name_;
}

long TangramNode::row()
{
	return row_;
}

long TangramNode::col()
{
	return col_;
}

long TangramNode::rows()
{
	return rows_;
}

long TangramNode::cols()
{
	return cols_;
}

TangramWindow* TangramNode::parentWindow()
{
	return m_pParentWnd;
}

TangramWinform* TangramNode::parentForm()
{
	return m_pParentForm;
}

TangramNode* TangramNode::getChild(long nIndex)
{
	auto it = m_mapChildNode.find(nIndex);
	if (it != m_mapChildNode.end())
		return it->value;
	return nullptr;
}

TangramNode* TangramNode::getChild(const String& strName)
{
	auto it = m_mapChildNode2.find(strName);
	if (it != m_mapChildNode2.end())
		return it->value;
	return nullptr;
}

TangramControl* TangramNode::getControl(const String& strCtrlName)
{
	auto it = m_mapChildControl2.find(strCtrlName);
	if (it != m_mapChildControl2.end())
		return it->value;
	return nullptr;
}

void TangramNode::setVal(const String& strKey, const String& val)
{
	WebString webstr = strKey;
	auto it = m_mapVal.find(webstr.Utf16());
	if (it != m_mapVal.end())
	{
		m_mapVal.erase(it);
	}
	m_mapVal[webstr.Utf16()] = val;
}

String TangramNode::getVal(const String& strKey)
{
	WebString webstr = strKey;
	auto it = m_mapVal.find(webstr.Utf16());
	if (it != m_mapVal.end())
	{
		return it->second;
	}
	return "";
}

void TangramNode::clearData()
{
	m_mapVal.erase(m_mapVal.begin(), m_mapVal.end());
}

void TangramNode::Trace(blink::Visitor* visitor) {
  EventTargetWithInlineData::Trace(visitor);
  ScriptWrappable::Trace(visitor);
  DOMWindowClient::Trace(visitor);
  visitor->Trace(m_pParentWnd);
  visitor->Trace(m_pParentForm);
  visitor->Trace(m_mapChildControl);
  visitor->Trace(m_mapChildControl2);
  visitor->Trace(m_mapChildNode);
  visitor->Trace(m_mapChildNode2);
}


void TangramNode::setControlVal(const String& CtrlID, long CtrlHandle, const String& strVal)
{
	long nHandle = 0;
	if (CtrlID != "")
	{
		Element* const tangramelement = DomWindow()->document()->getElementById(WTF::AtomicString(CtrlID));
		if (tangramelement)
		{
			WTF::AtomicString handle = tangramelement->getAttribute("hwnd");
			if (handle != "")
			{
				WebString webstr = handle;
				std::wstring u16_handle = webstr.Utf16();
				nHandle = _wtoi(u16_handle.c_str());
			}
		}
	}
	else
		nHandle = CtrlHandle;
	if (nHandle)
	{
		if (web_local_frame_client) {
			WebString webstr = strVal;
			std::wstring _val = webstr.Utf16();
			webstr = CtrlID;
			std::wstring _strCtrlID = webstr.Utf16();
			web_local_frame_client->SendTangramMessage(L"TANGRAM_CTRL_VALUE_MESSAGE", _strCtrlID, nHandle, 0, _val, L"");
		}
	}
}

void TangramNode::BindControlEvent(const String& CtrlID, long CtrlHandle, long EventID, const String& strBindID)
{
	long nHandle = 0;
	if (CtrlID != "")
	{
		Element* const tangramelement = DomWindow()->document()->getElementById(WTF::AtomicString(CtrlID));
		if (tangramelement)
		{
			WTF::AtomicString handle = tangramelement->getAttribute("hwnd");
			if (handle != "")
			{
				WebString webstr = handle;
				std::wstring u16_handle = webstr.Utf16();
				nHandle = _wtoi(u16_handle.c_str());
			}
		}
	}
	else
		nHandle = CtrlHandle;
	if (nHandle)
	{
		WebLocalFrameImpl* web_local_frame_impl = WebLocalFrameImpl::FromFrame(GetFrame());
		if (web_local_frame_impl != nullptr) {
			WebLocalFrameClient* web_local_frame_client = web_local_frame_impl->Client();
			if (web_local_frame_client) {
				WebString webstr = strBindID;
				std::wstring _strBindID = webstr.Utf16();
				webstr = CtrlID;
				std::wstring _strCtrlID = webstr.Utf16();
				web_local_frame_client->SendTangramMessage(L"TANGRAM_CTRL_BIND_MESSAGE", _strCtrlID, nHandle, EventID, _strBindID, L"");
			}
		}
	}
}

void TangramNode::AddedEventListener(const AtomicString& event_type,
                                 RegisteredEventListener& registered_listener) {
  EventTargetWithInlineData::AddedEventListener(event_type,
                                                registered_listener);
}

void TangramNode::addChannel(const String& channel) {
	sendMessage(L"ADD_CHANNEL", channel, L"", L"", L"", L"");
}

void TangramNode::removeChannel(const String& channel) {
	sendMessage(L"REMOVE_CHANNEL", channel, L"", L"", L"", L"");
}

void TangramNode::sendMessage(const String& id, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5) {
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

long TangramNode::nodehandle() {
	return nodehandle_;
}

TangramNode* TangramNode::AddChild(long nHandle, const String& strNodeName, blink::Tangram* pTangram)
{
	TangramNode* node = nullptr;
	auto it = pTangram->m_mapTangramNode.find(nHandle);
	if (it != pTangram->m_mapTangramNode.end())
	{
		node = it->value;
		int nSize = m_mapChildNode.size();
		m_mapChildNode.insert(nSize, node);
	}
	return node;
}

TangramControl* TangramNode::AddCtrl(long nCtrlHandle, const String& strCtrlName, const String& strWebPageID, blink::Tangram*)
{
	TangramControl* ctrl = nullptr;
	auto it = m_mapChildControl.find(nCtrlHandle);
	if (it == m_mapChildControl.end())
	{
		ctrl = TangramControl::Create(DomWindow()->GetFrame(), strCtrlName);
		ctrl->ctrlhandle_ = nCtrlHandle;
		ctrl->name_ = strCtrlName;
		ctrl->webpageid_ = strWebPageID;
		m_mapChildControl.insert(nCtrlHandle,ctrl);
		m_mapChildControl2.insert(strCtrlName, ctrl);
		DispatchEvent(*blink::TangramEvent::Create(
			blink::event_type_names::kTangramcontrolcreated, strCtrlName, L"",
			L"", L"", L"", L"", nCtrlHandle, nodehandle_));
	}
	return ctrl;
}

const AtomicString& TangramNode::InterfaceName() const {
  return event_target_names::kTangramNode;
}

ExecutionContext* TangramNode::GetExecutionContext() const {
  return DomWindow()->document();
}

}  // namespace blink
// end Add by TangramTeam
