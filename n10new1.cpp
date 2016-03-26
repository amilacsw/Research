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

int N=10;  //Number of Bosons
int L=18;  //Number of Orbitals (make sure you have enough orbitals according to deltaLupTo value)
int startL=60;  //Input the smallest possible Angular momentum for the given N
int deltLupTo=5;  // Decide upto which delta L is meaningful and enter that here

int main ()
{

/////////////////////////////  Main Calculation  ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

int BigM [1000][L];
int C [1][L];
int GPPM[1000][L];//matrix to store states satisfying the GPP
int TotLnew;
int deltaLnew=0;
vector<int> GPPstates;//vector to store the #of GPP states

// To add more particles, add for loop to outside. Remember to take out added particle after each loop.
/*
for (int n14=0; n14<L; n14++)
{
    C[0][n14]=C[0][n14]+1;

    for (int n13=0; n13<L; n13++)
    {
        C[0][n13]=C[0][n13]+1;

        for (int n12=0; n12<L; n12++)
        {
            C[0][n12]=C[0][n12]+1;

                                            bool GPPCheck8=false;

                                            for (int i=0; i<L-2; i++)
                                            {
                                                int particles=0;
                                                particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                if (particles>2)
                                                {
                                                    GPPCheck8=true;
                                                    break;
                                                }
                                            }
                                            if (GPPCheck8 == false)
                                            {

                for (int n11=0; n11<L; n11++)
                {
                    C[0][n11]=C[0][n11]+1;

                                            bool GPPCheck7=false;

                                            for (int i=0; i<L-2; i++)
                                            {
                                                int particles=0;
                                                particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                if (particles>2)
                                                {
                                                    GPPCheck7=true;
                                                    break;
                                                }
                                            }
                                            if (GPPCheck7 == false)
                                            {
*/

                    for (int n10=0; n10<L; n10++)
                    {
                        C[0][n10]=C[0][n10]+1;

                                                        bool GPPCheck6=false;

                                                        for (int i=0; i<L-2; i++)
                                                        {
                                                            int particles=0;
                                                            particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                            if (particles>2)
                                                            {
                                                                GPPCheck6=true;
                                                                break;
                                                            }
                                                        }
                                                        if (GPPCheck6 == false)
                                                        {


                        for (int n9=0; n9<L; n9++)
                        {
                            C[0][n9]=C[0][n9]+1;

                                                        bool GPPCheck5=false;

                                                        for (int i=0; i<L-2; i++)
                                                        {
                                                            int particles=0;
                                                            particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                            if (particles>2)
                                                            {
                                                                GPPCheck5=true;
                                                                break;
                                                            }
                                                        }
                                                        if (GPPCheck5 == false)
                                                        {


                            for (int n8=0; n8<L; n8++)
                            {
                                C[0][n8]=C[0][n8]+1;

                                                        bool GPPCheck4=false;

                                                        for (int i=0; i<L-2; i++)
                                                        {
                                                            int particles=0;
                                                            particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                            if (particles>2)
                                                            {
                                                                GPPCheck4=true;
                                                                break;
                                                            }
                                                        }
                                                        if (GPPCheck4 == false)
                                                        {


                                for (int n7=0; n7<L; n7++)
                                {
                                    C[0][n7]=C[0][n7]+1;

                                    for (int n6=0; n6<L; n6++)
                                    {
                                        C[0][n6]=C[0][n6]+1;

                                                        bool GPPCheck3=false;

                                                        for (int i=0; i<L-2; i++)
                                                        {
                                                            int particles=0;
                                                            particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                            if (particles>2)
                                                            {
                                                                GPPCheck3=true;
                                                                break;
                                                            }
                                                        }
                                                        if (GPPCheck3 == false)
                                                        {


                                        for (int n5=0; n5<L; n5++)
                                        {
                                            C[0][n5]=C[0][n5]+1;

                                                        bool GPPCheck2=false;

                                                        for (int i=0; i<L-2; i++)
                                                        {
                                                            int particles=0;
                                                            particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                            if (particles>2)
                                                            {
                                                                GPPCheck2=true;
                                                                break;
                                                            }
                                                        }
                                                        if (GPPCheck2 == false)
                                                        {


                                            for (int n4=0; n4<L; n4++)
                                            {
                                                C[0][n4]=C[0][n4]+1;

                                                for (int n3=0; n3<L; n3++)
                                                {
                                                    C[0][n3]=C[0][n3]+1;

                                                        bool GPPCheck1=false;

                                                        for (int i=0; i<L-2; i++)
                                                        {
                                                            int particles=0;
                                                            particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                            if (particles>2)
                                                            {
                                                                GPPCheck1=true;
                                                                break;
                                                            }
                                                        }
                                                        if (GPPCheck1 == false)
                                                        {


                                                    for (int n2=0; n2<L; n2++)
                                                    {
                                                        C[0][n2]=C[0][n2]+1; //Adding one particle: This should be removed at the end of the loop

                                                        for (int n1=0; n1<L; n1++)
                                                        {
                                                            C[0][n1]=C[0][n1]+1; //Adding one particle

                                                            //GPP Check
                                                            bool GPPCheck=false;

                                                            for (int i=0; i<L-2; i++)
                                                            {
                                                                int particles=0;
                                                                particles= C[0][i]+C[0][i+1]+C[0][i+2];

                                                                if (particles>2)
                                                                {
                                                                    GPPCheck=true;
                                                                    break;
                                                                }
                                                            }
                                                            if (GPPCheck == false)
                                                            {
                                                                //TotalStatesCount++;
                                                                //deltaL check. Only required deltaL states are stored
                                                                bool deltaLcheck = false;
                                                                TotLnew=0;
                                                                for (int j=0; j<L; j++)
                                                                {
                                                                    TotLnew= TotLnew+ C[0][j] *j;
                                                                }
                                                                deltaLnew=TotLnew-startL;

                                                                if (deltaLnew <= deltLupTo)
                                                                {

                                                                    bool check = false;
                                                                    int GPPn=GPPstates.size();
                                                                    for (int n=0; n<GPPn+1; n++)
                                                                    {
                                                                        for (int j=0; j<L; j++)
                                                                        {
                                                                            check= false;
                                                                            if (GPPM[n][j] == C[0][j]) check= true;

                                                                            else  break; //if any two elements are not equal break from j loop

                                                                        }

                                                                        if (check == true) break; //if BigM-row in consideration matches to any row, break from n loop
                                                                    }
                                                                    if (check == false)
                                                                    {
                                                                        for (int j=0; j<L; j++)
                                                                        {
                                                                            GPPM[GPPn][j]= C[0][j];
                                                                            cout<<GPPM[GPPn][j];
                                                                        }
                                                                        cout<<'\n';
                                                                        GPPstates.push_back(GPPn);

                                                                    }
                                                                }
                                                            }
                                                            //End of GPP Check

                                                            C[0][n1]=C[0][n1]-1;  //Removing a particle

                                                        }

                                                         C[0][n2]=C[0][n2]-1; //Remove
                                                    }
                                                                                    }//end of GPPCheck1

                                                    C[0][n3]=C[0][n3]-1;
                                                }

                                                C[0][n4]=C[0][n4]-1;
                                            }
                                                                                    }//end of GPPCheck2

                                            C[0][n5]=C[0][n5]-1;
                                        }
                                                                                    }//end of GPPCheck3

                                        C[0][n6]=C[0][n6]-1;
                                    }

                                    C[0][n7]=C[0][n7]-1;
                                }
                                                                                     }//end of GPPCheck4

                                C[0][n8]=C[0][n8]-1;
                            }
                                                                                    }//end of GPPCheck5

                            C[0][n9]=C[0][n9]-1;
                        }
                                                                                    }//end of GPPCheck6

                        C[0][n10]=C[0][n10]-1;
                    }
                     /*                                                               }//end of GPPCheck7

                    C[0][n11]=C[0][n11]-1;
                }
                                                                                    }//end of GPPCheck8

                C[0][n12]=C[0][n12]-1;
            }

            C[0][n13]=C[0][n13]-1;
        }

        C[0][n14]=C[0][n14]-1;
}

*/
    //printing the GPP matrix

    cout<<endl<<"States satisfying the GPP with given delta L's="<<endl;
      for (int i=0; i<GPPstates.size(); i++)
      {
          for (int j=0; j<L; j++)
          {
              cout<<GPPM[i][j];
          }
          cout<<'\n';
      }
            cout<<endl;

    cout<<"Total number of states satisfying the GPP for given deltaL's= "<< GPPstates.size()<<endl;
    cout<<endl;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////// Storing the change in Angular momentum, Delta L /////////////////////////////////

    int DeltaL [1][GPPstates.size()]; //Row matrix to store Delta-L values
    int DeltaLstates [1][deltLupTo+1]; // Matrix to store the number of states for delta L values

    int TotL;
    int countNumber;

    for (int i=0; i<GPPstates.size(); i++)
    {
        TotL=0;
        for (int j=0; j<L; j++)
        {
            TotL= TotL+ GPPM[i][j] *j;
        }

        DeltaL[0][i] = TotL-startL;
        //cout<<endl<<"For i= "<<i<<" TotL= "<<TotL<<" DeltaL= "<<DeltaL[0][i]<<endl;
    }

    // Number of states with Delta L

    cout<<"Number of States for different Delta-L :"<<endl;

    for (int l=0; l<deltLupTo+1; l++) // number  modified according to highest delta l
    {
        countNumber=0;
        for (int i=0; i<GPPstates.size(); i++)
        {
            if (DeltaL[0][i] == l)
            {
                countNumber++;
            }
        }
        DeltaLstates[0][l]=countNumber;
        cout<<"Delta L= "<<l<<"  Number of States= "<<DeltaLstates[0][l]<<endl;
    }


cout<<endl;

;return 0;
}

