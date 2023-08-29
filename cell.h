#ifndef CELL_H
#define CELL_H

class Cell{
    private:
        int value;
        int notes[9];

    public:
        Cell();
        Cell(int);
        ~Cell();
        void set_value(int);
        void print_value();

};



#endif