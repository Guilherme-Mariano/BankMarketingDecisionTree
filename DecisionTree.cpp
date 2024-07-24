
#include "DecisionTree.h"
#include <iostream>
#include "Helper.h"

DecisionTree::DecisionTree(Dataframe dataframe) {
    df = dataframe;
}


vector<string> DecisionTree::get_possible_categories(string col_name) {
    vector<string> possibilities;
    int col_ind = df.get_col_index(col_name);
    for(int i = 0; i < df.df_cols.at(col_ind).elements.size(); i++) {
        if(!Helper::check_string_in_vector(possibilities,df.df_cols.at(col_ind).elements.at(i).object)) {
            possibilities.insert(possibilities.end(), df.df_cols.at(col_ind).elements.at(i).object);
        }
    }
    return possibilities;
}

void DecisionTree::print_possible_categories(string col_name) {
    vector<string> possibilities = get_possible_categories(col_name);
    cout << "\n Possibilities for: " << col_name << "\n";
    for(int i = 0; i < possibilities.size(); i++) {
        cout << " ||" << possibilities.at(i) << "|| ";
    }
    cout << "\n";
}

int DecisionTree::get_positive_y_cat(string col_name, string pos) {
    int nr_pos = -1;
    int col_ind = df.get_col_index(col_name);
    int target_ind = df.get_col_index("y");
    for(int i = 0; i < df.df_cols.at(target_ind).elements.size(); i++) {
        if(df.df_cols.at(col_ind).elements.at(i).object == pos) {
            if(df.df_cols.at(target_ind).elements.at(i).object == "yes") {
                if(nr_pos == -1) nr_pos = 0;
                nr_pos++;
            }
        }
    }
    return nr_pos;
}

Split DecisionTree::get_best_split() {
    vector<string> cat_cols = df.get_categorical_cols();
    int highest_y = -1;
    string label = "";
    string pos = "";
    int nr_pos_y = -1;
    for(int i = 0; i < cat_cols.size(); i++) {
        vector<string> cat_pos = get_possible_categories(cat_cols.at(i));
        if(cat_cols.at(i) == "y") continue;
        for(int j = 0; j < cat_pos.size(); j++) {
            int y_pos = get_positive_y_cat(cat_cols.at(i), cat_pos.at(j));
            if(y_pos > highest_y) {
                highest_y = y_pos;
                label = cat_cols.at(i);
                pos = cat_pos.at(j);
                nr_pos_y = y_pos;
            }
        }
    }
    Split sp;
    sp.label = label;
    sp.pos = pos;
    sp.nr_pos_y = nr_pos_y;
    return sp;
}

void DecisionTree::make_splits() {
    vector<string> cat_cols = df.get_categorical_cols();
    while(!cat_cols.empty()) {
        Split sp = get_best_split();
        splits.insert(splits.end(), sp);
        df.delete_line_cat(sp.label, sp.pos);
        df.delete_columns(sp.label);
        cat_cols = df.get_categorical_cols();
    }
}

void DecisionTree::print_splits() {
    make_splits();
    for(int i = 0; i < splits.size(); i++) {
        cout << "\nLabel: " << splits.at(i).label << " Categorical value: " << splits.at(i).pos << " Nr Deposits: " << splits.at(i).nr_pos_y;
    }
}

