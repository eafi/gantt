//
// Created by imEaf on 2020/6/2.
//

#ifndef GANTT_JOB_H
#define GANTT_JOB_H

class Job{
public:
    int get_lst_t() {
        return lstT;
    }
    void set_lst_t(int val)
    {
        lstT = val;
    }

    int process = 0;
    void set_clr(const cv::Scalar& val)
    {
        color = val;
    }

    cv::Scalar get_clr()
    {
        return color;
    }
protected:
    int lstT;
    cv::Scalar color;
};


#endif //GANTT_JOB_H
