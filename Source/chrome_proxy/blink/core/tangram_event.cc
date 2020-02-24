// begin Add by TangramTeam
#include "tangram_event.h"

namespace blink {

  TangramEvent* TangramEvent::Create(const AtomicString& event_type,
    const String& eventId,
    const String& param1,
    const String& param2,
    const String& param3,
    const String& param4,
    const String& param5,
    const long handleSource, 
    const long handleTarget) {
      return MakeGarbageCollected<TangramEvent>(event_type, eventId, param1, param2, param3, param4, param5, handleSource, handleTarget);
  }

  TangramEvent* TangramEvent::Create(const AtomicString& event_type,
    const String& eventId,
    const String& param1,
    const long handleSource,
    const String& param3,
    const long handleTarget,
    const String& param5) {
      return MakeGarbageCollected<TangramEvent>(event_type, eventId, param1, "", param3, "", param5, handleSource, handleTarget);
  }

  String TangramEvent::eventId() {
      return eventId_;
  }

  long TangramEvent::handleSource() {
      return handleSource_;
  }

  void TangramEvent::setHandleSource(const long handleSource) {
      handleSource_ = handleSource;
  }

  long TangramEvent::handleTarget() {
      return handleTarget_;
  }

  void TangramEvent::setHandleTarget(const long handleTarget) {
      handleTarget_ = handleTarget;
  }

  void TangramEvent::setEventId(const String& eventId) {
      eventId_ = eventId;
  }

  String TangramEvent::param1() {
      return param1_;
  }

  void TangramEvent::setParam1(const String& param1) {
      param1_ = param1;
  }

  String TangramEvent::param2() {
    return param2_;
  }

  void TangramEvent::setParam2(const String& param2) {
    param2_ = param2;
  }

  String TangramEvent::param3() {
    return param3_;
  }

  void TangramEvent::setParam3(const String& param3) {
    param3_ = param3;
  }

  String TangramEvent::param4() {
    return param4_;
  }

  void TangramEvent::setParam4(const String& param4) {
      param4_ = param4;
  }

  String TangramEvent::param5() {
    return param5_;
  }

  void TangramEvent::setParam5(const String& param5) {
    param5_ = param5;
  }

  TangramEvent::TangramEvent() : Event("", Bubbles::kNo, Cancelable::kNo) {

  }

  TangramEvent::TangramEvent(const AtomicString& event_type,
    const String& eventId,
    const String& param1,
    const String& param2,
    const String& param3,
    const String& param4,
    const String& param5,
    const long handleSource,
    const long handleTarget)
    : Event(event_type, Bubbles::kNo, Cancelable::kNo) {
    eventId_ = eventId;
    param1_ = param1;
    param2_ = param2;
    param3_ = param3;
    param4_ = param4;
    param5_ = param5;
    handleSource_ = handleSource;
    handleTarget_ = handleTarget;
  }

  TangramEvent::~TangramEvent() = default;

}  // namespace blink
// end Add by TangramTeam
