#include <iostream>
#include <opencv2/opencv.hpp>
#include "Gantt.h"

int main() {
    gantt::read_file(CHROMOFILE,COSTFILE);
    gantt::draw(SAVEFILENAME,bSAVEFILE);
    return 0;
}
