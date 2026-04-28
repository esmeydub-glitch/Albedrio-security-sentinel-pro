# Albedrío Security Sentinel Pro
### Tactical Cybersecurity Architecture: Physical, Logical, and Defensive-Offensive

**Built in Pure C, eBPF, and SystemD.**

---

## 📜 Project History and Philosophy
Albedrío Security was born from the need to move away from traditional security architectures (based on reactive signatures and vulnerable high-level languages like Java or Python). This project was forged under a strict premise: **absolute immutability.**

Instead of building an antivirus, we built a living ecosystem. An engine that intertwines the hardware's physical signature (CPU/Silicon) with the machine's absolute time, ensuring that if a single malicious instruction attempts to execute, the system seals itself at the Kernel level. Additionally, it incorporates "Active Defense" doctrines, redirecting attacks back to their source.

---

## ⚙️ The 6 Pillars of the Architecture

1.  **🔐 Resonance Engine (SALK):** The cryptographic heart. Generates a rolling key every millisecond by merging the processor ID and CLOCK_BOOTTIME. If resonance is broken by an intrusion, the system cuts communications.
2.  **🛡️ The Iron Wall (eBPF/LSM):** A Kernel module injected deep into Linux. Intercepts absolutely all execution attempts (execve) and subjects them to SALK's mathematical validation.
3.  **🕳️ Punishment Multiverse:** A holographic Honeypot built using Namespaces (Network, PID, Mount). Isolates the attacker in a phantom shell, exposing them to 1.5 Terabytes of dynamically generated "bait" files to collapse their disk if they attempt exfiltration.
4.  **🛰️ Sentinel Radar (Active Defense):** An invisible omni-protocol radar that listens directly on Layer 2 (Raw Sockets). Upon detecting an intrusion, it activates a gravitational Black Hole and deploys **Petaboom** (an automated 100-thread counterattack designed to saturate the enemy network).
5.  **⚡ The Purifier (Hardware):** Aggressive quarantine and sterilization of peripherals (USB/NFC) by intercepting udev events before the OS mounts them, eradicating BadUSB injections.
6.  **🦅 Phoenix Protocol:** An agnostic self-repair engine. Audits disk cryptographic hashes against the official OS base. If mutated code (Rootkits) is detected, it executes a Panic Reboot.
7.  **🌌 Nebula Engine (Dark Matter):** Controlled traffic obfuscation system. Generates a continuous stream of noise to mask navigation patterns from ISP and Router Deep Packet Inspection (DPI).

---

## 🖥️ Tactical Command Center
The system includes a graphical operations interface written entirely in C++ with Dear ImGui (OpenGL/GLFW). Designed in "Dark Mode" for low power consumption and rapid military deployment. It does not use web engines, eliminating 100% of HTML/JS injection vulnerabilities.

---

## 🚀 Deployment and Installation
The system is designed to integrate automatically as an **Immortal Daemon (SystemD).**

1. **Clone the repository:**
   ```bash
   git clone https://github.com/esmeydub-glitch/Albedrio-security-sentinel-pro.git
   cd Albedrio-security-sentinel-pro
   ```
2. **Run the master installer as Root:**
   ```bash
   sudo ./instalar.sh
   ```
3. **Start the Graphical Interface (Visual Command Center):**
   ```bash
   ./albedrio_gui
   ```

---

## 🤝 Support the Project (Donations)
Cybersecurity must evolve towards physical immutability. If this ecosystem strengthens your infrastructure or you share our strict defensive design philosophy, consider supporting the forge of new weaponry:

📧 **Contact / Donations:** esmeydub@gmail.com

---
---

# Albedrío Security Sentinel Pro [ESPAÑOL]
### Arquitectura Táctica de Ciberseguridad de Nivel Físico, Lógico y Defensivo-Ofensivo

**Construido en C Puro, eBPF y SystemD.**

## 📜 Historia y Filosofía del Proyecto
Albedrío Security nació de la necesidad de abandonar las arquitecturas de seguridad tradicionales. Este proyecto fue forjado bajo una premisa estricta: **inmutabilidad absoluta.** En lugar de construir un antivirus, construimos un ecosistema vivo que entrelaza la firma física del hardware con el tiempo absoluto de la máquina.

