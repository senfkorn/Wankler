# Hardware / Elektronik

Elektronik-Unterlagen für die Wankler-Interfaceplatine.

## Inhalt

| Datei | Beschreibung |
|---|---|
| `Schematic.pdf` | Schaltplan der Interfaceplatine (Rev. 1.0) |
| `BOM.xlsx` | Stückliste mit typischen eBay-Suchbegriffen zur Beschaffung der Bauteile |
| `easyeda/` | EasyEDA-Quelldateien (Schaltplan + Platinenlayout) |

## Wichtiger Hinweis

**Die Interfaceplatine ist optional.** Sie dient nur der einfachen Montage. Die ersten Messgeräte wurden vollständig diskret verdrahtet, ganz ohne PCB. Wer trotzdem eine Platine möchte, kann sich gerne beim Projektautor melden – es sind noch ein paar Exemplare vorhanden.

## Platine selbst fertigen lassen (EasyEDA / JLCPCB)

1. Bei [EasyEDA](https://easyeda.com) einen neuen Account/Workspace öffnen.
2. Über die Menüleiste: **Dokument → Öffnen → EasyEDA-Quelle** und die Datei `easyeda/PCB_Wankler_Interface.json` bzw. `easyeda/Schematic_Wankler.json` laden.
3. Über **Fertigen → PCB fertigen** direkt an JLCPCB übergeben.

## Bauteile

Die Bauteilliste (`BOM.xlsx`) enthält neben den technischen Bezeichnungen auch gängige eBay-Suchbegriffe, mit denen sich die Komponenten leicht wiederfinden lassen.

## Sensor-Kalibrierung

Mehrere der verwendeten (chinesischen) Drucksensoren wurden in einem Prüflabor mit hochwertigem Referenz-Messequipment (mehrere 1000 € Anschaffungswert) verglichen. Mit der in der Firmware hinterlegten Kalibrierung lag die Abweichung bei allen getesteten Sensoren unter 0,1 bar. Aus diesem Grund wurde auf eine nutzerseitige Kalibrierung über das Display verzichtet.
