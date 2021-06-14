#include "Job.h"
using namespace std;
Job::Job() {
	this->jobname = " ";
	this->deadline = 0;
	this->profit = 0;
}
void Job::setJobname(string jobname) {
	this->jobname = jobname;
}
void Job::setDeadline(int deadline) {
	this->deadline = deadline;
}
void Job::setProfit(int profit) {
	this->profit = profit;
}
string Job::getJobname() {
	return jobname;
}
int Job::getDeadline() {
	return deadline;
}
int Job::getProfit() {
	return profit;
}