//good to go!

#ifndef C_MATRIX_H
#define C_MATRIX_H

#include <stdlib.h>
#include <iostream>
#include <C_vector.h>


const double epsilon=0.0000000001;


#define ABS(a) ((a) > 0 ? (a) : -(a))

#define NEW_VERSION

//this is a template, meaning that you need to specify the type when you instanciate a object.
template<class dataType> class C_matrix
{
public:
    //constructors and destructors
    #ifdef NEW_VERSION
    C_matrix();
    #endif
    C_matrix(unsigned short _L, unsigned short _C);
    C_matrix(const C_matrix &M);
    C_matrix(dataType **_M, unsigned short _L, unsigned short _C);
    virtual ~C_matrix();


    //IO methods
    #ifndef NEW_VERSION
    dataType get(unsigned short i, unsigned short j)const;
    bool set(unsigned short i, unsigned short j, dataType x);
    #else
    dataType& operator()(const unsigned int l, const unsigned int c);
    const dataType& operator()(const unsigned int l, const unsigned int c) const;
    #endif

    //overload operators
    C_matrix& operator= (C_matrix const& c);
    C_matrix& operator= (dataType const& x);
    C_matrix& operator+ (C_matrix const& c);
    C_matrix& operator+ (dataType const& x);
    C_matrix& operator- (C_matrix const& c);
    C_matrix& operator- (dataType const& x);
    C_matrix& operator* (C_matrix const& c);
    C_vector<dataType>& operator* (C_vector<dataType> const& c);
    C_matrix& operator* (const dataType& x);

    //
    C_matrix& m_abs(void);
    C_matrix<dataType>& dotProduct(C_matrix const& B);
    //C_matrix<dataType>& dotDiv(C_matrix const& B);
    C_matrix<dataType>& dotProduct(C_matrix& B);
    //C_matrix<dataType>& dotDiv(C_matrix& B);

    //tools for linear system solving
    C_matrix& Transpose(void);
    C_matrix<dataType>* LU(void);
    C_matrix<dataType>* LUP(C_vector<int> &Indice);
    C_matrix<dataType>* LMU(void);
    C_vector<dataType>* LineAlgEq_LU(C_vector<dataType> &B);

    //other tools
    unsigned short getNbRow(void)const {return m_L;}
    unsigned short getNbColumn(void)const {return m_C;}
    void show(void);

    //to use carefully
    #ifdef NEW_VERSION
    bool resize(unsigned short newL, unsigned short newC);
    #endif

protected:
    unsigned short m_L;
    unsigned short m_C;
    dataType** m_A;

    //privates tools to allocate and free memory
    dataType** allocate(unsigned short M, unsigned short N);
    void deallocation(dataType** B, unsigned short M, unsigned short N);

};
#ifdef NEW_VERSION
template<class dataType> C_matrix<dataType>::C_matrix()
{
    m_L=0;
    m_C=0;
    m_A=NULL;
}
#endif
template<class dataType> C_matrix<dataType>::C_matrix(unsigned short _L, unsigned short _C) : m_L(_L),m_C(_C)
{
    m_A = allocate(m_L,m_C);
    if(m_A==NULL)
    {
        m_L=0;
        m_C=0;
    }

}

template<class dataType> C_matrix<dataType>::C_matrix(dataType **_M, unsigned short _L, unsigned short _C) : m_L(_L),m_C(_C)
{
    m_A = allocate(m_L, m_C);
    if(m_A==NULL)
    {
        m_L=0;
        m_C=0;
    }
    else
    {
        for(unsigned short i=0 ; i<m_L ; i++)
        {
            for(unsigned short j=0 ; j<m_C ; j++)
                m_A[i][j] = _M[i][j];
        }
    }
}

template<class dataType> C_matrix<dataType>::C_matrix(const C_matrix &X)
{
    m_L = X.getNbRow();
    m_C = X.getNbColumn();
    m_A = allocate(m_L, m_C);
    if(m_A==NULL)
    {
        m_L=0;
        m_C=0;
    }
    else
    {
        for(unsigned short i=0 ; i<m_L ; i++)
        {
            for(unsigned short j=0 ; j<m_C ; j++)
            {
                #ifndef NEW_VERSION
                m_A[i][j] = X.get(i,j);
                #else
                m_A[i][j] = X(i,j);
                #endif
            }
        }
    }

}

template<class dataType> C_matrix<dataType>::~C_matrix()
{
    deallocation(m_A,m_L,m_C);
}

//to use carefully
#ifdef NEW_VERSION
template<class dataType> bool C_matrix<dataType>::resize(unsigned short newL, unsigned short newC)
{
    deallocation(m_A,m_L,m_C);
    m_A = NULL;
    m_L = 0;
    m_C = 0;
    m_A = allocate(newL, newC);
    if(m_A==NULL) return false;
    m_L = newL;
    m_C = newC;
    return true;
}
#endif

template<class dataType> dataType** C_matrix<dataType>::allocate(unsigned short M, unsigned short N)
{
    dataType** A = new dataType*[M];
    if(A==NULL) return A;

    for(unsigned short i=0 ; i<M ; i++)
        A[i] = new dataType[N];

    //should check if all allocation is OK
    bool cond=true;
    for(unsigned short i=0 ; i<M ; i++)
    {
        if(A[i]==NULL)
        {
            cond=false;
            i=M;
        }
    }
    if(!cond)
    {
        deallocation(A,M,N);
    }
    return A;
}

template<class dataType> void C_matrix<dataType>::deallocation(dataType** B, unsigned short M, unsigned short N)
{
    for(unsigned short i=0 ; i<M ; i++)
    {
        if(B[i]!=NULL)
        {
            delete B[i];
        }
    }
    delete B;
    B=NULL;
    return;
}

