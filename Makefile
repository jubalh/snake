all:
	g++ -o test snake.cpp `sdl-config --cflags --libs`
