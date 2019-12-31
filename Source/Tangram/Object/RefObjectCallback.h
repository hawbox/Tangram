#pragma once

#include "../CommonFile/IRefObject.h"

namespace RefObject
{
    class RefObject;
    class RefObjectParams;

    class RefObjectCallback : public IRefObjectCallback
    {
    public:
        RefObjectCallback() {};
        ~RefObjectCallback() {};

        // virtual void Invoke(RefObject* pObj, RefObjectParams* pParams) = 0;
    };
}