template<class dataType> void C_matrix<dataType>::show(void)
{
    for(unsigned short i=0 ; i<m_L ; i++)
    {
        for(unsigned short j=0 ; j<m_C ; j++)
        {
            std::cout << m_A[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

#ifndef NEW_VERSION
template<class dataType> dataType C_matrix<dataType>::get(unsigned short i, unsigned short j) const
{
    if(i<m_L && j<m_C)
    {
        return m_A[i][j];
    }
    else
    {
        throw "index must be positive and smaller than max length of vector";
    }

}

template<class dataType> bool C_matrix<dataType>::set(unsigned short i, unsigned short j, dataType x)
{
    if(i<m_L && j<m_C)
    {
        m_A[i][j] = x;
        return true;
    }
    else
    {
        return false;
        //throw "index must be positive and smaller than max length of vector";
    }

}
#endif


template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator= (C_matrix const& c)
{
    if(this==&c) return *this;
    if(c.getNbColumn()!=this->getNbColumn() || c.getNbRow()!=this->getNbRow()) throw "dimension matrix must agree";

    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            #ifndef NEW_VERSION
            this->m_A[i][j] = c.get(i,j);
            #else
            this->m_A[i][j] = c(i,j);
            #endif
        }
    }


    return *this;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator= (dataType const& x)
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




template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator+ (C_matrix const& c)
{
    if(c.getNbColumn()!=this->getNbColumn() || c.getNbRow()!=this->getNbRow()) throw "dimension matrix must agree";
    C_matrix* B = new C_matrix(m_L,m_C);
    for(unsigned short i=0 ; i<m_L ; i++)
    {
        for(unsigned short j=0 ; j<m_C ; j++)
        {
            #ifndef NEW_VERSION
            B->set(i, j, this->m_A[i][j] + c.get(i,j));
            #else
            (*B)(i,j) = this->m_A[i][j] + c(i,j);
            #endif
        }
    }
    return *B;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator+ (dataType const& x)
{
    C_matrix* B = new C_matrix(m_L,m_C);
    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            #ifndef NEW_VERSION
            B->set(i, j, this->m_A[i][j] + x);
            #else
            (*B)(i,j) = this->m_A[i][j] + x;
            #endif
        }
    }

    return *B;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator- (C_matrix const& c)
{
    if(c.getNbColumn()!=this->getNbColumn() || c.getNbRow()!=this->getNbRow()) throw "dimension matrix must agree";
    C_matrix* B = new C_matrix(m_L,m_C);
    for(unsigned short i=0 ; i<m_L ; i++)
    {
        for(unsigned short j=0 ; j<m_C ; j++)
        {
            #ifndef NEW_VERSION
            B->set(i, j, this->m_A[i][j] - c.get(i,j));
            #else
            (*B)(i,j) = this->m_A[i][j] - c(i,j);
            #endif
        }
    }
    return *B;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator- (dataType const& x)
{
    C_matrix* B = new C_matrix(m_L,m_C);
    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            B->set(i, j, this->m_A[i][j] - x);
            #ifndef NEW_VERSION
            B->set(i, j, this->m_A[i][j] - x);
            #else
            (*B)(i,j) = this->m_A[i][j] - x;
            #endif
        }
    }

    return *B;
}


template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator* (C_matrix const& c)
{
    if(this->getNbColumn()!=c.getNbRow()) throw "mismatch dimension matrix";

    C_matrix* B = new C_matrix(this->getNbRow(),c.getNbColumn());
    for(unsigned short i=0 ; i<B->getNbRow() ; i++)
    {
        for(unsigned short j=0 ; j<B->getNbColumn() ; j++)
        {
            dataType S = (dataType) 0;
            for(unsigned short k=0 ; k<m_C ; k++)
            {
                #ifndef NEW_VERSION
                S += this->m_A[i][k]*c.get(k,j);
                #else
                S += this->m_A[i][k]*c(k,j);
                #endif
            }

            #ifndef NEW_VERSION
            B->set(i, j, S);
            #else
            (*B)(i,j) = S;
            #endif
        }
    }
    return *B;
}

template<class dataType> C_vector<dataType>& C_matrix<dataType>::operator* (C_vector<dataType> const& c)
{
    if(this->getNbColumn()!=c.length()) throw "mismatch dimension matrix";
    C_vector<dataType>* Y = new C_vector<dataType>(this->getNbRow());
    for(unsigned short i=0 ; i<Y->length() ; i++)
    {
        dataType S = (dataType) 0;
        for(unsigned short k=0 ; k<c.length() ; k++)
            S += this->m_A[i][k]*c[k];

        Y->set(i,S);
    }

    return *Y;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::operator* (const dataType& x)
{
    C_matrix* B = new C_matrix(m_L,m_C);
    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            #ifndef NEW_VERSION
            B->set(i, j, this->m_A[i][j]*x);
            #else
            (*B)(i,j) = this->m_A[i][j]*x;
            #endif
        }
    }

    return *B;
}

#ifdef NEW_VERSION
template<class dataType> dataType& C_matrix<dataType>::operator()(const unsigned int l, const unsigned int c)
{
    return m_A[l][c];
}
template<class dataType> const dataType& C_matrix<dataType>::operator()(const unsigned int l, const unsigned int c) const
{
    return m_A[l][c];
}
#endif



template<class dataType> C_matrix<dataType>& C_matrix<dataType>::m_abs(void)
{
    C_matrix* B = new C_matrix(this->m_L,this->m_C);
    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            #ifndef NEW_VERSION
            B->set(i, j, ABS(this->m_A[i][j]));
            #else
            (*B)(i,j) = ABS(this->m_A[i][j]);
            #endif
        }
    }
    return *B;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::Transpose(void)
{
    C_matrix* B = new C_matrix(this->m_C,this->m_L);
    for(unsigned short i=0 ; i<this->m_L ; i++)
    {
        for(unsigned short j=0 ; j<this->m_C ; j++)
        {
            #ifndef NEW_VERSION
            B->set(j, i, this->m_A[i][j]);
            #else
            (*B)(j,i) = this->m_A[i][j];
            #endif
        }
    }
    return *B;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::dotProduct(C_matrix const& B)
{
    if(this->getNbRow()!=B.getNbRow() || this->getNbColumn()!=B.getNbColumn()) throw "mismatch dimension matrix";
    C_matrix* C = new C_matrix(this->getNbRow(),this->getNbColumn());
    for(unsigned short i=0 ; i<C->getNbRow() ; i++)
    {
        for(unsigned short j=0 ; j<C->getNbColumn() ; j++)
        {
            #ifndef NEW_VERSION
            C->set(i, j, this->get(i,j)*B.get(i,j));
            #else
            (*C)(i,j) = (*this)(i,j)*(B(i,j));
            #endif
        }
    }
    return *C;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::dotProduct(C_matrix& B)
{
    if(this->getNbRow()!=B.getNbRow() || this->getNbColumn()!=B.getNbColumn()) throw "mismatch dimension matrix";
    C_matrix* C = new C_matrix(this->getNbRow(),this->getNbColumn());
    for(unsigned short i=0 ; i<C->getNbRow() ; i++)
    {
        for(unsigned short j=0 ; j<C->getNbColumn() ; j++)
        {
            #ifndef NEW_VERSION
            C->set(i, j, this->get(i,j)*B.get(i,j));
            #else
            (*C)(i,j) = ((*this)(i,j))*(B(i,j));
            #endif
        }
    }
    return *C;
}

/*template<class dataType> C_matrix<dataType>& C_matrix<dataType>::dotDiv(C_matrix const& B)
{
    if(this->getNbRow()!=B.getNbRow() || this->getNbColumn()!=B.getNbColumn()) throw "mismatch dimension matrix";
    C_matrix* C = new C_matrix(this->getNbRow(),this->getNbColumn());
    for(unsigned short i=0 ; i<C->getNbRow() ; i++)
    {
        for(unsigned short j=0 ; j<C->getNbColumn() ; j++)
        {
            #ifndef NEW_VERSION
            if(ABS(B.get(i,j))>epsilon)
            {
                C->set(i, j, this->get(i,j)/B.get(i,j));
            }
            else
            {
                C->set(i, j, 0.0);
            }

            #else
            if(ABS(B(i,j))>epsilon)
            {
                (*C)(i,j) = ((*this)(i,j))/(B(i,j));
            }
            else
            {
                (*C)(i,j) = 0;
            }
            #endif
        }
    }
    return *C;
}

template<class dataType> C_matrix<dataType>& C_matrix<dataType>::dotDiv(C_matrix& B)
{
    if(this->getNbRow()!=B.getNbRow() || this->getNbColumn()!=B.getNbColumn()) throw "mismatch dimension matrix";
    C_matrix* C = new C_matrix(this->getNbRow(),this->getNbColumn());
    for(unsigned short i=0 ; i<C->getNbRow() ; i++)
    {
        for(unsigned short j=0 ; j<C->getNbColumn() ; j++)
        {
            #ifndef NEW_VERSION
            if(ABS(B.get(i,j))>epsilon)
            {
                C->set(i, j, this->get(i,j)/B.get(i,j));
            }
            else
            {
                C->set(i, j, 0.0);
            }

            #else
            if(ABS(B(i,j))>epsilon)
            {
                (*C)(i,j) = ((*this)(i,j))/(B(i,j));
            }
            else
            {
                (*C)(i,j) = 0;
            }
            #endif
        }
    }
    return *C;
}*/








//**********************
//Décomposition LU
//**********************
template<class dataType> C_matrix<dataType>* C_matrix<dataType>::LU(void)
{
    C_matrix<dataType>* MLU = new C_matrix<dataType>(*this);
    C_matrix<dataType> tmp(m_L,m_C);


    std::cout<<"\nLU Decomposition Steps\n";
    std::cout<<"------------------------\n";

    if(m_L != m_C)
    {
        std::cout<<"\nColumn and Rows must be equal"<<std::endl;
    }
    else
    {
        for(int j=0; j<m_C; j++)
        {

            #ifndef NEW_VERSION
            if(ABS(MLU->get(j,j))<epsilon)
            #else
            if(ABS((*MLU)(j,j))<epsilon)
            #endif
            {
                std::cout<<"Pivot is equal to zero..."<<std::endl;
                break; //pivot nul
            }
            else
            {

                MLU->show();
                //Division colonne j par pivot
                for(int i=j+1; i<m_L; i++)
                {
                    #ifndef NEW_VERSION
                    MLU->set(i,j, MLU->get(i,j)/MLU->get(j,j));
                    #else
                    (*MLU)(i,j) = (*MLU)(i,j)/(*MLU)(j,j);
                    #endif
                }

                //Complément de Shur
                for(int jj=j+1; jj<m_C; jj++)
                {
                    for(int ii=j+1; ii<m_L; ii++)
                    {
                        #ifndef NEW_VERSION
                        tmp.set(ii,jj,MLU->get(j,jj)*MLU->get(ii,j));
                        #else
                        tmp(ii,jj) = (*MLU)(j,jj)*(*MLU)(ii,j);
                        #endif
                    }
                }
                for(int jj=j+1; jj<m_C; jj++)
                {
                    for(int ii=j+1; ii<m_L; ii++)
                    {
                        #ifndef NEW_VERSION
                        MLU->set(ii,jj, MLU->get(ii,jj)-tmp.get(ii,jj));
                        #else
                        (*MLU)(ii,jj) = (*MLU)(ii,jj)-tmp(ii,jj);
                        #endif
                    }
                }

            }
        }
    }
    std::cout<<"\t\tEnd LU Decomposition\n";
    //MLU.Affiche();
    return MLU;
}












//******************************
//Décomposition LU + Permutation
//******************************
template<class dataType> C_matrix<dataType>* C_matrix<dataType>::LUP(C_vector<int> &Indice)
{
    C_matrix<dataType>* MLUP = new C_matrix<dataType>(*this);
    C_matrix<dataType> tmp(m_L,m_C);
    dataType Tmp;

    std::cout<<"\nLUP Decomposition Steps\n";
    std::cout<<"------------------------\n";

    if(m_L != m_C){
        std::cout<<"\nColumn and Rows must be equal"<<std::endl;
    }
    else
    {

        //Indice contiendra les permutations
        for(int j=0; j<m_C; j++)
            Indice.set(j,(dataType) j);

        //Pour tous les pivots
        for(int j=0; j<m_C; j++)
        {
            #ifndef NEW_VERSION
            if(ABS(MLUP->get(j,j))<epsilon)
            #else
            if(ABS((*MLUP)(j,j))<epsilon)
            #endif
            {
                std::cout<<"Pivot is equal to zero..."<<std::endl;
                break; //pivot nul
            }
            else
            {
                MLUP->show();

                //Recherche du pivot le plus grand
                #ifndef NEW_VERSION
                dataType max=MLUP->get(j,j);
                #else
                dataType max=(*MLUP)(j,j);
                #endif
                int indmax=j;
                for(int i=j+1; i<m_L; i++)
                {
                    #ifndef NEW_VERSION
                    if(MLUP->get(i,j)>max)
                    {
                        max=MLUP->get(i,j);
                        indmax=i;
                    }
                    #else
                    if((*MLUP)(i,j)>max)
                    {
                        max=(*MLUP)(i,j);
                        indmax=i;
                    }
                    #endif
                }

                //Echange des lignes
                for(int jj=0;jj<m_C;jj++)
                {
                    #ifndef NEW_VERSION
                    Tmp = MLUP->get(j,jj);
                    MLUP->set(j,jj,MLUP->get(indmax,jj));
                    MLUP->set(indmax,jj,Tmp);
                    #else
                    Tmp = (*MLUP)(j,jj);
                    (*MLUP)(j,jj) = (*MLUP)(indmax,jj);
                    (*MLUP)(indmax,jj) = Tmp;
                    #endif

                }
                //Mise à jour du tableau Indice (=les perumtations)
                Indice.set(j,indmax);
                Indice.set(indmax,j);

                //Division colonne j par pivot
                for(int i=j+1; i<m_L; i++)
                {
                    #ifndef NEW_VERSION
                    MLUP->set(i,j,MLUP->get(i,j)/MLUP->get(j,j));
                    #else
                    (*MLUP)(i,j) = (*MLUP)(i,j)/(*MLUP)(j,j);
                    #endif
                }

                //Complément de Shur
                for(int jj=j+1; jj<m_C; jj++)
                {
                    for(int ii=j+1; ii<m_L; ii++)
                    {
                        #ifndef NEW_VERSION
                        tmp.set(ii,jj, MLUP->get(j,jj)*MLUP->get(ii,j));
                        #else
                        tmp(ii,jj) = (*MLUP)(j,jj)*(*MLUP)(ii,j);
                        #endif
                    }
                }
                for(int jj=j+1; jj<m_C; jj++)
                {
                    for(int ii=j+1; ii<m_L; ii++)
                    {
                        #ifndef NEW_VERSION
                        MLUP->set(ii,jj, MLUP->get(ii,jj)-tmp.get(ii,jj));
                        #else
                        (*MLUP)(ii,jj) = (*MLUP)(ii,jj)-tmp(ii,jj);
                        #endif
                    }
                }

            }
        }
    }

    std::cout<<"\t\tEnd LUP Decomposition\n";
    //MLUP.Affiche();
    return MLUP;
}







//**********************
//Produit L*U
//**********************
template<class dataType> C_matrix<dataType>* C_matrix<dataType>::LMU(void)
{
    C_matrix<dataType>* L = new C_matrix<dataType>(m_L,m_C);
    C_matrix<dataType>* U = new C_matrix<dataType>(m_L,m_C);
    C_matrix<dataType>* LMU = new C_matrix<dataType>(m_L,m_C);


    //Matrice L
    for(int i=0;i<m_L;i++)
    {
        L->set(i,i,1);
        for (int j=0;j<i; j++)
        {
            #ifndef NEW_VERSION
            L->set(i,j,this->get(i,j));
            #else
            (*L)(i,j) = (*this)(i,j);
            #endif
        }
    }

    //Matrice L
    for(int i=0;i<m_L;i++)
    {
        for (int j=i;j<m_C; j++)
        {
            #ifndef NEW_VERSION
            U->set(i,j,this->get(i,j));
            #else
            (*U)(i,j) = (*this)(i,j);
            #endif
        }
    }

    L->show();
    U->show();

    *LMU = *L * *U;

    delete L;
    delete U;
    return LMU;

}


//**********************************
//Résolution du système MX=B avec LU
//**********************************
template<class dataType> C_vector<dataType>* C_matrix<dataType>::LineAlgEq_LU(C_vector<dataType> &B)
{

    C_matrix<dataType>* MLU = LU();
    C_vector<dataType>* X = new  C_vector<dataType>(m_C);
    C_vector<dataType>* Y = new  C_vector<dataType>(m_C);


    //Solve for LY=B
    for(int i=0;i<m_L;i++)
    {
        Y->set(i,B[i]);
        for(unsigned short j=0;j<i;j++)
        {
            #ifndef NEW_VERSION
            Y->set(i,(*Y)[i] - MLU->get(i,j)*(*Y)[j]);
            #else
            Y->set(i,(*Y)[i] - (*MLU)(i,j)*(*Y)[j]);
            #endif
        }
    }

    //Solve for UX=Y
    for(int i=m_L-1;i>=0;i--)
    {
        X->set(i, (*Y)[i]);
        for(int j=m_L-1;j>i;j--)
        {
            #ifndef NEW_VERSION
            X->set(i,(*X)[i] - MLU->get(i,j)*(*X)[j]);
            #else
            X->set(i,(*X)[i] - (*MLU)(i,j)*(*X)[j]);
            #endif
        }
        #ifndef NEW_VERSION
        X->set(i,(*X)[i]/MLU->get(i,i));
        #else
        X->set(i,(*X)[i]/(*MLU)(i,i));
        #endif
    }
    delete Y;
    delete MLU;
    return X;
}
/**/

#endif // C_MATRIX_H
