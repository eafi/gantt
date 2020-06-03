//
// Created by imEaf on 2020/6/2.
//

#ifndef GANTT_MACHINE_H
#define GANTT_MACHINE_H

class Machine{
public:
    int get_lst_t() {
        return lstT;
    }
    void set_lst_t(int val)
    {
        lstT = val;
    }


protected:
    int lstT;

};


#endif //GANTT_MACHINE_H
