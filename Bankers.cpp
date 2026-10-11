#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


typedef struct table {
    int n;
    int m;

    int **process;
    int **maxNeeds;
    int ** allocated;
    int **futureRequire;


    table(int rows, int cols) {
        n = rows;
        m = cols;

        process = new int*[n];
        allocated = new int*[n];
        maxNeeds = new int*[n];
        futureRequire = new int*[n];

        assignColumn(maxNeeds , m);
        assignColumn(allocated , m);
        assignColumn(futureRequire, m);
        assignColumn(process , 2);

   }


  void assignColumn(int **rows , int x) {

      for( int i = 0; i < n; i++ ){

          rows[i] = new int[x]; 

      }
  }

} table ;



void safeSequence(int completed , int n ,vector<vector<int>> &allprocesses , vector<int> &process ,vector<int> &avialableResources ,table * Table){
          

          // base case when all process are checked

        if( completed == n) {
              
           allprocesses.push_back(process);

        };

        for( int i=0 ; i<n ; i++ ) {
                
              // check if unmarked and future requirement is less that avialable

          bool isSuitable = true;
            
          if( Table->process[i][1] == 0  ) {
                
              for( int j=0 ; j < Table->m ; j++ ) {

                   if( Table->futureRequire[i][j] <= avialableResources[j] ){
                          
                      continue;

                   }

                  else {
                           
                       isSuitable = false ;

                       break;

                    }

               }

             if( isSuitable ){
                     
                  process.push_back(i);
                  Table->process[i][1] = 1;

                  // update avialable resources

                  for( int k=0 ; k < Table->m ; k++ ){
                        
                        avialableResources[k] += Table->allocated[i][k];

                  }

                  safeSequence(completed+1 , n , allprocesses, process , avialableResources , Table);

                   // undo the above changes 

                   process.pop_back();
                   Table->process[i][1] = 0;
                    for( int k=0 ; k < Table->m ; k++ ){
                        
                        avialableResources[k] -= Table->allocated[i][k];

                  }

                }
                
            }

        }
       
}


int main(){
    
  int numProcess = 0;
  int numResources = 0;

  cout << "enter number of process :";
  cin >> numProcess;

  cout << "enter number of resources :";
  
  cin >> numResources;

  table* Table = new table( numProcess , numResources );

   // process[pid][isdone];

   cout << "enter max need and allocated per process respectively : \n";


   for( int i=0 ; i < numProcess ; i++ ){

          cout << i << " :"  ;

          Table->process[i][0] = i ;
          Table->process[i][1] = 0 ;
                
          cout << "max need :" ;

          for( int j = 0  ; j < numResources ; j++ ){
                  
               cin >> Table->maxNeeds[i][j];
          }

          cout << "allocated :" ;

          for( int j = 0  ; j < numResources ; j++ ) {
                  
               cin >> Table->allocated[i][j];

          }

   

        for( int j=0 ; j < numResources ; j++ ){

              Table->futureRequire[i][j] = Table->maxNeeds[i][j] - Table->allocated[i][j];

        }

    }


    cout << "table : \n" ;

    cout << "process\tmaxneed\tallocated\tfuture\n" ;

 for( int i=0 ; i < numProcess ; i++ ){

        cout << "\n";

         cout << i << " \t";

         for( int j=0 ; j<numResources ; j++ ) 
              cout << Table->maxNeeds[i][j];
             
         

          cout << " \t" ;

          for( int j=0 ; j < numResources ; j++ ) 
               cout << Table->allocated[i][j];

          cout << "\t\t" ;

          for( int j=0 ; j < numResources ; j++ )
                cout << Table->futureRequire[i][j];

            
        }


    vector<int> avialableResources( numResources , 0);
    vector<int> totalResources( numResources , 0);

    cout << "\n\nenter total resources :";

    for( int i=0 ; i < numResources ; i++ ){

       cin >> totalResources[i];
    
    }

    cout << "\n\n";

   for( int i=0 ; i < numProcess ; i++ ) {
        
       for( int j=0 ; j<numResources ; j++ ) {

          totalResources[j] -= Table->allocated[i][j];

       }

    }


    avialableResources = totalResources ;

    vector<int> process;
    vector<vector<int>> allprocesses;
    
    safeSequence(0 , numProcess , allprocesses , process , avialableResources , Table);
      
    cout << "\n sequence of execution  :\n" ;
    
    for( int i=0 ; i < allprocesses.size() ; i++ ){
         
        cout << " \n";

        for( int j=0 ; j<allprocesses[i].size() ; j++ )
           
              cout << "P" << allprocesses[i][j] << " " ;
           
        }

}