// begin Add by TangramTeam
#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_TANGRAM_EVENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_TANGRAM_EVENT_H_

#include "third_party/blink/renderer/core/dom/events/Event.h"

namespace blink {

  class ScriptState;

  class CORE_EXPORT TangramEvent : public Event {
    DEFINE_WRAPPERTYPEINFO();

  public:
    static TangramEvent* Create() { return MakeGarbageCollected<TangramEvent>(); }

    static TangramEvent* Create(const AtomicString& event_type,
      const String& eventId,
      const String& param1,
      const String& param2,
      const String& param3,
      const String& param4,
      const String& param5,
      const long handleSource,
      const long handleTarget);

    static TangramEvent* Create(const AtomicString& event_type,
      const String& eventId,
      const String& param1,
      const long handleSource,
      const String& param3,
      const long handleTarget,
      const String& param5);

    String eventId();
    void setEventId(const String&);
    String param1();
    void setParam1(const String&);
    String param2();
    void setParam2(const String&);
    String param3();
    void setParam3(const String&);
    String param4();
    void setParam4(const String&);
    String param5();
    void setParam5(const String&);

    long handleSource();
    void setHandleSource(const long);
    long handleTarget();
    void setHandleTarget(const long);

    ~TangramEvent() override;

    TangramEvent();

    TangramEvent(const AtomicString& event_type,
      const String& eventId,
      const String& param1,
      const String& param2,
      const String& param3,
      const String& param4,
      const String& param5,
      const long handleSource,
      const long handleTarget);

  private:
    String eventId_;
    String param1_;
    String param2_;
    String param3_;
    String param4_;
    String param5_;
    long handleSource_;
    long handleTarget_;
  };

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_PROGRESS_EVENT_H_
// end Add by TangramTeam
