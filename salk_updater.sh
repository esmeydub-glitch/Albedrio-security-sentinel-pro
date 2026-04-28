#!/bin/bash
# SALK Security Updater v1.0
# Detecta cambios en el repositorio maestro

REPO_DIR="/home/salk/Documentos/albedrio security/instalable"
cd "$REPO_DIR" || exit

# Buscamos cambios en GitHub
git fetch origin main &>/dev/null

LOCAL=$(git rev-parse @)
REMOTE=$(git rev-parse @{u})

if [ "$LOCAL" = "$REMOTE" ]; then
    echo "[i] SALK está actualizado. Versión Local: $LOCAL"
else
    echo "[?] RECOMENDACIÓN: Nueva mejora disponible. ¿Deseas autorizar la descarga?"
    echo "[*] Ejecuta 'git pull origin main' para inyectar la nueva versión."
fi
