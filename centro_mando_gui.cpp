#include "imgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <vector>

float ejecutar_y_obtener_float(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return 0.0f;
    char buffer[128];
    float resultado = 0.0f;
    if (fgets(buffer, 128, pipe)) resultado = atof(buffer);
    pclose(pipe);
    return resultado;
}

void aplicar_estilo_cyberpunk() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.02f, 0.02f, 0.03f, 0.98f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 1.0f, 0.0f, 0.5f);
    style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 1.0f, 0.3f, 1.0f);
}

void renderizar_interfaz() {
    static std::vector<float> cpu_history(100, 0.0f);
    static std::vector<float> net_history(100, 0.0f);
    static int fantasmas = 0;
    static char logs[2048] = "Sincronizando con Sentinela...\n";
    static float timer = 0;

    timer += ImGui::GetIO().DeltaTime;
    if (timer > 0.5f) { // Actualización rápida (2Hz)
        fantasmas = (int)ejecutar_y_obtener_float("ss -tan | grep :2222 | grep ESTABLISHED | wc -l");
        
        // Desplazamos historial
        for (int i = 0; i < 99; i++) {
            cpu_history[i] = cpu_history[i+1];
            net_history[i] = net_history[i+1];
        }
        cpu_history[99] = ejecutar_y_obtener_float("top -bn1 | grep 'Cpu(s)' | awk '{print $2 + $4}'");
        net_history[99] = ejecutar_y_obtener_float("cat /proc/net/dev | grep wlan0 | awk '{print ($3+$11)/1024}'"); // KB/s
        timer = 0;
    }

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("ALBEDRIO TACTICAL DASHBOARD", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar()) {
        ImGui::Text("SISTEMA: OPERATIVO | NIVEL DE AMENAZA: BAJO | DUEÑO: ESME");
        ImGui::EndMenuBar();
    }

    // --- FILA 1: GRAFICOS DE PODER ---
    ImGui::Columns(2);
    ImGui::Text("CARGA DE SILICIO (CPU)");
    ImGui::PlotLines("##CPU", cpu_history.data(), cpu_history.size(), 0, NULL, 0.0f, 100.0f, ImVec2(-1, 80));
    
    ImGui::NextColumn();
    ImGui::Text("FLUJO DE MATERIA OSCURA (NET)");
    ImGui::PlotHistogram("##NET", net_history.data(), net_history.size(), 0, NULL, 0.0f, 5000.0f, ImVec2(-1, 80));
    
    ImGui::Columns(1);
    ImGui::Separator();

    // --- FILA 2: STATUS TACTICO ---
    ImGui::Columns(3);
    ImGui::Text("RESONANCIA");
    ImGui::TextColored(ImVec4(0,1,0,1), "LATIENDO: %lx", (unsigned long)time(NULL) ^ 0xDEADBEEF);
    
    ImGui::NextColumn();
    ImGui::Text("MULTIVERSO");
    ImGui::TextColored(fantasmas > 0 ? ImVec4(1,0,0,1) : ImVec4(1,1,1,1), "FANTASMAS: %d", fantasmas);

    ImGui::NextColumn();
    ImGui::Text("PURIFICADOR");
    if (ImGui::Button("LIBERAR USB", ImVec2(-1, 30))) system("salk_priv liberar_usb.sh");

    ImGui::Columns(1);
    ImGui::Separator();

    // --- FILA 3: CONSOLA DE EVENTOS ---
    ImGui::Text("CONSOLA DE EVENTOS SENTINELA");
    ImGui::BeginChild("LogRegion", ImVec2(0, -1), true);
    if (fantasmas > 0) ImGui::TextColored(ImVec4(1,0,0,1), "[!] ALERTA: Conexión detectada en puerto 2222.");
    ImGui::Text("[i] Resonancia de Hardware validada.");
    ImGui::Text("[i] Muro de Hierro bloqueando peticiones externas.");
    ImGui::Text("[i] El Purificador vigilando puertos físicos.");
    ImGui::EndChild();

    ImGui::End();
}

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

int main(int, char**) {
    if (!glfwInit()) return 1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Albedrio Security", NULL, NULL);
    glfwMakeContextCurrent(window);
    ImGui::CreateContext();
    aplicar_estilo_cyberpunk();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        renderizar_interfaz();
        ImGui::Render();
        int dw, dh; glfwGetFramebufferSize(window, &dw, &dh);
        glViewport(0, 0, dw, dh);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    return 0;
}
