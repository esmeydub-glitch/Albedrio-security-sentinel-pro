#!/bin/bash
# INSTALADOR MAESTRO - ALBEDRIO SECURITY v3.3 (Full Automation)
# Autor: Antigravity & Victor

echo ">>> Iniciando Despliegue de Albedrío Security v3.3 <<<"

# 1. Crear Grupo de Autorización (La Firma)
echo "[+] Creando grupo salk_auth (9999)..."
groupadd -g 9999 salk_auth 2>/dev/null
usermod -aG salk_auth $USER

# 2. Instalar Binarios de SALK
echo "[+] Instalando motores de resonancia y defensa..."
for f in salk_core salk_priv sentinela petaboom albedrio_gui; do
    if [ -f "./$f" ]; then
        cp "./$f" "/usr/bin/$f"
    elif [ -f "./bin/$f" ]; then
        cp "./bin/$f" "/usr/bin/$f"
    fi
done
chmod 4755 /usr/bin/salk_priv

# 3. FIRMA DE SUPERVIVENCIA (Pase VIP para herramientas críticas)
echo "[+] Firmando herramientas de supervivencia (GID 9999)..."
HERRAMIENTAS=(
    "/usr/bin/bash" "/usr/bin/ls" "/usr/bin/sudo" 
    "/usr/bin/systemctl" "/usr/bin/journalctl" 
    "/usr/bin/grep" "/usr/bin/cat" "/usr/bin/mkdir"
    "/usr/bin/chmod" "/usr/bin/chown" "/usr/bin/chgrp"
)

for h in "${HERRAMIENTAS[@]}"; do
    if [ -f "$h" ]; then
        chgrp 9999 "$h"
        # Restaurar SetUID si se perdió al cambiar el grupo (ej: sudo)
        if [[ "$h" == *"/sudo"* || "$h" == *"/su"* ]]; then
            chmod 4755 "$h"
        fi
    fi
done

# 4. Configurar La Muralla de Hierro (eBPF)
echo "[+] Inyectando La Muralla en el Kernel..."
mkdir -p /etc/albedrio/ebpf
cp ebpf/muralla_bpf.o /etc/albedrio/ebpf/ 2>/dev/null || cp muralla_bpf.o /etc/albedrio/ebpf/

# 5. Configurar GRUB (Activación de Kernel)
echo "[+] Configurando GRUB para activación BPF LSM..."
sed -i 's/GRUB_CMDLINE_LINUX_DEFAULT="quiet"/GRUB_CMDLINE_LINUX_DEFAULT="quiet lsm=lockdown,yama,bpf,apparmor"/' /etc/default/grub
update-grub

# 6. Instalar Servicio Systemd
echo "[+] Activando demonio inmortal salk-core..."
cp salk-core.service /etc/systemd/system/ 2>/dev/null || cp bin/salk-core.service /etc/systemd/system/
systemctl daemon-reload
systemctl enable salk-core.service

echo ">>> DESPLIEGUE 100% COMPLETADO. El sistema está blindado. <<<"
