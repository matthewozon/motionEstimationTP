#ifndef C_IMGMATRIX_H
#define C_IMGMATRIX_H

#include <C_matrix.h> //the class inherit all method from this one

#include <CImg.h> //load and display png

#define NO_NORMALIZATION 0 //it is assumed that data to be displayed are in the range [0,255]
#define NORMALIZE 1 //the displayed values are normalized in the range [0,255]

template<class dataType> class C_imgMatrix : public C_matrix<dataType>
{
public:
    C_imgMatrix(std::string fileNamePNG);
    C_imgMatrix(unsigned short L, unsigned short C);
    C_imgMatrix(const C_imgMatrix &M);
    C_imgMatrix(const C_matrix<dataType> &M);
    virtual ~C_imgMatrix();

    void display(unsigned short NORMALIZATION);

    C_imgMatrix& operator= (C_imgMatrix const& c);
    C_imgMatrix& operator= (C_matrix<dataType> const& c);
    C_imgMatrix& operator= (dataType const& x);


};


template<class dataType> C_imgMatrix<dataType>::C_imgMatrix(std::string fileNamePNG):C_matrix<dataType>(0,0)
{
    //load image
    cimg_library::CImg<float> image(fileNamePNG.data());

    //resize container
    this->resize(image.width(), image.height());

    //store data in pointer m_A
    for(unsigned short l=0 ; l<this->m_L ; l++)
    {
        //this->m_A[l] = &((imgData->data())[l*C]);
        for(unsigned short c=0 ; c<this->m_C ; c++)
        {
            this->m_A[l][c] = image(l,c);
        }
    }
}

template<class dataType> C_imgMatrix<dataType>::C_imgMatrix(unsigned short L, unsigned short C):C_matrix<dataType>(L,C)
{
    //
}

template<class dataType> C_imgMatrix<dataType>::C_imgMatrix(const C_imgMatrix &M):C_matrix<dataType>(M)
{
    //m_fileNamePNG = M.m_fileNamePNG;
}
template<class dataType> C_imgMatrix<dataType>::C_imgMatrix(const C_matrix<dataType> &M):C_matrix<dataType>(M)
{
    //
}

template<class dataType> C_imgMatrix<dataType>::~C_imgMatrix()
{
}


template<class dataType> C_imgMatrix<dataType>& C_imgMatrix<dataType>::operator= (C_imgMatrix const& c)
{
    if(this==&c) return *this;
    if(c.getNbColumn()!=this->getNbColumn() || c.getNbRow()!=this->getNbRow()) throw "dimension matrix must agree";

    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            this->m_A[i][j] = c(i,j);
        }
    }
    return *this;
}

template<class dataType> C_imgMatrix<dataType>& C_imgMatrix<dataType>::operator= (C_matrix<dataType> const& c)
{
    if(this==&c) return *this;
    if(c.getNbColumn()!=this->getNbColumn() || c.getNbRow()!=this->getNbRow()) throw "dimension matrix must agree";

    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            this->m_A[i][j] = c(i,j);
        }
    }
    return *this;
}

template<class dataType> C_imgMatrix<dataType>& C_imgMatrix<dataType>::operator= (dataType const& x)
{
    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            this->m_A[i][j] = x;
        }
    }
    return *this;
}

template<class dataType> void C_imgMatrix<dataType>::display(unsigned short NORMALIZATION)
{
    cimg_library::CImg<dataType> image(this->m_L,this->m_C);
    if(image.spectrum()==3) image.RGBtoBayer();
    ///fill in object
    for(unsigned short l=0 ; l<this->m_L ; l++)
    {
        for(unsigned short c=0 ; c<this->m_C ; c++)
        {
            image(l,c) = (*this)(l,c);
        }
    }
    cimg_library::CImgDisplay main_disp(image,"My image",0);
    while (!main_disp.is_closed())
    {
        main_disp.wait();
    }
}

#endif // C_IMGMATRIX_H
