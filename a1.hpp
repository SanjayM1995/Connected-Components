/*  YOUR_FIRST_NAME  Sanjay
 *  YOUR_LAST_NAME   Muthu Manickam
 *  YOUR_UBIT_NAME   sanjaymu
 */

#ifndef A1_HPP
#define A1_HPP

#include <unistd.h>
#include <vector>
#include <mpi.h>
int connected_components(std::vector<signed char>& A, int n, int q, const char* out, MPI_Comm comm) {
    // ...
    int length,rank,size,max,c1;
    MPI_Comm_rank(comm,&rank);
    int col = rank % q;
    int row = rank / q;
    length = n/q;
    int length1 = n/q;
    std::vector<int> p;
    std::vector<int> v;
    std::vector<int> temp;
    std::vector<int> comp(length*length,0);
    std::vector<int> comp1(length*length,0);
    std::vector<int> pprime(length*length,0);
    std::vector<int> temp1(length,0);
    std::vector<int> m(length*length,0);
    std::vector<int> t(length1*length1,0);
    for(int i=0;i<A.size();++i)
    {
      if(static_cast<int>(A[i]) == 1)
      {
        p.push_back((i/length)+(row*length));
      }
      else
      {
        p.push_back(-1);
      }
    }
    MPI_Barrier(comm);
  /*sleep(rank);
    std::cout<<"P :\n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << p[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for (int i = 0; i < length; ++i) {
        max=0;
        for (int j = 0; j < length; ++j)

          if(max<p[j*length+i])
            max = p[j*length+i];
        for (int j = 0; j < length; ++j)
        {
            p[j*length+i] = max;
        }

    }
    MPI_Barrier(comm);
    MPI_Comm_split(comm,col,rank,&c1);
    MPI_Allreduce(p.data(),m.data(),(length*length),MPI_INT,MPI_MAX,c1);
    MPI_Comm_free(&c1);
    MPI_Barrier(comm);
    for(int i=0;i<m.size();i++)
    {
      p[i] = m[i];
      comp[i] = m[i];
    }
    MPI_Barrier(comm);
    /*sleep(rank);
    std::cout<<"P Init : \n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << p[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for(int i=0;i<A.size();++i)
    {
      if(static_cast<int>(A[i])==1)
      {
        m[i]=p[i];
      }
      else
      {
        m[i] = 0;
      }
    }
    MPI_Barrier(comm);
    /*sleep(rank);
    std::cout<<"M : \n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << m[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for (int i = 0; i < length; ++i) {
        max=0;
        for (int j = 0; j < length; ++j)
          if(max<m[i*length+j])
            max = m[i*length+j];
        for (int j = 0; j < length; ++j)
        {
            m[i*length+j] = max;
        }

    }
    MPI_Barrier(comm);
    MPI_Comm_split(comm,row,rank,&c1);
    MPI_Allreduce(m.data(),t.data(),(length*length),MPI_INT,MPI_MAX,c1);
    /*MPI_Barrier(comm);
    sleep(rank);
    std::cout<<"T : \n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << t[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for(int i=0;i<length;i++)
    {
      for(int j=0;j<length;j++)
      {
        if(t[i*length+j]==j+(length*col))
        {
          m[i*length+j] = p[i*length+j];
        }
        else
        {
          m[i*length+j] = 0;
        }
      }
    }
    MPI_Barrier(comm);
    /*sleep(rank);
    std::cout<<"M1 : \n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << m[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for (int i = 0; i < length; ++i) {
        max=0;
        for (int j = 0; j < length; ++j)
          if(max<m[i*length+j])
            max = m[i*length+j];
        for (int j = 0; j < length; ++j)
        {
            m[i*length+j] = max;
        }
    }
    MPI_Barrier(comm);
    MPI_Comm_split(comm,row,rank,&c1);
    MPI_Allreduce(m.data(),pprime.data(),(length*length),MPI_INT,MPI_MAX,c1);
    MPI_Barrier(comm);
    /*sleep(rank);
    std::cout<<"P Prime: \n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << pprime[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for(int i=0;i<length;i++)
    {
      for(int j=0;j<length;j++)
      {
        if(p[j*length+i]==j+(length*row))
        {
          m[j*length+i] = pprime[j*length+i];
        }
        else
        {
          m[j*length+i] = 0;
        }
      }
    }
    MPI_Barrier(comm);
    /*sleep(rank);
    std::cout<<"M2 : \n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << m[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for (int i = 0; i < length; ++i) {
        max=0;
        for (int j = 0; j < length; ++j)
          if(max<m[i*length+j])
            max = m[i*length+j];
        for (int j = 0; j < length; ++j)
        {
            m[i*length+j] = max;
        }
    }
    MPI_Barrier(comm);
    MPI_Comm_split(comm,row,rank,&c1);
    MPI_Allreduce(m.data(),t.data(),(length*length),MPI_INT,MPI_MAX,c1);
    MPI_Barrier(comm);
    /*sleep(rank);
    std::cout<<"T 2 : \n";
    std::cout<<"Rank :"<<krank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << t[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);*/
    for(int i=0;i<(length*length);i++)
    {
      if(t[i]>pprime[i])
      {
        p[i]=t[i];
        comp1[i]=t[i];
      }
      else
      {
        p[i]=pprime[i];
        comp1[i]=pprime[i];
      }
    }
    MPI_Barrier(comm);
    #ifdef DEBUG
    sleep(rank);
    std::cout<<"P Final : \n";
    std::cout<<"Rank :"<<rank<<"\n";
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j)
        std::cout << p[i * length + j] << " ";
        std::cout << std::endl;
    }
    MPI_Barrier(comm);
    #endif
    return -1;
} // connected_components

#endif // A1_HPP
