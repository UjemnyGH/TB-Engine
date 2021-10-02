# Flags
NAME?="TBEngineTestCompile"

compile:
	clear
	echo ">-- Compiling engine --<"
	echo "Executable file name (NAME= to change): ${NAME}"
	echo ""

	g++ -o ${NAME} src/main.cpp src/shaders.cpp src/buffers.cpp src/cube.cpp src/mesh.cpp src/player/camera.cpp src/TB_time.cpp -lGL -lGLEW -lglut -lpthread

	echo ">-- Compilation end --<"

	./${NAME}

.SILENT:
