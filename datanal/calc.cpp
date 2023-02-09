#include <vector>
#include <cmath>

using namespace std;

double average(vector<double> &dlist)
{
    double dsum = 0;
    for (auto x:dlist) dsum+=x;
    return (dsum / dlist.size());
}

double stdevp(vector<double> &dlist)
{
    double mean = average(dlist);
    double dsum = 0;

    for (auto x:dlist) dsum += pow(x - mean, 2.0);
    return (sqrt(dsum / dlist.size()));
}

double stdevs(vector<double> &dlist)
{
    double mean = average(dlist);
    double dsum = 0;

    for (auto x:dlist) dsum += pow(x - mean, 2.0);
    return (sqrt(dsum / (dlist.size()-1)));
}

double dmax(vector<double> &dlist)
{
    double tmp = dlist[0];
    for (unsigned i=1; i < dlist.size(); ++i)
        if (dlist[i] > tmp) tmp=dlist[i];
    return tmp;
}

double dmin(vector<double> &dlist)
{
    double tmp = dlist[0];
    for (unsigned i=1; i < dlist.size(); ++i)
        if (dlist[i] < tmp) tmp=dlist[i];
    return tmp;
}
