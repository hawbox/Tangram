// begin Add by TangramTeam
#include "tangram.h"
#include "tangram_node.h"
#include "tangram_event.h"
#include "tangram_window.h"
#include "tangram_winform.h"
#include "tangram_compositor.h"
#include <stdlib.h>
#include <string>
#include <iostream>

#include "base/guid.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/html/html_element.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/public/web/web_local_frame_client.h"
#include "third_party/blink/renderer/core/frame/web_local_frame_impl.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_general_callback.h"

using namespace std;

namespace blink {

Tangram::Tangram(LocalFrame* frame) : DOMWindowClient(frame) {
	is_pending_ = false;
	web_local_frame_client = nullptr;
}

Tangram::~Tangram() {
	clearData();
}

void Tangram::Trace(blink::Visitor* visitor) {
  EventTargetWithInlineData::Trace(visitor);
  ScriptWrappable::Trace(visitor);
  DOMWindowClient::Trace(visitor);
  visitor->Trace(m_mapTangramNode);
  visitor->Trace(m_mapTangramWindow);
  visitor->Trace(m_mapTangramWindow2);
  visitor->Trace(m_mapTangramNode2);
  visitor->Trace(m_mapWinForm);
  visitor->Trace(m_mapTangramCompositor);
}

void Tangram::AddedEventListener(const AtomicString& event_type,
                                 RegisteredEventListener& registered_listener) {
  EventTargetWithInlineData::AddedEventListener(event_type,
                                                registered_listener);
}

// User level message
void Tangram::addChannel(const String& channel) {
	sendMessage(L"ADD_CHANNEL", channel, L"", L"", L"", L"");
}

void Tangram::removeChannel(const String& channel) {
	sendMessage(L"REMOVE_CHANNEL", channel, L"", L"", L"", L"");
}

void Tangram::sendMessage(const String& id, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5) {
	if (web_local_frame_client) {
		if (is_pending_) {
			String message = id + "%%%" + param1 + "%%%" + param2 + "%%%" + param3 + "%%%" + param4 + "%%%" + param5;
			pending_messages_.push_back(message);
		}
		else {
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

void Tangram::sendNodeMessage(const String& id, const String& param1, const String& param2, const String& param3, const String& param4, const String& param5) {
	Element* const tangramelement = DomWindow()->document()->getElementById(WTF::AtomicString(id));
	if (tangramelement&&web_local_frame_client) {
		WebString webstr = id;
		wstring u16_id = webstr.Utf16();
		WTF::AtomicString handle = tangramelement->getAttribute("hwnd");
		webstr = handle;
		wstring u16_handle = webstr.Utf16();
		webstr = param2;
		wstring u16_param2 = webstr.Utf16();
		webstr = param3;
		std::wstring u16_param3 = webstr.Utf16();
		webstr = param4;
		std::wstring u16_param4 = webstr.Utf16();
		//webstr = param5;
		//std::wstring u16_param5 = webstr.Utf16();
		web_local_frame_client->SendTangramMessage(L"TANGRAM_NODE_MESSAGE", u16_id, u16_handle, u16_param2, u16_param3, u16_param4);
	}
}

// Define a element
void Tangram::defineElement(const String& tagName, const String& html) {
	sendMessage(L"DEFINE_ELEMENT", tagName, html, L"", L"", L"");
}

// Render an element.
void Tangram::renderElement(const String& tagName, const String& html) {
	sendMessage(L"RENDER_ELEMENT", tagName, html, L"", L"", L"");
}

void Tangram::waitMessage() {
	is_pending_ = true;
}

void Tangram::releaseMessage() {
	is_pending_ = false;
	if (web_local_frame_client) {
		if (pending_messages_.size() > 0) {
			String stringBuffer = "";
			for (wtf_size_t i = 0; i < pending_messages_.size(); i++) {
				if (i > 0) {
					stringBuffer = stringBuffer + "$$$";
				}
				stringBuffer = stringBuffer + pending_messages_[i];
			}
			WebString bundle = stringBuffer;
			std::wstring type = L"AGGREGATED_MESSAGE";
			std::wstring param1 = bundle.Utf16();
			web_local_frame_client->SendTangramMessage(type, param1, L"", L"", L"", L"");
			pending_messages_.clear();
		}
	}
}

void Tangram::setVal(const String& strKey, const String& val)
{
	WebString webstr = strKey;
	auto it = m_mapVal.find(webstr.Utf16());
	if (it != m_mapVal.end())
	{
		m_mapVal.erase(it);
	}
	m_mapVal[webstr.Utf16()] = val;
}

String Tangram::getVal(const String& strKey)
{
	WebString webstr = strKey;
	auto it = m_mapVal.find(webstr.Utf16());
	if (it != m_mapVal.end())
	{
		return it->second;
	}
	return "";
}

void Tangram::clearData()
{
	m_mapVal.erase(m_mapVal.begin(), m_mapVal.end());
}

void Tangram::setControlVal(const String& CtrlID, long CtrlHandle, const String& strVal)
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

void Tangram::BindControlEvent(const String& CtrlID, long CtrlHandle, long EventID, const String& strBindID)
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
			WebString webstr = strBindID;
			std::wstring _strBindID = webstr.Utf16();
			webstr = CtrlID;
			std::wstring _strCtrlID = webstr.Utf16();
			web_local_frame_client->SendTangramMessage(L"TANGRAM_CTRL_BIND_MESSAGE", _strCtrlID, nHandle, EventID, _strBindID, L"");
		}
	}
}

TangramWinform* Tangram::createWinForm(const String& strFormXml, const long FormType)
{
	TangramWinform* form = TangramWinform::Create(DomWindow()->GetFrame(), strFormXml); 
	form->nHandle = (long)form;
	form->web_local_frame_client = web_local_frame_client;
	m_mapWinForm.insert(form->nHandle, form);
	if (web_local_frame_client) {
		WebString webstr = strFormXml;
		std::wstring _strFormXml = webstr.Utf16();
		web_local_frame_client->SendTangramMessage(L"TANGRAM_CREATE_WIN_FORM_MESSAGE", _strFormXml, form->nHandle, FormType, L"", L"");
	}
	return form;
}

TangramNode* Tangram::createTangramNode(const long nHandle, const String& strNodeName, const long nPHandle, const long nWndHandle)
{
	TangramNode* node = TangramNode::Create(DomWindow()->GetFrame(), strNodeName);
	node->nHandle = nHandle;
	node->web_local_frame_client = web_local_frame_client;
	m_mapTangramNode.insert(nHandle,node);
	m_mapTangramNode2.insert(strNodeName, node);
	if (nPHandle)
	{
		auto it = m_mapTangramNode.find(nPHandle);
		if (it != m_mapTangramNode.end())
		{
			//int nSize = it->value->m_mapChildNode.size();
			//it->value->m_mapChildNode.insert(nSize, node);
			it->value->m_mapChildNode2.insert(strNodeName, node);
			if (nWndHandle)
			{
				auto it1 = m_mapTangramWindow.find(nWndHandle);
				if (it1 != m_mapTangramWindow.end())
				{
					blink::TangramWindow* window = it1->value;
					if (window)
					{
						window->m_mapTangramNode.insert(nHandle, node);
						window->m_mapTangramNode2.insert(strNodeName, node);
						if (window)
							window->DispatchEvent(*blink::TangramEvent::Create(
								blink::event_type_names::kTangramnodecreated, String(L"CREATE_CHILD_TANGRAM_NODE"), 
								strNodeName,
								nHandle, 
								it->value->name(), 
								nPHandle,
								String(L"wndnode")));

					}
				}
			}
		}
	}


	return node;
}

TangramWindow* Tangram::createTangramWindow(const long nHandle, const String& strWndName)
{
	TangramWindow* window = TangramWindow::Create(DomWindow()->GetFrame(), strWndName);
	window->windowhandle_ = nHandle;
	window->web_local_frame_client = web_local_frame_client;
	m_mapTangramWindow.insert(nHandle, window);
	m_mapTangramWindow2.insert(strWndName, window);

	//window->m_pHostNode = TangramNode::Create(DomWindow()->GetFrame(), strWndName);
	//window->m_pHostNode->nHandle = nHandle;
	//window->m_pHostNode->web_local_frame_client = web_local_frame_client;
	//m_mapTangramNode[nHandle] = window->m_pHostNode;
	//m_mapTangramNode2[webstr.Utf16()] = window->m_pHostNode;


	//wstring s = L"xxx|123|yyy";
	//std::wstringstream ss;
	//ss.str(s);
	//std::vector<std::wstring> elems;
	//std::wstring item;
	//while (std::getline(ss, item, L'|')) {
	//	elems.push_back(item);
	//}

	return window;
}

TangramNode* Tangram::getNode(const String& nodeName)
{
	auto it = m_mapTangramNode2.find(nodeName);
	if (it != m_mapTangramNode2.end())
		return it->value;
	return nullptr;
}

TangramNode* Tangram::getNode(const long nodeHandle)
{
	auto it = m_mapTangramNode.find(nodeHandle);
	if (it != m_mapTangramNode.end())
		return it->value;
	return nullptr;
}

TangramWindow* Tangram::getWindow(const String& wndName)
{
	auto it = m_mapTangramWindow2.find(wndName);
	if (it != m_mapTangramWindow2.end())
		return it->value;
	return nullptr;
}

TangramWindow* Tangram::getWindow(const long wndHandle)
{
	auto it = m_mapTangramWindow.find(wndHandle);
	if (it != m_mapTangramWindow.end())
		return it->value;
	return nullptr;
}

const AtomicString& Tangram::InterfaceName() const {
  return event_target_names::kTangram;
}

ExecutionContext* Tangram::GetExecutionContext() const {
  return DomWindow()->document();
}

}  // namespace blink
   // end Add by TangramTeam
