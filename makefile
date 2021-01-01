file = main.cpp    ./src/graphics_engine/*.cpp ./src/graphics_engine/gl_renderer/*.cpp  ./src/app/*.cpp ./src/glad.c
#file = src/model_loading.cpp

all:$(file)
	g++ -I./include  -I./src  -o app  $(file)  -L./lib -lglfw -lGL -lpthread -ldl -lX11 -lXrandr -lXi -lSTB_IMAGE -lassimp -lIrrXML
	./app
clean:app
	rm -r app

test:app
	./app