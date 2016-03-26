#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include<ctime>
#include<cstdio>
#include<typeinfo>


#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

#include <vector>


using namespace std;

int N=4;
int L=10;
int C [50][10];
int D [50][10];


//int a[L];


int main ()
{
//Constructing the Root Partition

    int a[10]={1,1,0,0,0,1,1,0,0,0};
    cout<<endl<<"Root Partition= ";
    for (int i = 0; i < L; i++)
        cout << a[i];
    cout<<endl;


    ////////////////////////////////////////////////////////////////

vector<int> OdSequence;//vector to be modified to store Od operation sequence
vector<int> NumberState;//vector to contain the number of states
int BigM [1000][L];

 for (int i = 0; i < L ; i++)//1st row of BigM is the root partition
   { BigM [0][i]=a[i];
   }
 NumberState.push_back(0);

int mstart=0;
int mstop=1;

//////////////////////// Main Calculation ///////////////////////////////////

do{
     //int m=0;
    for (int m=mstart; m<mstop;m++) //m goes over a newly generated block of states
    {
     for (int d=1; d<L; d++)  // d-in O_d operator, applying Od to states in the block 1-by-1
       {
         vector<int> p; //vector to store positions of the movable particles

         for (int i=0; i<L; i++) //storing positions of the movable particles
           {
                if ((BigM [m][i]==1)&&(BigM [m][i+d]==0)&&(i+d<L))
                {int j=i; p.push_back(j);}
           }

    /*   cout<<"p= ";
         for (int i = 0; i < p.size(); i++)
                 {cout << p[i];
                 // NumberState.push_back(Tnstart+i);
                 }
         cout<<endl;
    */
         //to include newly added states to the check, need an upper bound nmax
         int nmax=NumberState.size();

  //////////////////////////////////////////////////////////////////////////////////
         //performing O_d operation on the root partition

         for (int i=0; i<p.size(); i++)
           {
             //making rows of the C matrix(C-temparily store generated states)
                 for (int l=0; l<L; l++)
                 {
                     C [i][l]= BigM [m][l];
                     C [i][p[i]]=0; C [i][p[i]+d]=1;

                 }

  /////////////////// Check for equivalent states ///////////////////////
         //adding above new states to the Big Matrix (check for equivalent states to be added)

                 int nadd=0;
                 bool check = false;
                 for (int n=0; n<nmax; n++)
                 {
                     for (int j=0; j<L; j++)
                     {
                         check= false;
                         if (C[i][j] == BigM[n][j]) check= true;

                         else  break; //if any two elements are not equal break from j loop

                     }

                     if (check == true) break; //if C-row in consideration matches to any row, break from n loop

                 }
                 if (check == false)
                             {
                                 for (int k=0; k<L; k++){
                                   BigM [nmax][k]=C[i][k];
                                 }
                                 nadd++;
                                 NumberState.push_back(nmax+i);

                             }
                 nmax=nmax+nadd;

           }

    ////////////////////////////////////////////////////////////////////////////////////////////

 /*        //printing out C[i][j]
        cout<<"C matrix"<<endl;
         for (int i=0; i<p.size(); i++)
                 {
                         for(int j=0; j<L; j++)
                         {
                                  cout<< C[i][j];
                         }
                         cout<<'\n';
                 }
        // cout<<endl;
    cout<<" NS= "<<NumberState.size()<<endl;
    cout<<endl;
 */
       }

    }

    mstart=mstop;  //defines the starting point of new block of states
    mstop= NumberState.size();  //defines the stopping point of new block of states

 } while (mstart != mstop);  // not equal means no further new states are generated

/////////////////////////////// End of Main Calculation ///////////////////////////////////////

//printing the big matrix with distinct states

cout<<endl<<"States="<<endl;
  for (int i=0; i<NumberState.size(); i++)
  {
      for (int j=0; j<L; j++)
      {
          cout<<BigM[i][j];
      }
      cout<<'\n';
  }
        cout<<endl;

cout<<"Total number of states= "<< NumberState.size()<<endl;
cout<<endl;

///////////////// Finding states that satisfy the GPP ///////////////////////////

int GPPM[500][L];//matrix to store states satisfying GPP
vector<int> GPPstates;//vector to store the #of GPP states

for (int n=0; n<NumberState.size(); n++)
{
    bool GPPCheck=false;

    for (int i=0; i<L-4; i++)
    {
        int particles=0;
        particles= BigM[n][i]+BigM[n][i+1]+BigM[n][i+2]+BigM[n][i+3]+BigM[n][i+4];

        if (particles>2)
        {
            GPPCheck=true;
            break;
        }
    }
    if (GPPCheck == true) continue;
    else
    {
        int GPPn=GPPstates.size();
        for (int j=0; j<L; j++)
        {
            GPPM[GPPn][j]= BigM[n][j];
        }
        GPPstates.push_back(n);
    }
}

//printing the GPP matrix

cout<<endl<<"States satisfying the GPP="<<endl;
  for (int i=0; i<GPPstates.size(); i++)
  {
      for (int j=0; j<L; j++)
      {
          cout<<GPPM[i][j];
      }
      cout<<'\n';
  }
        cout<<endl;

cout<<"Total number of states satisfying the GPP= "<< GPPstates.size()<<endl;
cout<<endl;

/////////////////////////////////////////////////////////////////////////

////////////////////////// Squeezing-in Zeros //////////////////////////

int rmax;//highest occupied orbital

for (int j=L-1; j>=0; j--)
{
   if (a[j]!=0)
   {
       rmax=j;
       break;
   }
}
//cout<<"rmax= "<<rmax<<endl;

vector<int> SqStates;//vector to store the # of states
SqStates.push_back(0);//root partition

vector<int> Inserter;//vector to contain the places where zero's could be inserted
Inserter.push_back(0);//r=0 orbital is always a place to insert a zero

for (int j=0; j<L-1; j++)//j<L-1 bc no point of inserting zeros to the end
{
    if (a[j]==1) Inserter.push_back(j+1);
}
/*cout<<"Inserter= ";
         for (int i = 0; i < Inserter.size(); i++)
                 {
                    cout << Inserter[i];
                 }
         cout<<endl;
*/
//////////////// Main Calculation of squeezing in zero's ////////////////////

//Matrix SqM to store states generated by squeezin-in zeros
int SqM [1000][L];
for (int i = 0; i < L ; i++)//1st row of SqM is the root partition
{
    SqM [0][i]=a[i];
}

int rstart=0;
int rstop=1;

if (rmax == L-1) {cout<<"Can't squeeze-in zero's"<<endl;}
else
{
    do
    {
        for (int r=rstart; r<rstop; r++)
        {
            rmax=0;//reset rmax value inorder to not affect while condition
            for (int j=L-1; j>=0; j--)
            {
               if (SqM[r][j]!=0)
               {
                   rmax=j;
                   break;
               }
            }

            if (rmax == L-1) break;
            int nmax=SqStates.size();

            for (int k=0; k<Inserter.size(); k++)
            {
                for (int l=0; l<Inserter[k]+1; l++)
                {
                    D[k][l]=SqM[r][l];
                }
                D[k][Inserter[k]]=0;
                for (int l=Inserter[k]+1; l<L; l++)
                {
                    D[k][l]=SqM[r][l-1];
                }

  /////////////////// Check for equivalent states ///////////////////////
        //adding above new states to the Sq Matrix (check for equivalent states to be added)

                int nadd=0;
                bool check = false;
                for (int n=0; n<nmax; n++)
                {
                    for (int j=0; j<L; j++)
                    {
                        check= false;
                        if (D[k][j] == SqM[n][j]) check= true;

                        else  break; //if any two elements are not equal break from j loop

                    }

                    if (check == true) break; //if C-row in consideration matches to any row, break from n loop

                }
                if (check == false)
                            {
                                for (int j=0; j<L; j++){
                                  SqM [nmax][j]=D[k][j];
                                }
                                nadd++;
                                SqStates.push_back(nmax+k);

                            }
                nmax=nmax+nadd;

   ////////////////////////////////////////////////////////////////////////////////////////////


            }
        }
        rstart=rstop;
        rstop=SqStates.size();

    } while(rstart != rstop);
}

//printing the big matrix with distinct states

cout<<endl<<"Squeezing in zeros States="<<endl;
  for (int i=0; i<SqStates.size(); i++)
  {
      for (int j=0; j<L; j++)
      {
          cout<<SqM[i][j];
      }
      cout<<'\n';
  }
        cout<<endl;

cout<<"Total number of states= "<< SqStates.size()<<endl;
cout<<endl;

  ;return 0;
 }



