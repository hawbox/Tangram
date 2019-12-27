// begin Add by TangramTeam
#include "tangram_event.h"

namespace blink {

  TangramEvent* TangramEvent::Create(const AtomicString& event_type,
    const String& from,
    const String& to,
    const String& msgid,
    const String& payload,
    const String& extra) {
    return MakeGarbageCollected<TangramEvent>(event_type, from, to, msgid, payload, extra);
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

  String TangramEvent::msgid() {
    return msgid_;
  }

  void TangramEvent::setMsgid(const String& msgid) {
    msgid_ = msgid;
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
    const String& msgid,
    const String& payload,
    const String& extra)
    : Event(event_type, Bubbles::kNo, Cancelable::kNo) {
    from_ = from;
    to_ = to;
    msgid_ = msgid;
    payload_ = payload;
    extra_ = extra;
  }

  TangramEvent::~TangramEvent() = default;

}  // namespace blink
// end Add by TangramTeam
