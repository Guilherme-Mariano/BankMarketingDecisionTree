
#include "Dataframe.h"
#include "DecisionTree.h"

int main() {
    Dataframe df = Dataframe();
    df.load_from_file("data/data.csv");
    df.fix_datatype();
    df.populate_df_cols();
    df.print_cat_cols();
    DecisionTree dt = DecisionTree(df);
    dt.print_splits();
    return 0;
}
