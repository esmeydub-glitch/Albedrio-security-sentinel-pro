CXX = g++
CXXFLAGS = -Iimgui -Iimgui/backends -g -Wall -Wformat
LDFLAGS = -lglfw -lGL -ldl

SOURCES = centro_mando_gui.cpp
SOURCES += imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp
SOURCES += imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:imgui/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: albedrio_gui

albedrio_gui: $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f albedrio_gui *.o
