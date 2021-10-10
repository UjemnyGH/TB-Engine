# Flags
NAME?="TBEngineTestCompile"

compile:
	clear
	echo ">-- Compiling engine --<"
	echo "Executable file name (NAME= to change): ${NAME}"
	echo ""

	g++ -o ${NAME} src/main.cpp src/TB_shaders.cpp src/TB_buffers.cpp src/TB_cube.cpp src/TB_mesh.cpp src/player/TB_camera.cpp src/TB_time.cpp src/TB_window.cpp -lGL -lGLEW -lglut -lpthread

	echo ">-- Compilation end --<"

	./${NAME}

.SILENT:
