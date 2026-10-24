# Capa 4 — I+D y prototipado (firmware + electrónica)

[![CI](https://github.com/lazarolpro/nodo-sensor-esp32/actions/workflows/ci.yml/badge.svg)](https://github.com/lazarolpro/nodo-sensor-esp32/actions/workflows/ci.yml)
[`lazarolpro/nodo-sensor-esp32`](https://github.com/lazarolpro/nodo-sensor-esp32) · parte del [portafolio de 9 capacidades](https://github.com/lazarolpro/portafolio)

**Capacidad demostrada:** llevar una idea a un prototipo de firmware ejecutable y
**verificable online** sin necesidad de hardware físico.

## Problema real

Prototipar electrónica suele requerir comprar componentes y montar un banco. Aquí
el prototipo corre en un simulador gratuito y deja la evidencia en el repo.

## Qué hace

- Firmware para ESP32 que lee un sensor analógico y publica una lectura JSON.
- Diagrama de Wokwi (`wokwi/diagram.json`) para ejecutarlo en el navegador gratis.
- Simulador local en Python que replica la misma matemática, para generar
  evidencia aunque no haya placa ni simulador.

## Cómo ejecutar

Simulador local (sin hardware):

```bash
python sim/sensor_sim.py --samples 5 --value 6.5
python sim/sensor_sim.py --sweep
```

En Wokwi (gratis, en el navegador):

1. Abre <https://wokwi.com/projects/new/esp32>.
2. Pega `firmware/main.ino` y el `wokwi/diagram.json`.
3. Pulsa *Start* y observa el monitor serie.

## Evidencia que produce

- `firmware/main.ino` — firmware comentado y compilable.
- `wokwi/diagram.json` — circuito reproducible online.
- Salida JSON determinista del simulador local.

## Stack

Arduino/ESP32 (C++), Wokwi (simulación), Python 3 (simulador de banco).

## Por qué le importa a la empresa

Demuestra **I+D y prototipado** con costo cero de hardware: de la idea a una
demo funcional y compartible en el navegador.

**En mantenimiento:** prototipar un sensor o un lazo de control antes de comprar
el hardware definitivo.
