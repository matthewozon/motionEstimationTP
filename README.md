use CImg lib (libpng): load png, save in a txt file so that it is possible to display it into octave


he project requires libpng that is used by CImg and it uses X11 and pthread.
So the CMakeList must include them and specify where to find them.

If CImg is not installed, you must install it using the following command line:

apt-get install cimg-dev

but you need a sudo access. If you do not have it, you may clone the git repository so that you don't have to install:

git clone http://git.code.sf.net/p/cimg/source CImg

but you should change the CMakeList to specify the directory where to find the CImg.h



You may find useful this link

http://en.wikipedia.org/wiki/Horn%E2%80%93Schunck_method

http://cimg.sourceforge.net/reference/group__cimg__tutorial.html

http://cimg.sourceforge.net/index.shtml


