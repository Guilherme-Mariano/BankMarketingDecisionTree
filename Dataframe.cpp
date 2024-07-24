#include "Dataframe.h"
#include <fstream>
#include <iostream>

#include "Helper.h"

int Dataframe::load_from_file(string filepath) {
    ifstream file(filepath);

    if(!file) {
        cerr << "Error opening file";
        return -1;
    }

    string line;
    int i = 0;
    while(file.good()) {
        file >> line;
        //cout << line;
        if(i == 0) {
            populate_labels(line);
            i++;
            continue;
        }
        populate_dataframe(line);
    }
    file.close();
    return 0;
}

void Dataframe::populate_labels(string line) {
    string str = "";
    for(int i = 0; i <= line.length(); i++) {
        if(line[i] == '\0') {
            labels.insert(labels.end(), str);
            break;
        }
        if(line[i] == ',' || line[i] == ';') {
            labels.insert(labels.end(), str);
            str = "";
            continue;
        }
        if(line[i] == '\"') continue;
        str += line[i];
    }
}

void Dataframe::print_labels() {
    for(int i = 0; i < labels.size(); i++) {
        cout << labels.at(i) << "\n";
    }
}

void Dataframe::populate_dataframe(string line) {
    string str = "";
    Line lin;
    for(int i = 0; i <= line.length(); i++) {
        if(line[i] == '\0') {
            Element elem;
            elem.object = str;
            lin.elements.insert(lin.elements.end(), elem);
            dataframe.insert(dataframe.end(), lin);
            break;
        }
        if(line[i] == ',' || line[i] == ';') {
            Element elem;
            elem.object = str;
            lin.elements.insert(lin.elements.end(), elem);
            str = "";
            continue;
        }
        if(line[i] == '\"') continue;
        str += line[i];
    }
}

void Dataframe::print_line(Line line) {
    for(int i = 0; i < line.elements.size(); i++) {
        if(line.elements.at(i).is_numeric)cout << " || Nr:" << line.elements.at(i).value << " || ";
        else cout << " || " << line.elements.at(i).object << " || ";
    }
    cout << "\n";
}

void Dataframe::print_dataframe() {
    for(int i = 0; i < dataframe.size(); i++) {
        print_line(dataframe.at(i));
    }
}

int Dataframe::get_col_index(string col_name) {
    for(int i = 0; i < labels.size(); i++) {
        if(col_name == labels.at(i)) return i;
    }
    return -1;
}

vector<string> Dataframe::get_numeric_cols() {
    vector<string> num_cols;
    for(int i = 0; i < labels.size(); i++) {
        bool flag = true;
        for(int j = 0; j < dataframe.size(); j++) {
            if(!Helper::check_string_is_numeric(dataframe.at(j).elements.at(i).object)) {
                flag = false;
            }
        }
        if(flag) {
            num_cols.insert(num_cols.end(), labels.at(i));
        }
    }
    return num_cols;
}

void Dataframe::print_num_cols() {
    vector<string> num_cols = get_numeric_cols();
    for(int i = 0; i < num_cols.size(); i++) {
        cout << num_cols.at(i) << " ";
    }
    cout << "\nNr Elements in num cols: " << num_cols.size() <<"\n";
}

vector<string> Dataframe::get_categorical_cols() {
    vector<string> num_cols = get_numeric_cols();
    vector<string> cat_cols;
    for(int i = 0; i < labels.size(); i++) {
        bool flag = true;
        for(int j = 0; j < num_cols.size(); j++) {
            if(labels.at(i) == num_cols.at(j)) {
                flag = false;
            }
        }
        if(flag && labels.at(i) != "y") {
            cat_cols.insert(cat_cols.end(), labels.at(i));
        }
    }
    return cat_cols;
}

void Dataframe::print_cat_cols() {
    vector<string> cat_cols = get_categorical_cols();
    for(int i = 0; i < cat_cols.size(); i++) {
        cout << cat_cols.at(i) << " ";
    }
    cout << "\nNr cat cols: " << cat_cols.size();
    cout << "\nTotal nr of columns: " << labels.size();
}

void Dataframe::fix_datatype() {
    vector<string> num_cols = get_numeric_cols();
    for(int i = 0; i < num_cols.size(); i++) {
        int col_ind = get_col_index(num_cols.at(i));
        for(int j = 0; j < dataframe.size(); j++) {
            dataframe.at(j).elements.at(col_ind).is_numeric = true;
            dataframe.at(j).elements.at(col_ind).value = Helper::str_to_double(dataframe.at(j).elements.at(col_ind).object);
            dataframe.at(j).elements.at(col_ind).object = "";
        }
    }
}

void Dataframe::populate_df_cols() {
    vector<Column> new_df;
    for(int i = 0; i < labels.size(); i++) {
        Column col;
        col.label = labels.at(i);
        int col_index = get_col_index(labels.at(i));
        for(int j = 0; j < dataframe.size(); j++) {
            col.elements.insert(col.elements.end(), dataframe.at(j).elements.at(col_index));
        }
        new_df.insert(new_df.end(), col);
    }
    df_cols = new_df;
}

void Dataframe::print_df_cols() {
    for(int j = 0; j < df_cols.at(0).elements.size(); j++ ) {
        for(int i = 0; i < df_cols.size(); i++) {
            if(df_cols.at(i).elements.at(j).is_numeric) cout << " ||" << df_cols.at(i).elements.at(j).value << "|| ";
            else cout << " ||" << df_cols.at(i).elements.at(j).object << "|| ";
        }
        cout << "\n";
    }
}

void Dataframe::delete_columns(string col) {
    int col_ind = get_col_index(col);
    vector<Line> new_df;
    for(int i = 0; i < dataframe.size(); i++) {
        Line new_line;
        for(int j = 0; j < dataframe.at(col_ind).elements.size(); j++) {
            if(j == col_ind) continue;
            Element elem = dataframe.at(i).elements.at(j);
            new_line.elements.insert(new_line.elements.end(), elem);
        }
        new_df.insert(new_df.end(), new_line);
    }

    for(int i = 0; i < labels.size(); i++) {
        if(labels.at(i) == col) {
            labels.erase(labels.begin() + i);
        }
    }

    dataframe = new_df;
    populate_df_cols();
}

void Dataframe::delete_line_cat(string col, string pos_to_keep) {
    vector<Line> new_df;
    int col_ind = get_col_index(col);
    for(int i = 0; i < dataframe.size(); i++) {
        if(dataframe.at(i).elements.at(col_ind).object != pos_to_keep) {
            continue;
        }
        new_df.insert(new_df.end(), dataframe.at(i));
    }
    dataframe = new_df;
    populate_df_cols();
}

