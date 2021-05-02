#include <iostream>
#include <cstring>
#include <fstream>

using namespace std ;

/* stores the co-ordinates of the 2D array */
 class Point_2D
{
    int x ;
    int y ;

public:
    Point_2D() ;
    Point_2D(int x_pos, int y_pos) ; // copy ctor
    ~Point_2D() ;
    int get_x()  const ;
    int get_y() const  ;
    void mark(int x, int y) ; // marks a given square to avoid repetition

};

Point_2D::Point_2D()
{
    x =  0 ;
    y =  0 ;
}
Point_2D::Point_2D(int x_pos, int y_pos)
{
    x = x_pos ;
    y=  y_pos ;
}
Point_2D::~Point_2D()
{
    x=0 ;
    y=0 ;
}
int Point_2D::get_x() const
{
    return x ;
}
int Point_2D::get_y() const
{
    return y ;
}
void Point_2D::mark(int x, int y)
{
    this->x = x ;
    this->y = y ;
}

/* This class is used as a container (ie: a 2D array) */
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
    char* get_data_row(int i) const  // returns a particular row as a char*
    {
        return data[i] ;
    }

    friend ifstream& operator >> (ifstream& inFile, const Puzzle& obj)
    {
        for (int i=0;i<obj.get_rows();i++)
        {
           inFile>>obj.get_data_row(i) ; //storing data from file row by row
        }
        return inFile ;
    }

    void print()
    {
        for (int i=0;i<rows;i++)
            cout<<data[i]<<endl ;
    }

    void allocate_mem() // dynamically allocates memory
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

/* index is used to access the next element of both str and chosen.
chosen is used to keep track of the squares that have been marked.
x and y are the current coordinates in the maze */
bool solve(Puzzle& puzzle,char ch,char* str,int x,int y,int index, Point_2D* chosen)//, Point_2D* chosen)
{

    if (index== strlen(str) ) // base case
    {
        return true ;
    }

    /* checks InBound errors and also if the given letter exists consecutively
     . Returns false if any of the conditions given below is true*/
    else if ( x<0 || x>=puzzle.get_cols() || y<0 ||
              y>=puzzle.get_rows() || puzzle.get_val(y,x) != ch )
           {
               return false ;
           }


    else
    {
        for (int i=0;i<index;i++)
        {
            // checking if the given square is already marked
            if (x== chosen[i].get_x() && y== chosen[i].get_y()) return false ;

        }
        // if not marked, mark it
        chosen[index].mark(x,y) ;


        //explore all possible paths from the given square.
   bool result = solve(puzzle,str[index+1],str, x, y-1,index+1,chosen)     // up
              || solve(puzzle,str[index+1],str, x, y+1,index+1,chosen)     // down
              || solve(puzzle,str[index+1],str, x-1, y,index+1,chosen)     // left
              || solve(puzzle,str[index+1],str, x+1, y,index+1,chosen) ;   // right

              /* if any 1 of the 4 recursive calls returns true, it means
                word has been found. Therefore, return true */
              if (result)  return true ;


            else return false ;

           }
}



int main()
{

     bool found ;
     int x_pos, y_pos, row, col, total_words ;
     Point_2D chosen[10] ; // array of Point_2D for storing the co-ordinates of the squares that have been marked
     Puzzle puzzle ;
     ifstream Infile ;
     ofstream Outfile ;
     char word[100] ;

     Outfile.open("output1.txt") ;
        if (!Outfile)
        {
            cout<<"file could not be opened"<<endl ;
             return 1 ;
        }

     Infile.open("input1.txt") ;
     if (!Infile)
     {
         cout<<"file could not be opened"<<endl ;
         return 1 ;
     }
     else
     {
          Infile>>row>>col ;
          cout<<row<<" "<<col<<endl ;
          puzzle.set_row(row) ;
          puzzle.set_col(col) ;
          puzzle.allocate_mem() ;
          Infile>>puzzle ;
          puzzle.print() ;
          Infile>>total_words ;
          cout<<total_words<<endl<<endl ;

         Infile.getline(word,100) ;
            // get a word to search from file
          for (int k=0;k<total_words;k++)
          {
              Infile.getline(word,100) ;
              cout<<word<<endl ;
            // search the 1st letter of that word in the puzzle
       for (int i=0;i<row;i++)
         {
             for (int j=0;j<col+1;j++)
             {
                 found = false ;
                 if (word[0] == puzzle.get_val(i,j) ) // 1st letter of the given word found
                 {
                    x_pos = j ;
                    y_pos = i ;
                    // check if the whole word exists in the puzzle
                    if ( solve(puzzle,word[0],word,x_pos,y_pos,0,chosen) ) // returns True if word found

                        {
                            // Word found. Therefore, output the co-ordinates of the 1st letter
                            cout<<y_pos<<x_pos<<endl ;
                            Outfile<<y_pos<<x_pos<<endl ;
                            found = true ;
                            break ;
                        }
                 }

             }
             if (found) break ; // word has been found. Now search for the next word in file
         }
                    if (!found && k!=0 )
                    {
                        // if the given word does not exist , output "n"
                        cout<<"n"<<endl ;
                        Outfile<<"n"<<endl ;
                    }

        }

     }

    Infile.close() ;
    Outfile.close() ;
     return 0 ;

}
