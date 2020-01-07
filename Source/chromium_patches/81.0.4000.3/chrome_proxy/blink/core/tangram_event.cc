// begin Add by TangramTeam
#include "tangram_event.h"

namespace blink {

  TangramEvent* TangramEvent::Create(const AtomicString& event_type,
    const String& from,
    const String& to,
    const String& msgId,
    const String& payload,
    const String& extra) {
    return MakeGarbageCollected<TangramEvent>(event_type, from, to, msgId, payload, extra);
  }

  String TangramEvent::from() {
    return from_;
  }

  void TangramEvent::setFrom(const String& from) {
    from_ = from;
  }

  String TangramEvent::to() {
    return to_;
  }

  void TangramEvent::setTo(const String& to) {
    to_ = to;
  }

  String TangramEvent::msgId() {
    return msgId_;
  }

  void TangramEvent::setMsgId(const String& msgId) {
    msgId_ = msgId;
  }

  String TangramEvent::payload() {
    return payload_;
  }

  void TangramEvent::setPayload(const String& payload) {
      payload_ = payload;
  }

  String TangramEvent::extra() {
    return extra_;
  }

  void TangramEvent::setExtra(const String& extra) {
    extra_ = extra;
  }

  TangramEvent::TangramEvent() : Event("", Bubbles::kNo, Cancelable::kNo) {

  }

  TangramEvent::TangramEvent(const AtomicString& event_type,
    const String& from,
    const String& to,
    const String& msgId,
    const String& payload,
    const String& extra)
    : Event(event_type, Bubbles::kNo, Cancelable::kNo) {
    from_ = from;
    to_ = to;
    msgId_ = msgId;
    payload_ = payload;
    extra_ = extra;
  }

  TangramEvent::~TangramEvent() = default;

}  // namespace blink
// end Add by TangramTeam
