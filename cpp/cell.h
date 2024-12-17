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
        int get_value();
        void print_value();
        void print_notes();
        void set_note(int, int);
        int get_note(int);

};



#endif