#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "calc.h"
#include "frontend.h"

using namespace std;

int main()
{
    vector<string> fnlist = GetFileNames();
    vector<string> collist = GetColNames(fnlist);

    string input;
    int colindex = -1;
    while (colindex < 0)
    {
        cout << "Enter parameter name : ";
        cin >> input;
        colindex = GetColIndex(collist, input);
    }

    unsigned step = 0;
    unsigned maxstep = GetMaxStep(fnlist);
    while (!(step > 0 && step <= maxstep))
    {
        cout << "Enter Step Counter (1 ~ " << maxstep << ") : ";
        cin >> step;
    }

    string ofname;
    ofstream ofdata;
    do
    {
        cout << "Enter output file name : ";
        cin >> ofname;
        ofdata.open(ofname);
    } while (!ofdata.is_open());

    ofdata << "Parameter : " << input << ", Step : " << step << endl;
    ofdata << "LotID, max, min, average, stdevp, stdevs" << endl;

    for (auto x1:fnlist)
    {
        vector<string> step_counter = GetColData(x1,GetColIndex(collist, "STEP_Counter"));
        vector<double> ddata = GetColDData(x1,colindex);

        vector<double> dresult;
        for (unsigned i=0; i<step_counter.size(); ++i)
        {
            if (step_counter[i] == to_string(step))
                dresult.push_back(ddata[i]);
        }
        ofdata << x1 << ", " << dmax(dresult) << ", " << dmin(dresult) << ", "
            << average(dresult) << ", " << stdevp(dresult) << ", " << stdevs(dresult) << ", " << endl;
    }

    ofdata.close();

    return 0;
}
