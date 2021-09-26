# Flags
NAME?="TBEngineTestCompile"

compile:
	clear
	echo ">-- Compiling engine --<"
	echo "Executable file name (NAME= to change): ${NAME}"
	echo ""

	g++ -o ${NAME} src/main.cpp src/shaders.cpp src/buffers.cpp src/cube.cpp src/mesh.cpp -lGL -lGLEW -lglut

	echo ">-- Compilation end --<"

	./${NAME}

.SILENT:
