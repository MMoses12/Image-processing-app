hw4: gsc_image.o rgb_image.o gsc_pixel.o rgb_pixel.o token.o hw4.o
	g++ -g gsc_image.o rgb_image.o gsc_pixel.o rgb_pixel.o token.o hw4.o -o hw4 -fsanitize=address
hw4.o: hw4.cpp gsc_image.o gsc_image.o rgb_image.o token.o
	g++ -g -c hw4.cpp gsc_image.cpp rgb_image.cpp token.cpp -fsanitize=address
gsc_image.o: gsc_image.cpp gsc_image.hpp gsc_pixel.o rgb_image.o
	g++ -g -c gsc_image.cpp -fsanitize=address
rgb_image.o: rgb_image.cpp rgb_image.hpp rgb_pixel.o
	g++ -g -c rgb_image.cpp -fsanitize=address
gsc_pixel.o: gsc_pixel.cpp gsc_pixel.hpp
	g++ -g -c gsc_pixel.cpp -fsanitize=address
rgb_pixel.o: rgb_pixel.cpp rgb_pixel.hpp
	g++ -g -c rgb_pixel.cpp -fsanitize=address
token.o: token.cpp token.hpp
	g++ -g -c token.cpp -fsanitize=address
clean:
	rm token.o rgb_pixel.o rgb_image.o gsc_pixel.o gsc_image.o hw4.o
