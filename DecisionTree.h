
#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include "Dataframe.h"

typedef struct Split {
    string label;
    string pos;
    int nr_pos_y = -1;
}Split;

class DecisionTree {
public:
    DecisionTree(Dataframe dataframe);
    Dataframe df;
    vector<string> get_possible_categories(string col_name);
    vector<Split> splits;
    void print_possible_categories(string col_name);
    int get_positive_y_cat(string col_name, string pos);
    Split get_best_split();
    void make_splits();
    void print_splits();
};



#endif //DECISIONTREE_H
