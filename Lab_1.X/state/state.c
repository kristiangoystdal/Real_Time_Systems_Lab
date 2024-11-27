
#include "state.h"

static Configs _configs;
static SensorsMaxMin _sensorsMaxMin;

void set_configs(Configs configs) {
  _configs = configs;
}

void set_default_configs() {
  
}

Configs get_configs(){
  return _configs;
}

void set_max_min(SensorsMaxMin sensorsMaxMin) {
  _sensorsMaxMin = sensorsMaxMin;
}

SensorsMaxMin get_max_min() {
  return _sensorsMaxMin;
}
