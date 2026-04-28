
#!/bin/bash
# Crear la carnada de 1.5 Terabytes de "Materia Oscura"
# Estos archivos pesan 0 bytes en tu disco, pero el hacker verá TBs.

dd if=/dev/zero of=ALBEDRIO_CORE_BACKUP.vault bs=1 count=0 seek=1T
dd if=/dev/zero of=SALK_KEY_DATABASE.db bs=1 count=0 seek=500G

# Dar permisos de solo lectura para que parezcan archivos protegidos
chmod 444 *.vault *.db

echo "[+] Multiverso preparado: 1.5 Terabytes de carnada listos."