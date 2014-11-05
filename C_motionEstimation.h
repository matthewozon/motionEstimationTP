#ifndef C_MOTIONESTIMATION_H
#define C_MOTIONESTIMATION_H

#include <C_imgPng.h>

class C_motionEstimation
{
public:
    //ctor: load two images (frames of a movie)
    C_motionEstimation(std::string fileNameFrame1, std::string fileNameFrame2);

    //method that computes all iterations of Horn & Schunck method: stores the result in vectX & vectY
    bool computeMotionField(double alpha, unsigned long nbIteration){return false;}

    //the two frames
    C_imgPng<double>* image1;
    C_imgPng<double>* image2;

    //the vector field: flow vector
    C_imgPng<double>* vectX;
    C_imgPng<double>* vectY;

    //tool to save the vector field (may be useful to export result so that you can plot it using octave)
    bool saveVectorField(std::string fileNameVectX, std::string fileNameVectY){return true;}

private:
    //first order derivatives of the images
    C_imgPng<double>* imDX;
    C_imgPng<double>* imDY;
    C_imgPng<double>* imDT;

    //methods that compute the derivatives
    C_imgPng<double>* derivativeX(C_imgPng<double>* im){return NULL;}
    C_imgPng<double>* derivativeY(C_imgPng<double>* im){return NULL;}
    C_imgPng<double>* derivativeT(C_imgPng<double>* imT, C_imgPng<double>* imTDT){return NULL;}

    //compute one iteration of Horn & Schunck method: one for each component
    double computeIterationX(double alpha){return 0.0;}
    double computeIterationY(double alpha){return 0.0;}

    //might be interesting to have those two...
    double computeAverageX(unsigned short i, unsigned short j){return 0.0;}
    double computeAverageY(unsigned short i, unsigned short j){return 0.0;}

    //init vector field: choose the right method
    bool initOpticalFlow(unsigned short METHOD){return false;}

};

#endif // C_MOTIONESTIMATION_H
