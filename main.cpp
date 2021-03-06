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


    //It's up to you!
    C_motionEstimation F(argv[1],argv[2]);

    ///run estimation alpha=0.05
    F.computeMotionField(0.05,500);

    //save vector field
    F.saveVectorField("vectXsmall","vectYsmall");

    //display images
    F.image1->display(NORMALIZE);
    F.image2->display(NORMALIZE);

    //display vector field
    F.vectX->display(NORMALIZE);
    F.vectY->display(NORMALIZE);

    ///run estimation alpha=1
    F.computeMotionField(1.0,500);

    //save vector field
    F.saveVectorField("vectX","vectY");

    //display images
    F.image1->display(NORMALIZE);
    F.image2->display(NORMALIZE);

    //display vector field
    F.vectX->display(NORMALIZE);
    F.vectY->display(NORMALIZE);


    ///run estimation alpha=20
    F.computeMotionField(20.0,500);

    //save vector field
    F.saveVectorField("vectXlarge","vectYlarge");

    //display images
    F.image1->display(NORMALIZE);
    F.image2->display(NORMALIZE);

    //display vector field
    F.vectX->display(NORMALIZE);
    F.vectY->display(NORMALIZE);


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
