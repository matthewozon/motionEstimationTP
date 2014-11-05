use CImg lib (libpng): load png, save in a txt file so that it is possible to display it into octave


he project requires libpng that is used by CImg and it uses X11 and pthread.
So the CMakeList must include them and specify where to find them.

If CImg is not installed, you must install it using the following command line:

apt-get install cimg-dev



You may find useful this link

http://en.wikipedia.org/wiki/Horn%E2%80%93Schunck_method

http://cimg.sourceforge.net/reference/group__cimg__tutorial.html

http://cimg.sourceforge.net/index.shtml
