#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"

namespace esphome {
namespace fakelight {

class FakeLight : public light::LightOutput, public Component {
 public:
  FakeLight() = default;

  void setup() override;

  light::LightTraits get_traits() override;

  void write_state(light::LightState *state) override;

  float get_setup_priority() const override { return setup_priority::HARDWARE; }
};

}  // namespace fakelight
}  // namespace esphome
