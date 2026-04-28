#!/bin/bash
# INSTALADOR MAESTRO - ALBEDRIO SECURITY v3.3
# Autor: Antigravity & Victor

echo ">>> Iniciando Despliegue de Albedrío Security v3.3 <<<"

# 1. Crear Grupo de Autorización (La Firma)
groupadd -g 9999 salk_auth 2>/dev/null
usermod -aG salk_auth $USER

# 2. Instalar Binarios de Sistema
cp salk_core /usr/bin/salk_core
cp salk_priv /usr/bin/salk_priv
cp sentinela /usr/bin/sentinela
chmod 4755 /usr/bin/salk_priv

# 3. Configurar La Muralla de Hierro (eBPF)
mkdir -p /etc/albedrio/ebpf
cp ebpf/muralla_bpf.o /etc/albedrio/ebpf/

# 4. Configurar GRUB (Activación de Kernel)
sed -i 's/GRUB_CMDLINE_LINUX_DEFAULT="quiet"/GRUB_CMDLINE_LINUX_DEFAULT="quiet lsm=lockdown,yama,bpf,apparmor"/' /etc/default/grub
update-grub

# 5. Instalar Servicio Systemd
cp salk-core.service /etc/systemd/system/
systemctl daemon-reload
systemctl enable salk-core.service

echo ">>> INSTALACIÓN COMPLETADA. El sistema se blindará en el próximo reinicio. <<<"
