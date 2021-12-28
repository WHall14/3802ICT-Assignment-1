This is a README file associated with DataFrame implemented in C++ Code

Below are possible interactions and ways to use the code. (Copy this code into main())

Example 1:
The code in this example creates a dataframe, prints the dataframe to prove it is empty which prints nothing, 
then loads more data into the dataframe then sets all of the column names with names2.
It will then add another column and delete the second column.
the code then prints the dataframe to prove these operations have occured.
it proceeds to perform the summary operation on the column titled 'hello' and prints the map returned

Code:
vector<vector<int>> vectors2 ={{20,4,4,1},
                                  {0,0,0,0,0,1},
                                  {0,0,0,1}};

    vector<int> chars = {0,0,2,1};
    string names2 [] = {"hello", "hi", "howdy"};
    DataFrame<int> df;
    df.printData();
    df.load_data(vectors2);
    df.set_columns(names2, 3);
    df.add_data(chars, "hey");
    df.printData();
    printmap(df["hello"].summary());


Example 2:
This code initalises the dataframe with a pre existing vector of vectors(vectors)
it then sets the column names with names2 and changes one column name by the name itself and the index
the code will then print the size and shape of the dataframe.
we then call a column by index with [] operator and print the min for that line.

Code:
   vector<vector<int>> vectors ={{20,4,4,1},
                                  {0,0,0,0,0,1},
                                  {-4,14,23,1}};

    string names2 [] = {"hello", "hi", "howdy"};

    DataFrame<int> df(vectors);
    df.set_columns(names2, size(names2));
    df.printData();
    df.update_column("hello", "world");
    df.update_column(1, "goodbye");
    df.printData();
    print("Size: ");
    print(df.size());
    println();
    print("Shape: ");
    print(df.shape());
    println();
    print("Min: ");
    print(df[2].min());
    println();


Example 3:
This code will initalise the dataframe with a pre existing vector of vectors, 
it will then set the columns with names2, then printing the dataframe and proceeding to delete the column titled "hello"
it will then print out the dataframe again before finishing

Code:
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
