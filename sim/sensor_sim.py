#!/usr/bin/env python3
"""Simulador local del firmware (Capa 4) sin hardware.

Replica la misma matematica que `firmware/main.ino` para poder generar
evidencia reproducible en cualquier maquina con Python, aunque no se disponga
de una placa ESP32 ni del simulador Wokwi.

Uso:
    python sensor_sim.py --samples 5 --value 6.5
    python sensor_sim.py --sweep        # barrido 0..10 bar
"""

from __future__ import annotations

import argparse
import json

VREF_MV = 3300.0
ADC_MAX = 4095.0
FULL_SCALE = 10.0


def adc_to_reading(raw: int) -> dict:
    volts = (raw / ADC_MAX) * VREF_MV / 1000.0
    pressure = (raw / ADC_MAX) * FULL_SCALE
    return {"pressure_bar": round(pressure, 3), "volts": round(volts, 3), "raw": raw}


def bar_to_raw(bar: float) -> int:
    bar = max(0.0, min(FULL_SCALE, bar))
    return int(round((bar / FULL_SCALE) * ADC_MAX))


def main() -> int:
    parser = argparse.ArgumentParser(description="Simulador del nodo sensor ESP32")
    parser.add_argument("--samples", type=int, default=5)
    parser.add_argument("--value", type=float, default=6.5, help="presion en bar")
    parser.add_argument("--sweep", action="store_true", help="barrido de 0 a 10 bar")
    args = parser.parse_args()

    print(json.dumps({"event": "boot", "firmware": "sensor-node-1.0.0"}))
    if args.sweep:
        for step in range(11):
            bar = step * 1.0
            print(json.dumps(adc_to_reading(bar_to_raw(bar))))
        return 0
    for _ in range(args.samples):
        print(json.dumps(adc_to_reading(bar_to_raw(args.value))))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
