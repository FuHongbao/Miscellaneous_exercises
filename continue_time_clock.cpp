/*************************************************************************
	> File Name: continue_time_clock.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年07月11日 星期四 18时11分34秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
using namespace std;
struct itimerval timeset;

void clock(int) {
    cout << "hello world!" << endl;
    timeset.it_value.tv_sec = timeset.it_interval.tv_sec;
    timeset.it_interval.tv_sec ++;
    setitimer(ITIMER_REAL, &timeset, NULL);
}

int main () {
    signal(14, clock);
    timeset.it_value.tv_sec = 5;
    timeset.it_value.tv_usec = 0;
    timeset.it_interval.tv_sec = 1;
    timeset.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timeset, NULL);
    int a;
    cin >> a; 
    return 0;
}

