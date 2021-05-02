#include <iostream>
#include <fstream>
#include <cstring>

using namespace std ;


class Puzzle
{
    int rows ;
    int cols;
    char **data ;
public:
    Puzzle()
    {
        rows = 0;
        cols = 0;
        data = 0 ;
    }
    Puzzle(int r, int c)
    {
        rows = r;
        cols = c ;

        data = new char*[rows] ;
        for (int i=0;i<rows;i++)
        {
            data[i] = new char[cols] ;
            memset(data[i],0,sizeof(char)* cols ) ;
        }

    }
    ~Puzzle()
    {
        if (!data)
        {
            for (int i=0;i<rows;i++)
            {
                delete[] data[i] ;
            }
            delete[] data ;
            rows = 0 ;
            cols = 0 ;
        }
    }

    char get_val(int r, int c)
    {
        return data[r][c] ;
    }

    int get_rows() const
    {
        return rows ;
    }

    int get_cols() const
    {
        return cols ;
    }
    void set_row(int r)
    {
      rows = r ;
    }

    void set_col(int c)
    {
        cols = c ;
    }
    char* get_data_row(int i) const
    {
        return data[i] ;
    }

    // overloading the insertion operator for file input
    friend ifstream& operator >> (ifstream& inFile, const Puzzle& obj)
    {
        for (int i=0;i<obj.get_rows();i++)
        {
           inFile>>obj.get_data_row(i) ;
        }
        return inFile ;
    }

    void print()
    {
        for (int i=0;i<rows;i++)
            cout<<data[i]<<endl ;
    }

    void allocate_mem()
    {
        if (!data)
        {
            data = new char*[rows] ;
            for (int i=0;i<rows;i++)
            {
                data[i] = new char[cols] ;
                memset(data[i],0,sizeof(char)* cols ) ;
            }
        }


    }
};





void PrintSolution(char ** sol, int row, int col)
{
        cout<<"{" ;
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<col;j++)
        {
            cout<<sol[i][j]<<' ' ;
        }
        cout<<endl ;
    }
    cout<<"}"<<endl ;
}


static int paths = 0 ; // counter for total number of paths

void paths_in_Maze(Puzzle& maze,char** sol, int y_pos, int x_pos)
{

    if (x_pos==maze.get_cols()-1 && y_pos== maze.get_rows()-1) // base case
    {
        sol[y_pos][x_pos] = '0';
        paths++ ;
        //PrintSolution(sol,y_pos,x_pos) ;
    }

    /*check InBound errors
      check for a block (i.e: a 1)
      check for repetition (i.e: not moving to the same square again) */
    else if( x_pos>=maze.get_cols() || y_pos>=maze.get_rows() ||
             maze.get_val(y_pos,x_pos)=='1' || sol[y_pos][x_pos]== '0' )
     {
         return  ; // invalid path
     }

    else
    {

        /* Backtracking */

        // choose a square (i.e: mark it )
        sol[y_pos][x_pos]= '0' ; // valid path

        // explore all possible paths from that square
        paths_in_Maze(maze,sol,y_pos,x_pos+1) ; // move right
        paths_in_Maze(maze,sol,y_pos+1,x_pos) ; // move down

        // un-choose that square
        sol[y_pos][x_pos]='1' ; // i.e: un-mark it

    }

}
int main()
{

    ifstream Infile ;
    ofstream Outfile ;
    Puzzle maze ;
    int row, col ;
    char **sol  ; // acts as a container for storing the squares that have been marked

    Infile.open("input2.txt") ;
    if (!Infile)
    {
        cout<<"file could not be opened!!"<<endl ;
        return 1 ;
    }

    else

    {
            Infile>>row>>col ; // read row and col size from file
            maze.set_row(row) ;
            maze.set_col(col) ;
            maze.allocate_mem() ; // allocate the required size of memory
            Infile>>maze ; // store the maze in the maze object
            maze.print() ;

    }

   Outfile.open("output2.txt") ;
   if(!Outfile)
   {
       cout<<"file could not be opened"<<endl ;
       return 1 ;
   }
            // allocate the max possible size for sol array
        sol = new char*[row] ;
        for (int i=0;i<row;i++)
        {
            sol[i] = new char[col] ;
            memset(sol[i],1,sizeof(char)* col ) ;
        }

            paths_in_Maze(maze,sol,0,0) ; //0,0 are the starting co-ordinates

            cout<<"Total number of paths : "<<paths<<endl ;
            Outfile<<paths<<endl ;

            for (int i=0; i< 5;i++)
            {
                delete[] sol[i] ;
            }

            delete [] sol ;
            Infile.close() ;
            Outfile.close() ;

            return 0 ;

}
