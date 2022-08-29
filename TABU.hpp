#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <cstdio>

using namespace std;

typedef vector<bool> vec;
typedef vector<int> vec_int;

//宣告變數
vec solution;
int result;
vec_int tabu_list;   //Tabu_list FIFO 從前面insert, 後面pop
vec temporary_solution;
int temporary_pick;

//宣告function
void initialization(int);
int evaluation(vec);
bool check(int);
void record(int, int);
void selection(vec);
void transition(vec);
void print_vec(vec);
void determination(vec);
void execution(int, int, int, int);

//print
void print_vec(vec v){
    for(auto i: v){
        cout << i;
    }
}

//Initialize
void initialization(int bit){

    tabu_list.clear();
    
    solution.assign(bit,0);         
    for (int i =0; i < bit; i++)
        solution[i] = rand() % 2;       //initial result
    
    
    result = evaluation(solution);

}

//Evaluation
int evaluation(vec v){
    int size = v.size();
    int vec_sum = 0;
    for (int i=0; i< size; i++){
        vec_sum += v[i];
    }
    return vec_sum;
}

//check tabu_list
bool check(int p){
    int check_set = false;
    for (int i = 0; i <tabu_list.size(); i++)
        if (tabu_list[i] == p)
            check_set = true;
    
    return check_set;
    
}

//record
void record(int p, int capacity){
    if (tabu_list.size() < capacity){
        tabu_list.insert(tabu_list.begin(), p);
    }
    else{
        tabu_list.pop_back();
        tabu_list.insert(tabu_list.begin(), p);
    }
}


//selection
void selection(vec v){
    int size = v.size();
    int pick = rand() % size;
    if (v[pick] == 1)
        v[pick] = 0;
    else
        v[pick] = 1; 
    
    temporary_solution = v;
    temporary_pick = pick;

}


//transition
void transition(vec v){
    
    selection(v);

    if (check(temporary_pick)){
        transition(v);
    }   

}


//Determination
void determination(vec new_transition){
    int f2 = evaluation(new_transition);
    if (f2 >= result){
        solution = new_transition;
        result = f2;
    }

}

//(bit; run; iteration; capacity)
void execution(int bit, int run, int iteration, int capacity){
    
    srand((unsigned)time(NULL));
    vector<int> all_result;
    all_result.assign(run, 0);
    double run_sum = 0;

    for (int i = 0; i < run; i++){

        cout << "run-" << i+1 << endl;

        initialization(bit);

        print_vec(solution);
        cout << endl ;

        for(int k = 0; k < iteration; k++){

            transition(solution);
            record(temporary_pick, capacity);
            determination(temporary_solution);

            print_vec(temporary_solution);
            cout << endl;
            //cout << " ( CURRENT: " ;
            //print_vec(solution);
            //cout << " " << result << ")" << endl;
        }

        all_result [i] = result;
        run_sum += result;
        cout << "\n" ;

    }

    cout << "\nEND: ";
    for (auto i: all_result)
        cout << i << " ";
        
    double average = run_sum / run;
    cout << "\n";
    printf("average: %.2f",average);

}
