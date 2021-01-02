files = main.cpp \
	./src/graphics_engine/3d/*.cpp \
	./src/graphics_engine/displays/display_glfw/*.cpp \
	./src/graphics_engine/3d/renderers/renderer_gl/*.cpp \
	./src/app/*.cpp \
	./src/glad.c
#file = src/model_loading.cpp

all:$(file)
	g++ -Wall -I./include  -I./src  -o app  $(files)  -L./lib -lglfw -lGL -lpthread -ldl -lX11 -lXrandr -lXi -lSTB_IMAGE -lassimp -lIrrXML
	./app
clean:app
	rm -r app

test:app
	./app