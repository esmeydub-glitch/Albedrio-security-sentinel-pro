#!/bin/bash

# --- CONFIGURACIÓN DE RUTAS ---
RAIZ=$(pwd)
DESTINO="$RAIZ/instalable"
VERDE='\033[0;32m'
NC='\033[0m'

echo -e "${VERDE}>>> Iniciando la Forja del Instalador Independiente <<<${NC}"

# 1. Crear carpeta de salida
mkdir -p "$DESTINO"

# 2. Compilar Sentinela (El Observador)
echo "[+] Compilando Sentinela Core..."
gcc "$RAIZ/sentinela/sentinela_core.c" -o "$DESTINO/sentinela_final" -lpthread -O3

# 3. Compilar Multiverso (La Jaula)
echo "[+] Compilando Multiverso Core..."
gcc "$RAIZ/multiverso de castigo/multiverso_core.c" -o "$DESTINO/multiverso_final" -lpthread -O3

# 4. Compilar Petaboom (El Proyectil)
echo "[+] Compilando Petaboom Core con G++-15..."
g++-15 -O3 "$RAIZ/multiverso de castigo/petaboom_core.cpp" -o "$DESTINO/petaboom" -lpthread

# 5. Mover scripts necesarios
cp "$RAIZ/multiverso de castigo/generar_trampas.sh" "$DESTINO/"
cp "$RAIZ/sellar_sistema.sh" "$DESTINO/"

# --- INTEGRACIÓN DEFENSIVA (SALK, Fénix, Purificador, Muralla, GUI) ---
echo "[+] Compilando Armadura Pasiva (SALK, Purificador, Fénix)..."
gcc "$RAIZ/salk/salk_core.c" -o "$DESTINO/salk_core" -lcrypto -lbpf -O3
gcc "$RAIZ/el_purificador/purificador_core.c" -o "$DESTINO/purificador_core" -O3
gcc "$RAIZ/protocolo fenix/fenix_core.c" -o "$DESTINO/fenix_core" -O3

echo "[+] Compilando Centro de Mando Gráfico (GUI)..."
make -C "$RAIZ/apps interface frontend"
cp "$RAIZ/apps interface frontend/albedrio_gui" "$DESTINO/"

echo "[+] Preparando objetos del Kernel (eBPF y Udev)..."
mkdir -p "$DESTINO/ebpf" "$DESTINO/rules"
cp "$RAIZ/muralla de hierro/muralla_bpf.o" "$DESTINO/ebpf/"
cp "$RAIZ/el_purificador/99-albedrio-usb.rules" "$DESTINO/rules/"

# 6. CREAR EL INSTALADOR FINAL DENTRO DE LA CARPETA
echo "[+] Generando script de instalación maestra..."
cat << 'EOF' > "$DESTINO/instalar.sh"
#!/bin/bash
echo "--- INSTALANDO ALBEDRÍO SECURITY (MODO ABSOLUTO) ---"
if [ "$EUID" -ne 0 ]; then echo "Ejecuta con sudo"; exit; fi

# --- CONFIGURACIÓN CRÍTICA DEL KERNEL (BPF LSM) ---
if ! grep -q "lsm=bpf" /etc/default/grub; then
    echo "[!] Habilitando BPF LSM en el GRUB para activar La Muralla..."
    sed -i 's/GRUB_CMDLINE_LINUX_DEFAULT="/GRUB_CMDLINE_LINUX_DEFAULT="lsm=lockdown,yama,bpf,apparmor /' /etc/default/grub
    update-grub
    echo "[!] REINICIO REQUERIDO para activar el escudo de hardware."
fi

# Dar permisos a binarios
chmod +x sentinela_final multiverso_final petaboom generar_trampas.sh

# Preparar el cebo del multiverso
./generar_trampas.sh

# Configurar capacidades de red para el Petaboom
setcap cap_net_raw,cap_net_admin=eip petaboom 2>/dev/null

# --- ENCAPSULACIÓN SSH (MODO GITHUB EXCLUSIVO) ---
echo "[!] Desactivando el Servidor SSH de Entrada (Inbound)..."
systemctl stop sshd ssh 2>/dev/null || true
systemctl disable sshd ssh 2>/dev/null || true

echo "[!] Aplicando Muralla de Red para SSH (Outbound a GitHub)..."
iptables -D INPUT -p tcp --dport 22 -j DROP 2>/dev/null || true
iptables -D OUTPUT -p tcp --dport 22 -j DROP 2>/dev/null || true

iptables -A INPUT -p tcp --dport 22 -j DROP
# Bloques IP oficiales de GitHub para SSH
iptables -A OUTPUT -p tcp --dport 22 -d 140.82.112.0/20 -j ACCEPT
iptables -A OUTPUT -p tcp --dport 22 -d 192.30.252.0/22 -j ACCEPT
iptables -A OUTPUT -p tcp --dport 22 -d 185.199.108.0/22 -j ACCEPT
iptables -A OUTPUT -p tcp --dport 22 -j DROP

# --- DESPLIEGUE DEFENSIVO Y OFENSIVO ---
echo "[*] Instalando Motores Absolutos en /usr/local/bin/"
cp salk_core purificador_core fenix_core albedrio_gui sentinela_final multiverso_final petaboom generar_trampas.sh /usr/local/bin/ 2>/dev/null
chmod +x /usr/local/bin/salk_core /usr/local/bin/purificador_core /usr/local/bin/fenix_core /usr/local/bin/albedrio_gui /usr/local/bin/sentinela_final /usr/local/bin/multiverso_final /usr/local/bin/petaboom /usr/local/bin/generar_trampas.sh 2>/dev/null

echo "[*] Instalando La Muralla de Hierro (eBPF)..."
mkdir -p /etc/albedrio/ebpf
cp ebpf/muralla_bpf.o /etc/albedrio/ebpf/

echo "[*] Instalando Reglas de Frontera Física (Udev)..."
cp rules/99-albedrio-usb.rules /etc/udev/rules.d/
udevadm control --reload-rules
udevadm trigger

echo "--- INSTALACIÓN COMPLETADA ---"
echo "-> Usa: sudo ./sentinela_final para activar el radar."
echo "-> Usa: albedrio_gui para iniciar el Centro de Mando Visual."
EOF

chmod +x "$DESTINO/instalar.sh"

echo -e "${VERDE}>>> PROCESO FINALIZADO. Todo está en la carpeta: /instalable <<<${NC}"