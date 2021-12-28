#include <iostream>
#include <vector> // for vectors
#include <string> // for strings
#include <concepts> // for concepts like integral and keywords requires
#include <algorithm> //for algorithms like find
#include <tuple> // for using loops with
#include <numeric>
#include <map> // for the Vec class

using namespace std;

auto scan = [](auto x){cin >> x;}; // lambda functions for printing to screen
auto print = [](auto x){cout << x << " ";};
auto println = [](){ cout << "\n";};

template<typename M, typename J> // template made to print the map created by the summary() method
void printmap(map<M, J> p){
    for (auto& it : p) {
        print(it.first);
        print(it.second);
        println();
    }
}

template<typename G>
requires integral<G> || floating_point<G>
class Vec: public std::vector<G>{ // Vec class inherits publically from std::vector
    std::vector<G> container;//stores values

public:
    //1.8
    //These operations should only be used if it is integral or floating point type

    explicit Vec(std::vector<G> p){
        copy(p.begin(), p.end(), back_inserter(container)); // constructs Vec with another vector
    }

    G min(){
        return *min_element(container.begin(), container.end()); // returns the minimum element
    }

    G max(){
        return *max_element(container.begin(), container.end()); // returns the maximum element
    }

    float mean(){ // calculates and returns the mean
        int n = container.size();
        if (n != 0){
            return accumulate(container.begin(), container.end(), 0.0) / n;
        }else{
            return 0;
        }
    }

    float median(){ // calculates and returns the median
        int mid = container.size()/2;
        nth_element(container.begin(), container.begin()+mid, container.end());
        int contn = container[mid];
        if (container.size()%2 == 0){
            nth_element(container.begin(), container.begin()+mid-1, container.end());
            return 0.5*(contn+container[mid-1]);
        }else{
            return contn;
        }
    }

    G mode(){ // calculates and returns the mode via a map
        map<int, int> temp; // create a map of the same size as container
        for (int i = 0; i < container.size(); ++i) {
            temp[container[i]]++;
        }
        auto comp = [](const decltype(temp)::value_type & p1, const decltype(temp)::value_type & p2) {return p1.second < p2.second;};
        return (max_element(temp.begin(), temp.end(), comp)->first);
    }

    map<string, G> summary(){ // returns results of all methods in this template class in a map
        map<string, G> ret;
        ret["min"] = min();
        ret["max"] = max();
        ret["mean"] = mean();
        ret["median"] = median();
        ret["mode"] = mode();

        return ret;
    }

};

template<typename T>
class DataFrame {
        vector<string> *columnNames;
        vector<vector<T>> *data_vec;
        int contSize;

        void resize_containers(){// resizes containers to current contSize
            data_vec->resize(contSize);
            columnNames->resize(contSize);

        }

        bool indexcheck(int index){//True if its in the bounds of contSize, false otherwise
            if (index < 0 || index > contSize-1){ // if it is not an index within the columnNames
                print("Error: Bad column name or index provided.\n");
                println();
                return false;
            }
            return true;
        }

        // Destructor not required as data_vec and columnNames will be sorted out by the vector<> destructors

        public:

            void printData(){//prints the data in the data_vec along with the column names
                for (auto [it, it2] = tuple{columnNames->begin(), data_vec->begin()}; it2 != data_vec->end();  it++, it2++) {
                    print(">");
                    print(*it);
                    for (auto col = it2->begin(); col != it2->end() ; ++col) {
                        print(*col);
                    }
                    println();
                }
                println();
            }

            //1.1
            DataFrame(){ //intalises an empty dataframe
                contSize = 0;
                data_vec = new vector<vector<T>>;
                columnNames = new vector<string>;
            };

            explicit DataFrame(const vector<vector<T>> &vectors){ // intalises a data_vec with the vector of vectors
                contSize = vectors.size();
                data_vec = new vector<vector<T>>(contSize); // initalise.
                for (int i = 0; i < contSize; i++) { // loop through vector of vectors and set values
                    data_vec->at(i).resize(vectors[i].size());
                    for (int j = 0; j < vectors[i].size(); j++) {
                        data_vec->at(i).at(j) = vectors[i][j];
                    }
                }
                columnNames = new vector<string>(contSize);
            }


            //1.2
            void load_data(const vector<vector<T>> &vectors){ // copying a whole dataset over and wiping old data
                data_vec->clear(); // emptys old data
                columnNames->clear();
                contSize = vectors.size();
                resize_containers(); // resizes container to new size
                for (int i = 0; i < contSize; i++) { // sets new values in data_vec
                    data_vec->at(i).resize(vectors[i].size());
                    for (int j = 0; j < vectors[i].size(); j++) {
                        data_vec->at(i).at(j) = vectors[i][j];
                    }
                }
            }

            void add_data(const vector<T> &vector){ //adds a single vector without column name
                contSize++;
                resize_containers(); // expand data_vec
                auto it = data_vec->end()-1;
                for (int i = 0; i < vector.size(); i++) { // add new vector
                    it->push_back(vector[i]);
                }
            }

