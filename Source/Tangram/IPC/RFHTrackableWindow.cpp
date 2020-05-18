#include "../stdafx.h"
#include "RFHTrackableWindow.h"
#include "../json.hpp"
#include "../Gui/Document.h"

// https://github.com/nlohmann/json
using json = nlohmann::json;

namespace IPC
{
    RFHTrackableWindow::RFHTrackableWindow()
    {

    }

    RFHTrackableWindow::~RFHTrackableWindow()
    {
        for (auto it : m_mapDocuments)
        {
            delete it.second;
        }
        m_mapDocuments.clear();
    }

    LRESULT RFHTrackableWindow::OnCustomMessageReceived(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
    {
        LPSTR lpStr = (LPSTR)lParam;
        std::string msg = ParamToString(lpStr);
        json j = json::parse(msg);
        std::string referenceId = j["referenceId"].get<std::string>();
        std::string action = j["action"].get<std::string>();
        if (action == "finish_parsing_children")
        {
            // Create Element
            std::string xcml = j["outerHTML"].get<std::string>();
            int wlen = MultiByteToWideChar(CP_UTF8, 0, xcml.c_str(), xcml.length() + 1, 0, 0);
            wchar_t* lpszXcml = new wchar_t[wlen];
            MultiByteToWideChar(CP_UTF8, 0, xcml.c_str(), xcml.length() + 1, lpszXcml, wlen);
            Gui::IDocument* document = new Gui::Document();
            m_mapDocuments[referenceId] = document;
            document->Load(lpszXcml);
            delete[] lpszXcml;
            document->CreateWnd(NULL);
        }
        else if (action == "attribute_changed")
        {
            // Update Element
            std::string attrName = j["attrName"].get<std::string>();
            std::string newValue = j["newValue"].get<std::string>();
            auto it = m_mapDocuments.find(referenceId);
            if (it != m_mapDocuments.end())
            {
                Gui::INode* rootNode = it->second->GetRoot();
                rootNode->SetAttribute(CString(attrName.c_str()), CString(newValue.c_str()));
            }
        }
        return DefWindowProc(uMsg, wParam, lParam);
    }

    LRESULT RFHTrackableWindow::OnCustomMessageEnded(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&)
    {
        LPSTR lpStr = (LPSTR)lParam;
        delete[] lpStr;
        return DefWindowProc(uMsg, wParam, lParam);
    }

    void RFHTrackableWindow::OnFinalMessage(HWND hwnd)
    {
        CWindowImpl::OnFinalMessage(hwnd);
        delete this;
    }
}
