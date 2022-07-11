all: image_file ascii_image questions_3 one_color ppm_menu

PPM.o: PPM.cpp Image.h PPM.h ActionData.h
	g++ -c PPM.cpp
image_menu.o: image_menu.cpp image_menu.h Image.h PPM.h ActionData.h 
	g++ -c image_menu.cpp
Image.o: Image.cpp image_menu.h Image.h
	g++ -c Image.cpp
ActionData.o: ActionData.cpp ActionData.h PPM.h
	g++ -c ActionData.cpp
MenuData.o: MenuData.cpp MenuData.h ActionData.h
	g++ -c MenuData.cpp
NumberGrid.o: NumberGrid.cpp NumberGrid.h PPM.h
	g++ -c NumberGrid.cpp
ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h NumberGrid.h ThreadedVector.h
	g++ -c ThreadedGrid.cpp
ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h ThreadedGrid.h ThreadedVector.h
	g++ -c ComplexFractal.cpp 
JuliaSet.o: JuliaSet.cpp JuliaSet.h ComplexFractal.h
	g++ -c JuliaSet.cpp
ColorTable.o: ColorTable.cpp ColorTable.h
	g++ -c ColorTable.cpp
MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h ComplexFractal.h
	g++ -c MandelbrotSet.cpp


questions_3: questions_3.o image_menu.o Image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -o questions_3 questions_3.o image_menu.o Image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread
questions_3.o: questions_3.cpp image_menu.h ActionData.h MenuData.h NumberGrid.h ThreadedGrid.h ThreadedVector.h ColorTable.h MandelbrotSet.h
	g++ -c questions_3.cpp 

ascii_image.o: ascii_image.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ComplexFractal.h JuliaSet.h ThreadedGrid.h ThreadedVector.h ColorTable.h MandelbrotSet.h
	g++ -c ascii_image.cpp
ascii_image: image_menu.o Image.o ascii_image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -o ascii_image image_menu.o	Image.o ascii_image.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread

image_file: image_file.o Image.o image_menu.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -o image_file image_menu.o Image.o image_file.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread
image_file.o: image_file.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ComplexFractal.h JuliaSet.h ThreadedGrid.h ThreadedVector.h ColorTable.h MandelbrotSet.h
	g++ -c image_file.cpp 

one_color: one_color.o Image.o image_menu.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -o one_color image_menu.o Image.o one_color.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread
one_color.o: one_color.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ComplexFractal.h JuliaSet.h ThreadedGrid.h ThreadedVector.h ColorTable.h MandelbrotSet.h
	g++ -c one_color.cpp 

ppm_menu: ppm_menu.o Image.o image_menu.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o
	g++ -o ppm_menu image_menu.o Image.o ppm_menu.o PPM.o ActionData.o MenuData.o NumberGrid.o ComplexFractal.o JuliaSet.o ThreadedGrid.o ColorTable.o MandelbrotSet.o -lpthread
ppm_menu.o: ppm_menu.cpp image_menu.h MenuData.h NumberGrid.h ComplexFractal.h JuliaSet.h ThreadedGrid.h ThreadedVector.h ColorTable.h MandelbrotSet.h
	g++ -c ppm_menu.cpp

clean:
	rm -f *.o one_color ppm_menu questions_3 image_file ascii_image *~

