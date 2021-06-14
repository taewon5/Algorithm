#include <string>
using namespace std;
class Job
{
	string jobname;
	int deadline;
	int profit;
public:
	Job();
	void setJobname(string jobname);
	void setDeadline(int deadline);
	void setProfit(int profit);
	string getJobname();
	int getDeadline();
	int getProfit();
};

