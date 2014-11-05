#include <C_motionEstimation.h>

C_motionEstimation::C_motionEstimation(std::string fileNameFrame1, std::string fileNameFrame2)
{
    //load two frames into image1 and image2
    image1 = NULL;
    image2 = NULL;
    image1 = new C_imgMatrix<double>(fileNameFrame1);
    image2 = new C_imgMatrix<double>(fileNameFrame2);
}

C_motionEstimation::~C_motionEstimation()
{
    if(image1!=NULL) delete image1;
    if(image2!=NULL) delete image2;
}


bool C_motionEstimation::saveVectorField(std::string fileNameVectX, std::string fileNameVectY)
{
    std::ofstream myfile;
    myfile.open (fileNameVectX.data(), std::ios::out ); //| std::ios::binary
    if(myfile.is_open())
    {
        for(unsigned short l=0 ; l<vectX->getNbRow() ; l++)
        {
            for(unsigned short c=0 ; c<vectX->getNbRow() ; c++)
            {
                myfile << 1 << ", ";
            }
            myfile << std::endl;
        }
        myfile.close();
    }


    std::ofstream myfile2;
    if(myfile2.is_open())
    {
        for(unsigned short l=0 ; l<vectY->getNbRow() ; l++)
        {
            for(unsigned short c=0 ; c<vectY->getNbRow() ; c++)
            {
                myfile2 << 1 << ", ";
            }
            myfile2 << std::endl;
        }
        myfile2.close();
    }
    return true;
}

void C_motionEstimation::derivativeX(void)
{
    //allocate the container (should check first if pointer is null)
    imDX = new C_imgMatrix<double>(image1->getNbRow(), image1->getNbColumn());
    *imDX = 0.0;
    for(unsigned short i=0 ; i<image1->getNbRow()-1 ; i++)
    {
        for(unsigned short j=j ; j<image1->getNbRow()-1 ; j++)
        {
            (*imDX)(i,j) = 0.25*((*image1)(i,j+1)-(*image1)(i,j) + (*image1)(i+1,j+1)-(*image1)(i+1,j) + \
                    (*image2)(i,j+1)-(*image2)(i,j) + (*image2)(i+1,j+1)-(*image2)(i+1,j));
        }
    }
    return;
}
