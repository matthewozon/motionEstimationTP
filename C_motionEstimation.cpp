#include <C_motionEstimation.h>

C_motionEstimation::C_motionEstimation(std::string fileNameFrame1, std::string fileNameFrame2)
{
    //load two frames into image1 and image2
    image1 = new C_imgMatrix<double>(fileNameFrame1);
    image2 = new C_imgMatrix<double>(fileNameFrame2);
}

C_motionEstimation::~C_motionEstimation()
{
    if(image1!=NULL) delete image1;
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
