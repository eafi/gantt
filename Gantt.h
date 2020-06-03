//
// Created by imEaf on 2020/6/2.
//

#ifndef GANTT_GANTT_H
#define GANTT_GANTT_H

namespace gantt{

//项目定义
#define CHROMOFILE "../examples/J20P10M10.txt" //染色体文本
#define COSTFILE "../examples/J20P10M10_cost.txt" //工序耗时文本
#define SAVEFILENAME "J20P10M10.png" //输出图片名
#define bSAVEFILE 1 //是否保存文件

const unsigned JOBS_NUM = 20; //工件数量
const unsigned PROCESS_NUM = 10; //工序数量
const unsigned MACHINE_NUM = 10; //机器数量
//画布定义
const unsigned WIDTH = 1920;
const unsigned HEIGHT = 1080;
const unsigned OPTIMAL_TIME = 81; //已知的最优化时间，用以缩放画布


const unsigned RATIO = std::ceil(WIDTH / OPTIMAL_TIME); //缩放尺度
const unsigned MACHINE_HEIGHT = std::ceil(HEIGHT / MACHINE_NUM);


void read_file(const std::string &chromoFile,const std::string &costFile);
void rectangle(unsigned time, unsigned machineNum,unsigned length,unsigned jobsNum);
void draw(const std::string &imgname,bool bsaveimg);
void putsys(unsigned jobsNum,unsigned machineIndex,unsigned machineNum,unsigned length,unsigned time);
}
#endif //GANTT_GANTT_H
