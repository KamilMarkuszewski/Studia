#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int main(int argc, char *argv[])
{
    
    // 1
    //vector<int> vec;
    vector< vector<int> > glowny(10);
    vector< vector<int> >::iterator iterator;
    //2
    cout << endl <<" Ilosc elementow glownego wektora: " << glowny.size() <<endl;
    
    //3
    
    int n=0;
    for( iterator = glowny.begin(); iterator!= glowny.end();iterator++, n++){
         for( int j=0; j<n;j++){
              iterator->push_back(0);   
              }     
         }
    
    
    cout <<endl<<endl<< " Glowny vector: " <<endl;
    cout << " Liczba elementow: " << glowny.size() << endl; 
    cout << " Pamiec zaalokowana na: " << glowny.capacity() << endl<<endl<<endl;

    cout << endl << endl << " ----------------------------------- " << endl << endl;
    cout << " Vectory skladowe: "<<endl<<endl;
    cout << endl << endl << " ----------------------------------- " << endl << endl;
    n=0;
    for( iterator = glowny.begin(); iterator!= glowny.end();iterator++, n++){
         
         
         cout << " Vector nr " << n << " : " << endl;
         cout << " Liczba elementow: " << iterator->size() << endl;
         cout << " Pamiec zaalokowana na: " << iterator->capacity() << endl;
         
         cout << " Elementy: ";
         for( vector<int>::iterator iter=iterator->begin(); iter != iterator->end(); iter++){
              cout << *iter << "\t";
              }
         cout << endl << endl << " ----------------------------------- " << endl << endl;         
         }
    
    
    cout << " 5ty element w 8 vectorze: " << glowny[8].at(5) << endl;
    
    cout << " 5ty element w 8 vectorze: " << glowny[8][5] << endl;
    
    cout << " 5ty element w 8 vectorze: " << (glowny.at(8)).at(5) << endl;
    
    
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
