#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::find;
using std::map;
using std::setw;

struct zodis
{
	int counter;
	vector<int> eilutes;
};

void skaitymas(map<string, zodis>&);
void nuorodos(map<string, zodis>&);
void spausdinimas(map<string, zodis>&);
