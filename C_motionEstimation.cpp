#include <C_motionEstimation.h>

C_motionEstimation::C_motionEstimation(std::string fileNameFrame1, std::string fileNameFrame2)
{
    //load two frames into image1 and image2
    image1 = NULL;
    image2 = NULL;
    image1 = new C_imgMatrix<double>(fileNameFrame1);
    image2 = new C_imgMatrix<double>(fileNameFrame2);



    vectX = NULL;
    vectY = NULL;
    vectX = new C_imgMatrix<double>(image1->getNbRow(), image1->getNbColumn());
    vectY = new C_imgMatrix<double>(image1->getNbRow(), image1->getNbColumn());


    imDX = NULL;
    imDY = NULL;
    imDT = NULL;
    vectXMean = NULL;
    vectYMean = NULL;
}

C_motionEstimation::~C_motionEstimation()
{
    if(image1!=NULL) delete image1;
    if(image2!=NULL) delete image2;
    if(vectX!=NULL) delete vectX;
    if(vectY!=NULL) delete vectY;
}


bool C_motionEstimation::saveVectorField(std::string fileNameVectX, std::string fileNameVectY)
{
    std::ofstream myfile;
    myfile.open (fileNameVectX.data(), std::ios::out ); //| std::ios::binary
    if(myfile.is_open())
    {
        for(unsigned short l=0 ; l<vectX->getNbRow() ; l++)
        {
            for(unsigned short c=0 ; c<vectX->getNbColumn() ; c++)
            {
                myfile << (*vectX)(l,c) << ", ";
            }
            myfile << std::endl;
        }
        myfile.close();
    }


    std::ofstream myfile2;
    myfile2.open (fileNameVectX.data(), std::ios::out );
    if(myfile2.is_open())
    {
        for(unsigned short l=0 ; l<vectY->getNbRow() ; l++)
        {
            for(unsigned short c=0 ; c<vectY->getNbColumn() ; c++)
            {
                myfile2 << (*vectY)(l,c) << ", ";
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
        for(unsigned short j=0 ; j<image1->getNbRow()-1 ; j++)
        {
            (*imDX)(i,j) = 0.25*((*image1)(i,j+1)-(*image1)(i,j) + (*image1)(i+1,j+1)-(*image1)(i+1,j) + \
                    (*image2)(i,j+1)-(*image2)(i,j) + (*image2)(i+1,j+1)-(*image2)(i+1,j));
        }
    }
    return;
}

void C_motionEstimation::derivativeY(void)
{
    //allocate the container (should check first if pointer is null)
    imDX = new C_imgMatrix<double>(image1->getNbRow(), image1->getNbColumn());
    *imDX = 0.0;
    for(unsigned short i=0 ; i<image1->getNbRow()-1 ; i++)
    {
        for(unsigned short j=0 ; j<image1->getNbRow()-1 ; j++)
        {
            (*imDX)(i,j) = 0.25*((*image1)(i+1,j)-(*image1)(i,j) + (*image1)(i+1,j+1)-(*image1)(i,j+1) + \
                    (*image2)(i+1,j)-(*image2)(i,j) + (*image2)(i+1,j+1)-(*image2)(i,j+1));
        }
    }
    return;
}

void C_motionEstimation::derivativeT(void)
{
    //allocate the container (should check first if pointer is null)
    imDX = new C_imgMatrix<double>(image1->getNbRow(), image1->getNbColumn());
    *imDX = 0.0;
    for(unsigned short i=0 ; i<image1->getNbRow()-1 ; i++)
    {
        for(unsigned short j=0 ; j<image1->getNbRow()-1 ; j++)
        {
            (*imDX)(i,j) = 0.25*((*image2)(i,j)-(*image1)(i,j) + (*image2)(i+1,j)-(*image1)(i+1,j) + \
                    (*image2)(i,j+1)-(*image1)(i,j+1) + (*image2)(i+1,j+1)-(*image1)(i+1,j+1));
        }
    }
    return;
}

double C_motionEstimation::computeAverageX(unsigned short i, unsigned short j)
{
    if(i>0 && i<(vectX->getNbRow()-1) && j>0 && j<(vectX->getNbColumn()-1))
    {
        return (1.0/6.0)*((*vectX)(i-1,j) + (*vectX)(i,j+1) + (*vectX)(i+1,j) + (*vectX)(i,j-1))\
                +(1.0/12.0)*((*vectX)(i-1,j-1) + (*vectX)(i-1,j+1) + (*vectX)(i+1,j+1) + (*vectX)(i+1,j-1));
    }
    else
    {
        return 0.0;
    }
}

double C_motionEstimation::computeAverageY(unsigned short i, unsigned short j)
{
    if(i>0 && i<(vectY->getNbRow()-1) && j>0 && j<(vectY->getNbColumn()-1))
    {
        return (1.0/6.0)*((*vectY)(i-1,j) + (*vectY)(i,j+1) + (*vectY)(i+1,j) + (*vectY)(i,j-1))\
                +(1.0/12.0)*((*vectY)(i-1,j-1) + (*vectY)(i-1,j+1) + (*vectY)(i+1,j+1) + (*vectY)(i+1,j-1));
    }
    else
    {
        return 0.0;
    }
}



void C_motionEstimation::computeAverages(void)
{
    //allocate the container (should check first if pointer is null)
    vectXMean = new C_imgMatrix<double>(image1->getNbRow(), image1->getNbColumn());
    vectYMean = new C_imgMatrix<double>(image1->getNbRow(), image1->getNbColumn());
    for(unsigned short i=0 ; i<image1->getNbRow() ; i++)
    {
        for(unsigned short j=0 ; j<image1->getNbRow() ; j++)
        {
            (*vectXMean)(i,j) = computeAverageX(i,j);
            (*vectYMean)(i,j) = computeAverageY(i,j);
        }
    }
    return;
}
