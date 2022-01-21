#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

int main() {

    int n;          //number of arrays
    int q;          //number of queries
    int tempValue;  //would be used to store the input value of each element in inner vector

    // storing the number of arraus in 'n' and number queries in 'q'
    cin >> n >> q;

    /* creation of vectors*/

    //creating 'n' number of vectors
    vector< vector<int> >a(n);

    int numElem;    //number of elements in inner vector

    for(int i = 0; i < n; i++){
        //store the number of elements desired
        cin >> numElem;
        //runs 'numElem' times
        for(int j = 0; j < numElem; j++){
            cin >> tempValue;
            a[i].push_back(tempValue);
        }
    }

    /*query of vectors*/
    int outVec;         //stores the queried outer vector index
    int inVec;          //stores the queried inner vector index

    //runs 'q' times
    for(int i = 0; i < q; i++){
        cin >> outVec >> inVec;
        cout << a[outVec][inVec] << endl;
    }

    return 0;    
}