## ⚙️ Los 6 Pilares de la Arquitectura
1.  **🔐 Motor de Resonancia (SALK):** El corazón criptográfico. Genera una llave rodante cada milisegundo fusionando el ID del procesador y el tiempo real.
2.  **🛡️ La Muralla de Hierro (eBPF/LSM):** Un módulo de Kernel que intercepta absolutamente todos los intentos de ejecución.
3.  **🕳️ Multiverso de Castigo:** Un Honeypot holográfico que aísla al atacante en una terminal falsa para colapsar su sistema.
4.  **🛰️ Sentinela Radar (Defensa Activa):** Radar invisible que activa un Agujero Negro y despliega el **Petaboom** contra el atacante.
5.  **⚡ El Purificador (Hardware):** Esterilización agresiva de periféricos (USB/NFC) antes de ser montados.
6.  **🦅 Protocolo Fénix:** Motor de autorreparación que audita hashes contra repositorios oficiales.
7.  **🌌 Motor Nebulosa (Materia Oscura):** Sistema de ofuscación de tráfico controlado. Genera ruido constante para enmascarar patrones de navegación ante el análisis del Router y el ISP (DPI).

## 🔐 Código Fuente y Política de Seguridad

**Albedrío Security** es un proyecto de **código abierto**, pero por razones de seguridad estratégica y para proteger la integridad del núcleo (Motor de Resonancia SALK, Muralla eBPF, Encriptado de GRUB), el código fuente completo de ciertos binarios sensibles **no se encuentra publicado directamente en este repositorio**.

Sí publicamos el código fuente de los módulos no críticos (Purificador, Nebulosa, Fénix, partes de Sentinela, etc.) para que la comunidad pueda auditar la mayoría del sistema.

### 📥 Solicitud del Código Fuente Completo

Si eres **investigador de seguridad, desarrollador, auditor o usuario avanzado** y necesitas acceder al código fuente completo (incluyendo las partes ofuscadas que generan los binarios) por motivos legítimos, puedes solicitarlo por correo electrónico:

✉️ **`codigo@albedriosecurity.org`**

**Condiciones para acceder al código fuente completo:**

1. **Identificación breve**: Indícanos tu nombre, afiliación (si aplica) y el propósito de tu auditoría o uso.
2. **Acuerdo de uso ético**: Compromiso por escrito de no utilizar el código para desarrollar malware, vulnerar sistemas ajenos, o vulnerar la integridad del proyecto.
3. **Confidencialidad**: El código fuente se entrega para tu uso personal o institucional, con el compromiso de no redistribuirlo sin permiso explícito.

El código se entregará en formato legible (`.c`, `.h`, `.cpp`, `Makefile`, scripts) bajo la misma licencia **GPL v3** que rige el proyecto.

### 📦 Para Usuarios Finales

**Los binarios proporcionados en este repositorio (`albedrio_gui`, `salk_core`, `sentinela`, `petaboom`, etc.) son totalmente funcionales y seguros.** No necesitas el código fuente para instalar, configurar y utilizar Albedrío Security en tu sistema. Sigue las instrucciones de instalación en la sección [🚀 Deployment and Installation](#-deployment-and-installation).

> [!NOTE]
> **Transparencia**: Los binarios no están encriptados (son binarios ELF estándar de Linux). Cualquier experto en ingeniería inversa puede analizarlos con herramientas como `objdump`, `strace` o `Ghidra`. Sin embargo, para facilitar la auditoría y modificación, proporcionamos el código fuente bajo petición a quienes demuestren un uso legítimo.

## ⚖️ Aviso Legal y Ética (Blindaje Jurídico)
Albedrío Security es un sistema de **Legítima Defensa Digital**. Cuenta con módulos de "Materia Oscura" (código ofensivo automatizado como Petaboom). El uso de este sistema en redes externas sin autorización es ilegal y responsabilidad exclusiva del administrador.

### 🛡️ Transparencia y Licenciamiento (GPLv3)
1.  **Componentes Sensibles:** Partes críticas del sistema (integración con el boot y encriptado de resonancia) se distribuyen en formato binario para proteger el secreto industrial y la integridad del hardware del usuario.
2.  **Cumplimiento GPL:** El código fuente completo de estos módulos está disponible bajo petición para fines de auditoría, previa verificación de identidad, garantizando que el conocimiento caiga en manos de defensores y no de atacantes.
3.  **Uso de Señuelos:** El sistema utiliza técnicas de "Honeypot" (Multiverso). Cualquier robo de información dentro de estos entornos es responsabilidad del intruso, ya que el acceso fue no autorizado y sobre datos de señuelo.

© 2024 Victor Manuel Gutierrez Flores (Esme) - Albedrío Security Master Tools.
