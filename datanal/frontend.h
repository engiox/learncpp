#include <vector>
#include <string>

using namespace std;

vector<string> GetFileNames(const string = ".");
vector<string> GetColNames(const vector<string>);
int GetColIndex(const vector<string>, const string);
vector<string> GetColData(const string, const int);
vector<double> GetColDData(const string, const int);
unsigned GetMaxStep(const vector<string>);
