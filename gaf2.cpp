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

int deltaL=3;
int imax= 4*deltaL -1;
int n,m;


int main ()
{


vector<int> ivalues; // vector to store i values

int SM [1000][imax]; //Maximum number of columns should be imax
                       //because, it's like having imax number of zero's
int ST[1000][imax];


  for (n=0; n<1000; n++)
    for (m=0; m<imax; m++)
    {
      SM [n][m]=0;
      ST [n][m]=0;
    }

  vector<int> GS; // Ground state vector
  //cout<<"initial size of GS= "<<GS.size()<<endl;
  for (int j=0; j<imax; j++)
  {
      GS.push_back(0);
  }
  for (int j=0; j<deltaL; j++)
  {
      GS[3*j+1]=2;
  }

///////////  Manually entering the first element //////////////
SM [0][0]=1;
SM [1][0]=4;

ivalues.push_back(1);
ivalues.push_back(3);
//////////////////////////////////////////////////////////////

//cout<<ivalues[0]<<"and"<<ivalues[1]<<endl;

int mstart=0;
int mstop=2;
int mstopUpdate=2;


for (int l=0; l<imax-1; l++)
{
    for (int m=mstart; m<mstop; m++)
    {
        if (ivalues[m] < imax)
        {
            if (SM [m][l]==1)
            {
                for (int p=0; p<4; p++)
                {
                    for (int j=0; j<l+1; j++)
                    {
                        SM [mstopUpdate+p][j]= SM [m][j];
                    }
                    SM [mstopUpdate+p][l+1]=p+1;
                    if ((p==0)||(p==1)){ivalues.push_back(ivalues[m]+1);}
                    else {ivalues.push_back(ivalues[m]+p);}

                }
                mstopUpdate=mstopUpdate+4;
                continue;
            }

            if (SM [m][l]==2)
            {
                SM [mstopUpdate][l+1]=1;
                for (int j=0; j<l+1; j++)
                {
                    SM [mstopUpdate][j]= SM [m][j];
                }
                ivalues.push_back(ivalues[m]+1);

                mstopUpdate=mstopUpdate+1;
                continue;
            }


            if (SM [m][l]==3)
            {
                SM [mstopUpdate][l+1]=1;
                for (int j=0; j<l+1; j++)
                {
                    SM [mstopUpdate][j]= SM [m][j];
                }
                ivalues.push_back(ivalues[m]+1);

                mstopUpdate=mstopUpdate+1;
                continue;
            }

            if (SM [m][l]==4)
            {

                SM [mstopUpdate][l+1]=1;
                ivalues.push_back(ivalues[m]+1);

                SM [mstopUpdate+1][l+1]=4;
                ivalues.push_back(ivalues[m]+3);

                for (int j=0; j<l+1; j++)
                {
                    SM [mstopUpdate][j]= SM [m][j];
                    SM [mstopUpdate+1][j]= SM [m][j];
                }

                mstopUpdate=mstopUpdate+2;
                continue;
            }
        }


    }
    cout<<"l= "<<l<<" mstart= "<<mstart<<" mstop= "<<mstop<<endl;
    mstart=mstop;
    mstop=mstopUpdate;

}
/*
cout<<"ivalues vector= "<<endl;
for (int j=0; j<ivalues.size(); j++)
{
    cout<<ivalues[j];
}
cout<<endl;

//printing the SM matrix

cout<<endl<<"Sequence of states="<<endl;
  for (int i=0; i<mstop; i++)
  {
      for (int j=0; j<imax; j++)
      {
          cout<<SM[i][j];
      }
      cout<<'\n';
  }
        cout<<endl;
*/
///////////////////////////////////////////////////////////////////////////

// Selecting states with correct i values and constructing a new matrix ST

int STrowUpdate=0;
int STcolUpdate=0;

for (int i=0; i<ivalues.size(); i++)
{
    if (ivalues[i] == imax)
    {
        STcolUpdate=0;
        for (int j=0; j<imax; j++)
        {
            if (SM[i][j]==1)
            {ST[STrowUpdate][STcolUpdate] =0; STcolUpdate=STcolUpdate+1;continue;}

            if (SM[i][j]==2)
            {ST[STrowUpdate][STcolUpdate] =1; STcolUpdate=STcolUpdate+1;continue;}

            if (SM[i][j]==3)
            {ST[STrowUpdate][STcolUpdate] =1;
             ST[STrowUpdate][STcolUpdate+1] =1; STcolUpdate=STcolUpdate+2;continue;}

            if (SM[i][j]==4)
            {ST[STrowUpdate][STcolUpdate] =0;
             ST[STrowUpdate][STcolUpdate+1] =2;
             ST[STrowUpdate][STcolUpdate+2] =0; STcolUpdate=STcolUpdate+3;continue;}

        }
        STrowUpdate++;
    }
}

// Check for Equivalent states in ST matrix and get rid of them

vector<int> STiNum; // vector to store number of states
int nmax=0;
bool check = false;

for (int i=0; i<STrowUpdate; i++)
{
    for (int n=0; n<nmax; n++)
    {
        for (int j=0; j<imax; j++)
        {
            check= false;
            if (ST[i][j] == ST[n][j]) check= true;

            else  break; //if any two elements are not equal break from j loop

        }

        if (check == true) break; //if ST-row in consideration matches to any row, break from n loop

    }
    if (check == false)
                {
                    for (int k=0; k<imax; k++){
                      ST [nmax][k]=ST[i][k];
                    }
                    nmax++;
                    STiNum.push_back(nmax);

                }

}

/*cout<<endl<<"States with correct i ="<<endl;
  for (int i=0; i<STiNum.size(); i++)
  {
      for (int j=0; j<imax; j++)
      {
          cout<<ST[i][j];
      }
      cout<<'\n';
  }
        cout<<endl;
*/
/////////////////////////////////////////////////////////////////////////////////////

// Getting rid-of states with wrong particle number

vector<int> STiNum2; // vector to store number of states
int pmax=0;
int XNum=0; //Number of particles in a generated state
int GSNum=0; //Number of particles in the ground state
for (int j=0; j<imax; j++)
{
    GSNum = GSNum+ GS[j];
}

for (int i=0; i<STiNum.size(); i++)
{
    XNum=0;
        for (int j=0; j<imax; j++)
        {
            XNum = XNum + ST[i][j];
        }

        if (XNum == GSNum)
        {
            for (int k=0; k<imax; k++){
              ST [pmax][k]=ST[i][k];
            }
            pmax++;
            STiNum2.push_back(pmax);
        }
        else continue;

}



//printing the ST matrix
/*
cout<<endl<<"States with correct i and N ="<<endl;
  for (int i=0; i<STiNum2.size(); i++)
  {
      for (int j=0; j<imax; j++)
      {
          cout<<ST[i][j];
      }
      cout<<'\n';
  }
        cout<<endl;
*/
/////////////////////////////////////////////////////////////////////////////////////



cout<<endl<<"Ground state pattern= "<<endl;
for (int j=0; j<imax; j++)
{
    cout<<GS[j];
}
cout<<endl;

//Storing delta-L values

vector<int> STdeltaL; // vector to store delta_L values
int XdeltaL=0;

for (int i=0; i<STiNum2.size(); i++)
{
    XdeltaL=0;
        for (int j=0; j<imax; j++)
        {
            XdeltaL = XdeltaL + j* (ST[i][j] - GS[j]);
        }
        STdeltaL.push_back(XdeltaL);
        //cout<<"XdeltaL= " <<XdeltaL<<endl;
}

int NumCount=0; // number of states with correct delta-L

cout<<endl<<"States with delta-L= "<<deltaL<<endl;

for (int j=0; j<STdeltaL.size(); j++)
{
    if (STdeltaL[j]==deltaL)
    {
        NumCount++;

        for (int k=0; k<imax; k++)
        {
            cout<< ST[j][k];
        }
        cout<<'\n';
    }
}

cout<<endl<<"Number of states with delta-L equals "<<deltaL<<"= "<<NumCount<<endl;
cout<<endl;

}
