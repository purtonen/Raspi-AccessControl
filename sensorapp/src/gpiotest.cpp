#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

using namespace std;

int main(){
    GPIO* gpio4 = new GPIO("4");
    gpio4->export_gpio();
    usleep(50000);
    gpio4->setdir_gpio("in");

    string val;

    while(1){
        val = "NULL";
        usleep(500000);
        gpio4->getval_gpio(val);
        cout << val << endl;
    }
}