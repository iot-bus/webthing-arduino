/**
 * Thing.h
 *
 * Provides ThingProperty and ThingDevice classes for creating modular Web
 * Things.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef MOZILLA_IOT_THING_H
#define MOZILLA_IOT_THING_H

enum ThingPropertyType {
  BOOLEAN,
  NUMBER,
  STRING
};

union ThingPropertyValue {
  bool boolean;
  double number;
  String* string;
};

class WebThingAdapter;
class ThingDevice;

class ThingProperty {
public:
  String id;
  String description;
  ThingPropertyType type;
  String atType;
  String label = "";
  String unit = "";
  bool writable = true;
  ThingProperty* next = nullptr;

  ThingProperty(const char* id_, const char* description_, ThingPropertyType type_, const char* atType_, const char* label_, const char* unit_, bool writable_):
    id(id_),
    description(description_),
    type(type_),
    atType(atType_),
    label(label_),
    unit(unit_),
    writable(writable_)  {
  }

  ThingProperty(const char* id_, const char* description_, ThingPropertyType type_, const char* atType_, const char* label_, const char* unit_):
    id(id_),
    description(description_),
    type(type_),
    atType(atType_),
    label(label_) {
  }  
  
  ThingProperty(const char* id_, const char* description_, ThingPropertyType type_, const char* atType_):
    id(id_),
    description(description_),
    type(type_),
    atType(atType_) {
  }

  // overloaded to reference device
  ThingProperty(ThingDevice* device, const char* id_, const char* description_, ThingPropertyType type_, const char* atType_);  

  void setValue(ThingPropertyValue newValue) {
    this->value = newValue;
  }

  ThingPropertyValue getValue() {
    return this->value;
  }
  
private:
  ThingPropertyValue value = {false};
};

class ThingDevice {
public:
  String id;
  String name;
  const char** type;
  ThingDevice* next = nullptr;
  ThingProperty* firstProperty = nullptr;
  ThingProperty* lastProperty = nullptr;

  ThingDevice(const char* _id, const char* _name, const char** _type):
    id(_id),
    name(_name),
    type(_type) {
  }

  ThingDevice(WebThingAdapter* adapter, const char* _id, const char* _name, const char** _type);


  void addProperty(ThingProperty* property) {
    if (lastProperty == nullptr) {
      firstProperty = property;
      lastProperty = property;
    } else {
      lastProperty->next = property;
      lastProperty = property;
    }
  }
};

#endif
