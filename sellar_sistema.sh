#!/bin/bash
echo "--- FORJANDO EL SELLO DE SALK ---"

if [ "$EUID" -ne 0 ]; then
  echo "Por favor, ejecuta como root (sudo)"
  exit
fi

# 1. Crear el grupo con GID 9999
groupadd -g 9999 salk_auth 2>/dev/null || true

# 2. Sellar todos los directorios vitales (incluyendo intérpretes de librerías)
DIRECTORIOS=("/bin" "/usr/bin" "/sbin" "/usr/sbin" "/lib" "/lib32" "/lib64" "/usr/lib" "/usr/local/bin")

echo "[!] Sellando sistema operativo con GID 9999..."
for DIR in "${DIRECTORIOS[@]}"; do
    if [ -d "$DIR" ]; then
        echo "  -> Marcando $DIR"
        chown -R root:salk_auth "$DIR" 2>/dev/null
    fi
done

# Asegurar que nuestra propia carpeta de Albedrio Security también esté sellada,
# o de lo contrario no podremos ejecutar los binarios generados en el instalador
chown -R root:salk_auth "/home/salk/Documentos/albedrio security" 2>/dev/null

echo "[+] Sello forjado con éxito. Sistema esterilizado."
