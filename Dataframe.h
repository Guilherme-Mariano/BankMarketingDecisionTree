#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <string>
#include <vector>
using namespace std;

typedef struct Element {
    bool is_numeric = false;
    string object;
    double value;
}Element;

typedef struct Line {
    vector<Element> elements;
}Line;

typedef struct Column {
    string label;
    vector<Element> elements;
}Column;

class Dataframe {
public:
    vector<string> labels;
    vector<Line> dataframe;
    vector<Column> df_cols;
    int load_from_file(string filepath);
    void print_labels();
    void populate_labels(string line);
    void populate_dataframe(string line);
    void print_line(Line line);
    void print_dataframe();
    int get_col_index(string col_name);
    vector<string> get_numeric_cols();
    void print_num_cols();
    vector<string> get_categorical_cols();
    void print_cat_cols();
    void fix_datatype();
    void populate_df_cols();
    void print_df_cols();
    void delete_columns(string col);
    void delete_line_cat(string col, string pos_to_keep);
};



#endif //DATAFRAME_H
