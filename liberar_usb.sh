#!/bin/bash
# Script de Liberación Autorizada SALK
echo 1 | ./salk/salk_priv tee /sys/bus/usb/devices/*/authorized > /dev/null
echo "[+] Puertos USB Liberados por el Dueño."
