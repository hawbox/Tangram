#pragma once

#include <string>

namespace TangramCommon {

	class CChromeWebFrameClient {
	public:
		CChromeWebFrameClient() {}

		virtual ~CChromeWebFrameClient() {}

		virtual void SendTangramMessage(std::wstring strId,
			std::wstring strParam1,
			std::wstring strParam2,
			std::wstring strParam3,
			std::wstring strParam4,
			std::wstring strParam5) {}
			
		virtual void SendTangramMessage(std::wstring strId,
			std::wstring strParam1,
			long nHandle,
			long nID,
			std::wstring strParam4,
			std::wstring strParam5) {}
			
		virtual void SendTangramMessage(std::wstring strId,
			std::wstring strParam1,
			long fromhandle,
			std::wstring strParam3,
			long tohandle,
			std::wstring strParam5) {}

		virtual void OnTangramMessage(long messageIndex,
			std::wstring strId,
			std::wstring strParam1,
			std::wstring strParam2,
			std::wstring strParam3,
			std::wstring strParam4,
			std::wstring strParam5) {}

		virtual void OnTangramMessage8(long messageIndex,
			std::wstring strId,
			long NodeHandle,
			std::wstring strParam1,
			std::wstring strParam2,
			std::wstring strParam3,
			std::wstring strParam4,
			std::wstring strParam5) {}

		virtual void OnTangramMessage9(long messageIndex,
			std::wstring strId,
			long NodeHandle,
			std::wstring strParam1,
			std::wstring strParam2,
			std::wstring strParam3,
			std::wstring strParam4,
			std::wstring strParam5,
			std::wstring strParam6) {}

		virtual void OnTangramMessage10(long messageIndex,
			std::wstring strId,
			long NodeHandle,
			std::wstring strParam1,
			std::wstring strParam2,
			std::wstring strParam3,
			std::wstring strParam4,
			std::wstring strParam5,
			std::wstring strParam6,
			std::wstring strParam7) {}
	};

}  // namespace TangramCommon
