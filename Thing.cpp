#include "arduino.h"
#include "Thing.h"
#include "WebThingAdapter.h"
  
  ThingProperty::ThingProperty(ThingDevice* device, const char* id_, const char* description_, ThingPropertyType type_, const char* atType_):
    id(id_),
    description(description_),
    type(type_),
    atType(atType_) {
      device->addProperty(this);
  }

  ThingDevice::ThingDevice(WebThingAdapter* adapter, const char* _id, const char* _name, const char** _type):
    id(_id),
    name(_name),
    type(_type) {
        adapter->addDevice(this);
  }