            void add_data(const vector<vector<T>> &vectors){
                if (vectors.size() <= 0){ // if there is nothing in the vector output an error
                    print("Error: You must pass at least one vector");
                    println();
                    return;
                }
                int old_contSize = contSize;
                contSize = contSize + vectors.size();
                resize_containers(); // resizes data_vec to new size
                for (auto [i, it] = tuple{old_contSize, vectors.begin()}; i < contSize; i++, it++) { // adds new vectors into the data_vec
                    for (int j = 0; j < it->size(); j++) {
                        data_vec->at(i).push_back(it->at(j));
                    }
                }
            }

            void add_data(const vector<T> &vector, const string &column_name){ // adds vector with a column name into data_vec
                add_data(vector);
                auto it = columnNames->end()-1;
                *it = column_name;
            }

            void add_data(const vector<vector<T>> &vectors, const string column_names []){ // adds multiple vectors with multiple column names into data_vec
                try {
                    int old_contSize = contSize;
                    add_data(vectors);
                    for (auto [i, j] = tuple{old_contSize, 0}; i < contSize; i++, j++) {
                        columnNames->at(i) = column_names[j];
                    }
                }catch(...){
                    print("Must be equal strings and and Vectors");
                    println();
                }
            }


            //1.3
            void set_columns(const string column_names[], const int colNamSize){ //sets the column names for every column in the data_vec must be exact
                if(contSize != colNamSize){ // Must set names for all existing columns
                    print("Error: Number of column names provided (");
                    print(columnNames->capacity());
                    print(") to equivalent to required amount (");
                    print(colNamSize);
                    print(").\n");
                    println;
                    return;
                }
                for (int i = 0; i < colNamSize; i++) {
                    columnNames->at(i) = column_names[i];
                }
            }


            //1.4
            void update_column(const string& oldName, const string &newName){ // updates the name of columns, takes the old name and replaces it with the new one
                auto it = find(columnNames->begin(), columnNames->end(), oldName);
                int index = distance(columnNames->begin(), it);
                if (!indexcheck(index)) return;
                columnNames->at(index) =  newName;
            }

            void update_column(int index, const string &name){ // updates the column name at a given index with a new name
                if (!indexcheck(index)) return;
                columnNames->at(index) =  name;
            }


            //1.5
            void update_columnval(int column_idx, vector<T> _vector){ // updates the vector at a set index
                if (!indexcheck(column_idx)) return;
                data_vec->at(column_idx).assign(_vector.begin(), _vector.end());
            }

            void update_columnval(const string &column_name, vector<T> _vector){ // updates the vector at a given column name
                auto it = find(columnNames->begin(), columnNames->end(), column_name);
                int index = distance(columnNames->begin(), it);
                if (!indexcheck(index)) return;
                update_columnval(index, _vector); // calls the index version of this function as they are similar
            }

            void delete_column(int column_idx){ // deletes the column at given index

                int last_index = contSize-1;

                if (!indexcheck(column_idx)){ // if it is in the bounds of the vectors
                    print("Not in bounds");
                    println();
                    return;
                }

                if(column_idx != last_index){ // if the index is not the last one then we want to move it there by swapping
                    int curr = column_idx;
                    while(curr != last_index){
                        data_vec->at(curr).swap(data_vec->at(curr+1)); //swap the vectors
                        columnNames->at(curr).swap(columnNames->at(curr+1)); //swap strings related to Vec
                        curr++;
                    }
                }

                //remove variables
                std::destroy(data_vec->at(last_index).begin(), data_vec->at(last_index).end());
                columnNames->at(last_index).erase();

                //resize the data and names vectors to one less then before.
                contSize--;
                resize_containers();
            }

            void delete_column(const string &column_name){
                auto it = find(columnNames->begin(), columnNames->end(), column_name);
                if (it == columnNames->end()){
                    print("Error: Bad column name provided");
                    println();
                    return;
                }
                delete_column(distance(columnNames->begin(), it));// calls the index version of this function as they are similar
            }


            //1.6
            Vec<T> operator [](const string &column_name){ // returns a class Vec version of the vector entry
                int i = 0;
                for (i; i < columnNames->size(); i++) {
                    if(column_name == columnNames->at(i)){
                        break;
                    }
                }
                if (i == columnNames->size()){
                    print("Error: Bad column name provided");
                    println();
                    return Vec(data_vec->at(0));
                }
                return Vec(data_vec->at(i));
            }

            Vec<T> operator [](int column_idx){// returns a class Vec version of the vector entry
                try {
                    return Vec(data_vec->at(column_idx));
                }catch(...) {
                    print("Error: Bad index provided");
                    println();
                    return Vec(data_vec->at(0));
                }

            }


            //1.7
            int size(){ // returns the current size of the entire data_vec
                int total = 0;
                for(auto row = data_vec->begin(); row != data_vec->end(); row++){
                    total = total + row->size();
                }
                return total;
            }

            int shape(){ // returns the shape of the data_vec
                return data_vec->size();
            }
};







int main() {

    vector<vector<int>> vectors2 ={{20,4,4,1},
                                   {0,0,0,0,0,1},
                                   {0,0,0,1}};

    string names2 [] = {"hello", "hi", "howdy"};
    DataFrame<int> df;
    df.load_data(vectors2);
    df.set_columns(names2, 3);
    df.printData();
    df.delete_column("hello");
    df.printData();



    return 0;
}
