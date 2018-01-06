#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
    // nowa kolejka
    priority_queue<int> kolejka;
    
    
    // dodaje na koncu 10 liczb 0-50
    for( int i=0; i<10;i++){
         kolejka.push(rand()%51); //
         }

    cout << " Ilosc elementow: " << kolejka.size() << endl<< endl<< endl;
    
    
    for( int i=0; i<10; i++){
         cout << " Element nr " << i<< " ma wartosc: " << kolejka.top() << endl;
         kolejka.pop();         
         }


    system("PAUSE");
    return EXIT_SUCCESS;
}
