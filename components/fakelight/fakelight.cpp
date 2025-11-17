#include "fakelight.h"
#include "esphome/core/log.h"

namespace esphome {
namespace fakelight {

static const char *const TAG = "fakelight";

void FakeLight::setup() {
  ESP_LOGI(TAG, "FakeLight component initialized - stores RGB values only");
}

light::LightTraits FakeLight::get_traits() {
  auto traits = light::LightTraits();
  traits.set_supported_color_modes({light::ColorMode::RGB});
  traits.set_min_mireds(0);
  traits.set_max_mireds(0);
  return traits;
}

void FakeLight::write_state(light::LightState *state) {
  // This component does nothing - it just stores the RGB value
  // The RGB values can be read via state->current_values
  
  float red, green, blue;
  state->current_values.as_rgb(&red, &green, &blue);
  
  ESP_LOGD(TAG, "FakeLight updated - RGB: %.2f, %.2f, %.2f", red, green, blue);
}

}  // namespace fakelight
}  // namespace esphome
