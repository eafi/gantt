//
// Created by imEaf on 2020/6/2.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Gantt.h"
#include <string>
#include "Machine.h"
#include "Job.h"
#include "clrmap.h"

namespace gantt{

    Job jobs[JOBS_NUM];
    Machine machines[MACHINE_NUM];
    int chromo[2*JOBS_NUM*PROCESS_NUM];
    int cost[JOBS_NUM*PROCESS_NUM*MACHINE_NUM];
    cv::Mat gantt_(HEIGHT,WIDTH,CV_8UC3,cv::Scalar(255,255,255));

    void read_file(const std::string &chromoFile,const std::string &costFile)
    {
        //clr init
        for(int i=0;i<JOBS_NUM;++i)
        {
           cv::RNG rng(12345+i);
//           jobs[i].set_clr(cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)));
            jobs[i].set_clr(clrMap[rng.uniform(0,40)]);
        }

        std::ifstream infile,infile2;
        infile.open(chromoFile,std::ios::in);
        infile2.open(costFile,std::ios::in);
        int tmp;
        for(int i=0;i<2*JOBS_NUM*PROCESS_NUM;++i)
        {
            infile >>tmp;
            chromo[i] = tmp;
        }
        std::string tmpstr;
        for(int i=0;i<JOBS_NUM*PROCESS_NUM*MACHINE_NUM;++i)
        {
            infile2>>tmpstr;
            if(tmpstr == "-")
                cost[i] = -1;
            else cost[i] = std::stoi(tmpstr);
        }
        // check the date.
//        for(int i=0;i<JOBS_NUM*PROCESS_NUM;++i)
//        {
//            std::cout<<chromo[i]<<" ";
//        }std::cout<<std::endl;
//        for(int i=0;i<JOBS_NUM*PROCESS_NUM;++i)
//        {
//            std::cout<<chromo[i+JOBS_NUM*PROCESS_NUM]<<" ";
//        }
//        std::cout<<std::endl;
//        for(int i=0;i<MACHINE_NUM*JOBS_NUM*PROCESS_NUM;++i)
//        {
//            std::cout<<cost[i]<<" ";
//        }std::cout<<std::endl;
    }


    void draw(const std::string &imgname,bool bsaveimg)
    {
        for(int i=0;i<JOBS_NUM*PROCESS_NUM;++i)
            //for(int i=0;i<10;++i)
        {
            unsigned j = chromo[i]; //处理工序染色体i,其表达含义：1.该值为第j个工件,2.出现第几次表达第几到供需
            //******NOTE*********
            //j 取值从1开始
            --j;
            unsigned machineMapIdx = (j)*PROCESS_NUM+jobs[j].process;//机器染色体对应机器index
            unsigned machineIndex = JOBS_NUM*PROCESS_NUM + machineMapIdx; //带有偏置的机器染色体对应机器index
            unsigned machineNum = chromo[machineIndex]; //机器人染色体，当前工序i对应的机器.
            //******NOTE********
            //machineNum 取出得值为从1开始
            --machineNum;
            unsigned costMapIdx = (PROCESS_NUM*(j)+jobs[j].process)*MACHINE_NUM + machineNum;//时序表映射
            int length = cost[costMapIdx]; //该工序应该消耗的时间，即长度
            //当前工件的最新时间和当前机器的最新时间，二者应该取最大值作为有效的时间以防止工序冲突
            int time = jobs[j].get_lst_t() > machines[machineNum].get_lst_t() ?
                       jobs[j].get_lst_t() : machines[machineNum].get_lst_t();

            //输出信息
            putsys(j,machineIndex,machineNum,length,time);
            //在当前时间进行工序绘制
            gantt::rectangle(time,machineNum,length,j);

            //update phase,更新段，需要刷新当前工件和机器的最新时间到最新
            time += length;
            ++jobs[j].process; //当前工序更新
            jobs[j].set_lst_t(time);
            machines[machineNum].set_lst_t(time);
        }

        //用以核算每个机器的最终总时长，机器核算的最大总时长应该等于优化算法计算出来的时长
//          for(int i=0;i<MACHINE_NUM;++i)
//          {
//              std::cout<<machines[i].get_lst_t()<<std::endl;
//          }
        //显示和保存
        cv::imshow(imgname,gantt_);
        if(bsaveimg)
            cv::imwrite(imgname,gantt_);
        cv::waitKey(0);
    }

    /// 将时间-机器编号-时间长度向绘图层映射
    /// \param time :当前的时间位置.NOTE!当前时间画图会覆盖后面时间,需要减去length
    /// \param machineNum
    /// \param length:时间历程
    /// \param jobsNum:工件编号
    void rectangle(unsigned time, unsigned machineNum,unsigned length,unsigned jobsNum)
    {
        int x = time * RATIO;
        int y = machineNum * MACHINE_HEIGHT;
        cv::Rect rect (x,y,length*RATIO,MACHINE_HEIGHT);
        cv::rectangle(gantt_,
                rect,jobs[jobsNum].get_clr(),
                -1);
        std::string txt("J"+std::to_string(jobsNum));

        //字体调整，以适应小矩形
        //但仍然存在被后续渲染的字体覆盖的bug
        float thickness = 1.8;
        float fontscale = 1.0;
        int baseline=0;
        cv::Size txtSize = cv::getTextSize(txt,cv::FONT_HERSHEY_SIMPLEX,fontscale,thickness,&baseline);
        while(txtSize.width > rect.width)
        {
            fontscale *= 0.9;
            txtSize = cv::getTextSize(txt,cv::FONT_HERSHEY_SIMPLEX,fontscale,thickness,&baseline);
        }

        cv::putText(gantt_,txt,
                cv::Point(x,y+MACHINE_HEIGHT-baseline),
                cv::FONT_HERSHEY_SIMPLEX,
                fontscale,
                cv::Scalar(0,0,0),thickness,cv::LINE_8);
    }

    void putsys(unsigned jobsNum,unsigned machineIndex,unsigned machineNum,unsigned length,unsigned time)
    {

        std::cout<<"工件:"<<jobsNum<<",工序:"<<jobs[jobsNum].process
                 <<",with displacement:"
                 <<machineIndex<<",对应的机器#"<<machineNum
                 <<"消耗时间:"<<length
                 <<"该工序应该放在时刻:"<<time<<std::endl;
    }

}
