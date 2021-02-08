Der Wankler ist ein Mikrocontroller gesteuertes Kompressionsmessgerät für Wankelmotoren.

Der Mikrocontroller liest das Drucksignal eines Drucksensors 1000mal pro Sekunde (1000Hz) ein. Die Messwerte werden mit einem gleitenden Mittelwert gemittelt (die Filterkonstante kann über das LCD Display eingestellt werden). Nun wird der sinusförmige Druckverlauf des Wankelmotors analysiert und Minima und Maxima ermittelt. Drei aufeinander folgende Maxima entsprechen den Kompressionswerten der drei Brennkammern im Motor. Gleichzeitig wird noch die zeitliche Differenz zwischen den Maxima gemessen und somit die Motordrehzahl ermittelt. Der zu erwartende Kompressionsdruck ist direkt von der Motordrehzahl abhängig. Daher ist auch dieser Messwert wichtig.

Leider gibt es aktuell noch eine Montageanleitung. Ich habe ein paar Bilder als Referenz hochgeladen.

Die letzten Messgeräte wurden mit einer Interfaceplatine gebaut. Diese ist absolut nicht notwendig. Sie dient nur zur einfachen Montage. Die ersten Messgeräte habe ich komplett diskret verdrahtet. Wenn jemand eine Platine will, kann er sich gerne bei mir melden. Ich habe noch ein paar hier liegen.

Mehrere chinesischen Druckmesssensoren wurden in einem Prüflabor von uns mit einem mehrere 1000 Euro teuren Messequipment geprüft. Die Sensoren liegen mit den in der Firmware hinterlegten Kalibrierung in einem Bereich unter 0.1 Bar. Nach diesem Ergebnis wurde die Idee der "Userkalibrierung " über das Display wieder verworfen.
