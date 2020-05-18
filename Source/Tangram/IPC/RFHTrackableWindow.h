#pragma once

#include <map>
#include "../CommonFile/Messages.h"
#include "Broker.h"
#include "../CommonFile/IGui.h"

namespace IPC
{
    class RFHTrackableWindow : 
        public CWindowImpl<RFHTrackableWindow, CWindow>, 
        public Broker
    {
    public:
        RFHTrackableWindow();
        virtual ~RFHTrackableWindow();

        BEGIN_MSG_MAP(RFHTrackableWindow)
            MESSAGE_HANDLER(WM_TRACKABLEWINDOWCLIENTMSG, OnCustomMessageReceived)
            MESSAGE_HANDLER(WM_TRACKABLEWINDOWEDMSG, OnCustomMessageEnded)
        END_MSG_MAP()

        void OnFinalMessage(HWND hwnd);
    private:
        std::map<std::string, Gui::IDocument*> m_mapDocuments;

        LRESULT OnCustomMessageReceived(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&);
        LRESULT OnCustomMessageEnded(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&);
    };
}