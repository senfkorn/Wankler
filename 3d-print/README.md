# 3D-Druck – Gehäuse

3D-Druckdateien für das Gehäuse des Wankler-Messgeräts.

## Inhalt

| Datei | Beschreibung |
|---|---|
| `Case.3mf` | Druckfertige Datei inkl. Druckeinstellungen, zum direkten Import in den Slicer (z. B. PrusaSlicer, Bambu Studio) |
| `Wankler_v24.step` | STEP-Datei des Gehäuses, editierbar in jedem gängigen CAD-Programm (Fusion 360, FreeCAD, SolidWorks, ...) |

## Verwendung

- **Nur drucken:** `Case.3mf` direkt im Slicer öffnen und drucken.
- **Gehäuse anpassen:** `Wankler_v24.step` in ein CAD-Programm importieren, bearbeiten und als neue `.3mf`/`.stl` für den Slicer exportieren.

## Material & Druckempfehlung

In den Baufotos (siehe [`../docs/images`](../docs/images)) sind fertig gedruckte Gehäuse in orange und rot zu sehen – Standard-PLA hat sich dabei bewährt. Konkrete Slicer-Einstellungen (Layerhöhe, Infill, Support) sind in der `Case.3mf` bereits hinterlegt.
