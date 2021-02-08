Der Wankler ist ein Mikrocontroller gesteuertes Kompressionsmessgerät für Wankelmotoren.

Der Mikrocontroller liest das Drucksignal eines Drucksensors 1000mal pro Sekunde (1000Hz) ein. Die Messwerte werden mit einem gleitenden Mittelwert gemittelt (die Filterkonstante kann über das LCD Display eingestellt werden). Nun wird der sinusförmige Druckverlauf des Wankelmotors analysiert und Minima und Maxima ermittelt. Drei aufeinander folgende Maxima entsprechen den Kompressionswerten der drei Brennkammern im Motor. Gleichzeitig wird noch die zeitliche Differenz zwischen den Maxima gemessen und somit die Motordrehzahl ermittelt. Der zu erwartende Kompressionsdruck ist direkt von der Motordrehzahl abhängig. Daher ist auch dieser Messwert wichtig.

Hier findet ihr alle zum Bau eines Messgeräts nötigen Informationen. 

Unter case ist eine Datei zum direkten 3D Druck des Gehäuses zu finden. Zusätzlich ist dort die Step Datei zu finden. Diese kann in ein beliebiges 3D Cad Programm importiert und bearbeitet werden.

Unter Firmware ist die Software des Arduino Mikrokontrollers zu finden. Diese wurde mit PlatformIO erzeugt. Zusätzlich ist dort die fertig Kompilierte hex Datei zu finden. Diese kann mit einem Tool wie zum Beispiel http://www.hobbytronics.co.uk/download/XLoader.zip auf den Arduino Nano geladen werden.

Im Hardware Ordner ist das EasyEda Projekt zu finden. Damit kann man sich direkt bei JlcPcb die Platinen herstellen lassen. Dort gibt zusätzlich eine Bauteilliste mit typischen Ebay Suchnamen um die Komponenten zu finden.

Leider gibt es aktuell noch eine Montageanleitung. Ich habe ein paar Bilder als Referenz hochgeladen.

Die letzten Messgeräte wurden mit einer Interfaceplatine gebaut. Diese ist absolut nicht notwendig. Sie dient nur zur einfachen Montage. Die ersten Messgeräte habe ich komplett diskret verdrahtet. Wenn jemand eine Platine will, kann er sich gerne bei mir melden. Ich habe noch ein paar hier liegen.

Mehrere chinesischen Druckmesssensoren wurden in einem Prüflabor von uns mit einem mehrere 1000 Euro teuren Messequipment geprüft. Die Sensoren liegen mit den in der Firmware hinterlegten Kalibrierung in einem Bereich unter 0.1 Bar. Nach diesem Ergebnis wurde die Idee der "Userkalibrierung " über das Display wieder verworfen.
