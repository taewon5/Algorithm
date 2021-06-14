#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "Job.h"
using namespace std;
bool CompareObj(Job first, Job second) {
	return first.getProfit() > second.getProfit();
}
bool CompareDeadline(Job first, Job second) {
    return first.getDeadline() < second.getDeadline();
}
vector<Job>read_jobs(string fName) {
    vector<Job>jobs;
    Job temp;
    ifstream file;
    string name;
    int deadline, profit;
    file.open(fName);
    while (!file.eof()) {
        file >> name;
        file >> deadline >> profit;
        temp.setJobname(name);
        temp.setDeadline(deadline);
        temp.setProfit(profit);
        jobs.push_back(temp);
    }
    file.close();
    return jobs;
}
vector<Job> sort_profit(vector<Job>jobs) {
    sort(jobs.begin(), jobs.end(), CompareObj);
    return jobs;
}
int LastDeadline(vector<Job>jobs) {
    int n = jobs.size() - 1;
    sort(jobs.begin(), jobs.end(), CompareDeadline);
    return jobs[n].getDeadline();
}
vector<Job>schedule(vector<Job>jobs) {
    vector<Job> J;
    int n = jobs.size();
    int deadline = 1;
    int last_deadline = LastDeadline(jobs);
    J.push_back(jobs[0]);
    for (int i = 1; i <n ; i++) {
        if (jobs[i].getDeadline() > deadline && J.size() < last_deadline) { //jobs[i]의 데드라인이 작업데드라인보다 크고 J의 사이즈가 최대 데드라인보다 작을경우 J에 추가ㅣ
            J.push_back(jobs[i]);
            deadline++;
        }
    }
    return J;
}
void print_job(vector<Job>jobs) {
    int total = 0;
    cout <<"----------------------" << endl;
    cout << "Deadline Job   profit" << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < jobs.size(); i++) {
        cout << jobs[i].getDeadline() << "\t " << jobs[i].getJobname() << "    " << jobs[i].getProfit() << endl;
        total += jobs[i].getProfit();
    }
    cout << "----------------------" << endl;
    cout << "Total Profit=  " << total << endl;
    cout << "----------------------" << endl;
}
int main(){
    int j, i;
	vector<Job>jobs = read_jobs("jobs.txt");
    /*for (i = 0; i < jobs.size(); i++) {
        cout << jobs[i].getJobname() << " " << jobs[i].getDeadline() << " " << jobs[i].getProfit()<<endl;
    }
    cout << "--------------------------------------" << endl;
    */
    vector<Job>sorted_by_profit = sort_profit(jobs);
    /*for (i = 0; i < jobs.size(); i++) {
        cout << sorted_by_profit[i].getJobname() << " " << sorted_by_profit[i].getDeadline() << " " << sorted_by_profit[i].getProfit() << endl;
    }
    cout << "--------------------------------------" << endl;
   */
   vector<Job>scheduled = schedule(sorted_by_profit);
   print_job(scheduled);
   system("pause");
}

