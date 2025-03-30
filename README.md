# Easy Preferences

[![PlatformIO](https://github.com/hpsaturn/easy-preferences/workflows/PlatformIO/badge.svg)](https://github.com/hpsaturn/easy-preferences/actions/) [![All Platforms](https://github.com/hpsaturn/easy-preferences/workflows/Scheduled/badge.svg)](https://github.com/hpsaturn/easy-preferences/actions/) ![ViewCount](https://views.whatilearened.today/views/github/hpsaturn/easy-preferences.svg)  

ESP32 Preferences abstraction and manager with enhanced key-value capabilities. It includes a basic keys manifest and auto setters to streamline implementation.

## Usage

### Configuration

Define in your project in the libraries directory, a new local library, and it  should be contain a header `preferences-key.h`, that contains your custom preferences keys and its key value and key type, like this:

```cpp
#define CONFIG_KEYS_LIST                 \
  X(KMAP_SPEED, "Map_speed", BOOL)       \
  X(KMAP_SCALE, "Map_scale", BOOL)       \
  X(KMAP_COMPASS, "Map_compass", BOOL)   \
  X(KCOMP_X, "Compass_X", INT)           \
  X(KCOMP_Y, "Compass_Y", INT)           \
  X(KSPEED_X, "Speed_X", INT)            \
  X(KSPEED_Y, "Speed_Y", INT)            \
  X(KCOUNT, "KCOUNT", UNKNOWN)
```

A possible directory structure for your preferences header could be:

```bash
└── your_project
    ├── lib
    │   └── preferences
    │       └── preferences-keys.h
    └── src
        └── main.cpp
```

### Methods access

You are able to use a basic methods for different types from a global instance called `cfg`, something like this:

```cpp
#include <EasyPreferences.hpp>

void saveShowCompass(bool showCompass)
{
    cfg.saveBool(PKEYS::KMAP_COMPASS, showCompass);
}

void saveGPSBaud(uint16_t gpsBaud)
{
    cfg.saveShort(PKEYS::KGPS_SPEED, gpsBaud);
}

void setup ()
{
    cfg.init("MyMapApp");
}
```

## Auto type selection

Also you are able to use some Auto calls, that they knows what do with each preference:

```cpp
cfg.saveAuto(PKEYS::KMYSTR, "abcdeABCDE1234_-@()***[]'");
cfg.saveAuto(PKEYS::KMBOOL, "false");
```

## Preferences iterator

Also is possible iterate over all preferences to get all values:

```cpp
for (int i = 0; i < KCOUNT; i++) {
    String key = cfg.getKey((PKEYS)i);
    bool isDefined = cfg.isKey(key);
    String defined = isDefined ? "custom " : "default";
    String value = "";
    if (isDefined) value = cfg.getValue(key);
    Serial.printf("%11s \t%s \t%s \r\n", key.c_str(), defined.c_str(), value.c_str());
}
```

And you should have an ouput similar to:

```bash
     KEYNAME       DEFINED         VALUE
     =======       =======         =====
     Map_rot       custom          false
   Map_speed       custom          true
   Map_scale       custom          true
 Map_compass       custom          true
   Compass_X       default 
   Compass_Y       default 
     Speed_X       default 
     Speed_Y       default 
  C_offset_x       custom          28.87115288
  C_offset_y       custom          26.96616936
 Compass_rot       custom          true
    Def_zoom       custom  
```

>[!TIP]
>For more details please review the [basic example](https://github.com/hpsaturn/easy-preferences/tree/master/examples/basic), and also these developments that implements EasyPreferences library:

[IceNav v3 - ESP32 Based GPS Navigator](https://github.com/jgauchia/IceNav-v3)  
[ESPNowCam - Freenove S3 camera Tank](https://github.com/hpsaturn/ESPNowCam/tree/master/examples/freenove-tank)  
[CanAirIO - Air quality device](https://github.com/kike-canaries/canairio_firmware?tab=readme-ov-file#readme)  
[ESP32 Camera CLI - Camera Manager](https://github.com/hpsaturn/esp32-camera-cli?tab=readme-ov-file#readme)  

## Credits

Thanks to [@jgauchia](https://github.com/jgauchia) to use and test this library in his project.
