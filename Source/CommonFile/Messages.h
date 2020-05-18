#pragma once

#define WM_TRACKABLEWINDOWCREATED (WM_USER + 0x00001000)
#define WM_TRACKABLEWINDOWMSG (WM_USER + 0x00001001)
#define WM_TRACKABLEWINDOWEDMSG (WM_USER + 0x00001002)
#define WM_TRACKABLEWINDOWCLIENTMSG (WM_USER + 0x00001003)
#define WM_TRACKABLEWINDOWCLIENTEDMSG (WM_USER + 0x00001004)

static LPSTR ParamFromString(std::string str)
{
    LPSTR lpStr = new char[str.length() + 1];
    strcpy(lpStr, str.c_str());
    return lpStr;
}

static std::string ParamToString(LPSTR lpStr)
{
    std::string str(lpStr);
    return str;
}