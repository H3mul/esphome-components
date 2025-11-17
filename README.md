# ESPHome Components

A collection of custom ESPHome components for specialized use cases.

## Components

### FakeLight

A dummy light component that stores an RGB value without controlling any physical hardware. This is useful for scenarios where you need to:

- Store RGB color values in ESPHome
- Create virtual lights that sync with external services
- Maintain light state for automation logic without physical output
- Use as a configuration value holder in your ESPHome setup

#### Features

- Stores RGB color state
- Supports full light configuration options
- No physical LED control
- Perfect for use as a virtual light entity in Home Assistant

#### Configuration

```yaml
light:
  - platform: fakelight
    name: "Light Name"
    id: light_id
    restore_mode: RESTORE_DEFAULT_OFF
    entity_category: config
```

#### Parameters

- **name** (Required): Name of the light
- **id** (Required): ESPHome ID for the light
- **restore_mode** (Optional): How to restore the light state on boot. Default is `RESTORE_DEFAULT_OFF`
- **entity_category** (Optional): Entity category for Home Assistant (e.g., `config`, `diagnostic`)

#### Example Use Case

Store an RGB color value that can be used for dynamic lighting effects or audio-reactive visualizations:

```yaml
light:
  - platform: fakelight
    name: "Max Sound Color"
    id: max_sound_color
    restore_mode: RESTORE_DEFAULT_OFF
    entity_category: config
```

## Installation

Copy the `components/` directory into your ESPHome configuration:

```
esphome/
  config_name.yaml
  components/
    fakelight/
```

Then reference the component in your configuration using `platform: fakelight`.

## Usage

Once installed, use the component like any other ESPHome light:

```yaml
light:
  - platform: fakelight
    name: "My Fake Light"
    id: my_fake_light
```

The light can be controlled via Home Assistant or any ESPHome automations/scripts.

### Using FakeLight in Lambdas

The FakeLight component can be referenced in lambda expressions to retrieve and use its current RGB color values. This is useful for:

- Syncing physical LED effects with virtual light colors
- Audio-reactive lighting systems
- Color-based automations and conditions

#### Example: Custom Effect with FakeLight Color

```yaml
light:
  - platform: fakelight
    name: "Accent Color"
    id: accent_color
    restore_mode: RESTORE_DEFAULT_OFF

  - platform: neopixel
    pin: GPIO5
    num_leds: 30
    name: "Status LED"
    effects:
      - lambda:
          name: "Accent Color Effect"
          update_interval: 50ms
          lambda: |-
            auto accent = id(accent_color)->current_values;
            auto r = (uint8_t)(accent.get_red() * 255.0f);
            auto g = (uint8_t)(accent.get_green() * 255.0f);
            auto b = (uint8_t)(accent.get_blue() * 255.0f);
            
            for (int i = 0; i < it.size(); i++) {
              it[i].set_rgb(r, g, b);
            }
            it.schedule_show();
```

In this example:
- The FakeLight `accent_color` stores an RGB value that can be controlled from Home Assistant
- A NeoPixel LED strip uses a custom lambda effect to read the FakeLight color
- The lambda applies the color to all LEDs in the strip
- The effect updates every 50ms to reflect any color changes
