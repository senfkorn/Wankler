# Firmware

Firmware für den Arduino Nano im Wankler-Messgerät, erstellt mit [PlatformIO](https://platformio.org/).

## Inhalt

| Datei | Beschreibung |
|---|---|
| `src/main.cpp` | Quellcode der Firmware |
| `platformio.ini` | PlatformIO-Projektkonfiguration (siehe Hinweis unten) |
| `firmware.hex` | Fertig kompilierte Firmware zum direkten Flashen |

## Firmware flashen

**Option A – fertige .hex-Datei (am einfachsten)**

Mit einem Tool wie [XLoader](http://www.hobbytronics.co.uk/download/XLoader.zip) kann `firmware.hex` direkt auf den Arduino Nano geflasht werden. Kein Compiler nötig.

**Option B – aus dem Quellcode bauen**

```bash
# PlatformIO CLI installieren, falls noch nicht vorhanden
pip install platformio

# Im firmware/-Ordner:
pio run --target upload
```

> **Hinweis:** `platformio.ini` war im Originalprojekt nicht dabei und wurde anhand der in `main.cpp` eingebundenen Bibliotheken (`LiquidCrystal_I2C`, `RotaryEncoder`, `OneButton`) sowie der Zielhardware (Arduino Nano / ATmega328) rekonstruiert. Bitte die Bibliotheksversionen bei Bedarf anpassen, falls es beim Bauen zu Fehlern kommt.

## Funktionsweise

Die Firmware liest das Signal eines Drucksensors mit 1000 Hz ein, glättet es per gleitendem Mittelwert und erkennt darin die Maxima des sinusförmigen Druckverlaufs eines Wankelmotors. Drei aufeinanderfolgende Maxima entsprechen den Kompressionswerten der drei Brennkammern. Aus dem zeitlichen Abstand der Maxima wird zusätzlich die Motordrehzahl berechnet.

Bedienung erfolgt über ein I2C-LCD (20x4) und einen Drehencoder mit Taster. Parameter (Schwellwert, Timeout, Filter) werden im EEPROM gespeichert und können über das Menü angepasst werden.
