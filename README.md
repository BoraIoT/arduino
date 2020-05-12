# Arduino Library for Plataforma IoT
> **Version:** 1.0.0
> **Tags:** arduino, node-mcu, iot, mqtt

This is an Arduino Library responsible to send and receive data from [Plataforma IoT](https://github.com/paulovitorcs/plataformaiot).

---

## Requirements:
- Connection no Internet

---

## How to Use:
1. Make sure you have created a device on [Plataforma IoT](https://github.com/paulovitorcs/plataformaiot)
2. On Arduino import library with `#include <plataformaIot.h>`
3. Declare your device variable object with `IoT <your-device-variable>(<wifi-object-as-parameter>)`
```
WifiClient wifi;
IoT myMainDevice(wifi);
```
4. Init your device variable object using `<your-device-variable>.begin("<your-device-secret-key>")`
```
myMainDevice.begin("432219073b2d09d1369955dd95877ff4cedcac25bce25e69540d1c46555c8eaf");
```
5. From now on you will be able to use our library functions to send and receive data

---

## Reading variables:
Arduino already uses `analogRead()` and `digitalRead()`. Now you can also read virtual variables that comes directly from API with `virtualRead()`. To use those functions to send data to API you may use it inside your device variable object: `myMainDevice.analogRead()`. It's also important to set a variable name that will save that on database. Check example:
#### int analogRead(int pin, String variable);
```
myMainDevice.analogRead(D1, "pin_D1")
```
#### int digitalRead(int pin, String variable);
```
myMainDevice.digitalRead(D1, "pin_D1")
```
#### String virtualRead(String variable);
```
myMainDevice.virtualRead("pin_D1")
```

## Writing variables:
To write values Arduino already uses `analogRead()` and `digitalRead()`. It's also possible to write virtual variables directly from Arduino IDE to API. Just like reading variables you may use it inside your device variable object:
#### int analogWrite(int pin, int value, String variable);
```
myMainDevice.analogWrite(D1, 111, "pin_D1")
```
#### int digitalWrite(int pin, int value, String variable);
```
myMainDevice.digitalWrite(D1, HIGH, "pin_D1")
```
#### String virtualWrite(String variable, String value);
```
myMainDevice.virtualWrite("pin_D1", "value")
```
