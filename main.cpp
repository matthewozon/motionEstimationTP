#include <iostream>
#include <stdio.h>
#include <sstream>

#include <C_imgMatrix.h>
#include <C_motionEstimation.h>



int main(int argc, char *argv[])
{
    if(argc!=3) return -1;
    std::string file1 = argv[1];
    std::string file2 = argv[2];

    std::cout << "Input files: " << file1 << " " << file2 << std::endl;

    //display images
    C_imgMatrix<double> IM1(file1); //load file1
    C_imgMatrix<double> IM2(file2); //load file2

    IM1.display(NO_NORMALIZATION); //display image 1
    IM2.display(NO_NORMALIZATION); //display image 2


    //It's up to you!
    C_motionEstimation F("file1","file2");
    F.saveVectorField("fileX","fileY");

    //display results...
    return 0;
}




/*C_matrix<float> A(2,3);
    A=1;
    A.show();
    A(1,1)=2;
    A.show();
    std::cout << A(1,1) << std::endl;
    A.resize(4,2);
    A  = 5;
    A.show();

    C_imgMatrix<float> B("00000001.png");
    B.display(NO_NORMALIZATION);
    std::cout << B(10,10) << std::endl;

    C_imgMatrix<float> C(B);
    C.display(NO_NORMALIZATION);

    A.resize(200,300);
    A = (float) 128;
    C_imgMatrix<float> D(A);
    D.display(NO_NORMALIZATION);

    C_imgMatrix<float> E("00000002.png");
    E.display(NO_NORMALIZATION);

    C_imgMatrix<float> F(E.getNbRow(), E.getNbColumn());
    F = B-E;
    F.display(NORMALIZE);

    C_matrix<float> K = F.m_abs();
    C_matrix<float> KK = K.dotProduct(K);
    //KK.show();
    C_imgMatrix<float> GG(K);
    GG.display(NORMALIZE);

    C_imgMatrix<float> GL(KK);
    GL.display(NORMALIZE);


    return 1;
    std::string fileNameScene1 = "00000001.png";
    cimg_library::CImg<float> image(fileNameScene1.data());
    image.RGBtoBayer();
    float* G = image.data();
    std::cout << G << " " << G[0] << std::endl;
    image.height();
    image.width();
    image.depth();
    image.spectrum();
    std::cout << "height = " << image.height()  << ", width = " << image.width() << ", depth = " << image.depth() << ", spectrum = " << image.spectrum() << std::endl;
    image(10,10) = 255;
    std::cout << image(10,10) << std::endl;
    cimg_library::CImgDisplay main_disp(image,"image title");
    while (!main_disp.is_closed())
    {
        main_disp.wait();
    }
    return 0;*/
