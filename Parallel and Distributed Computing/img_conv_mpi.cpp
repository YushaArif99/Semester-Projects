#include<png++/png.hpp>
#include<omp.h>
#include<bits/stdc++.h>

typedef std::vector<double> Array;
typedef std::vector<Array> Matrix;

using namespace std;


vector<double> getGaussian(int height, int width, double sigma)
{
    vector<double> kernel(height);

    double sum = 0;

    for (int i=0 ; i<height ; i++) {
        kernel[i] = exp(-(i*i)/(2*sigma*sigma))/(sqrt(2*M_PI)*sigma);   //gaussian kernel equation. Normal distribution
        sum += kernel[i];
    }

    for (int i=0 ; i<height ; i++) {
            kernel[i] /= sum;
    }

    cout<<endl;
    return kernel;
}

vector<Matrix> loadImage(const char *filename,int fh,int fw)
{
    png::image<png::rgb_pixel> image(filename);
    std::cout<<image.get_height()<<" "<<image.get_width()<<endl;
    vector<Matrix> imageMatrix(3, Matrix(image.get_height(), Array(image.get_width())));

    int h,w;
    for (h=0 ; h<image.get_height(); h++) {
        for (w=0 ; w<image.get_width(); w++) {

            imageMatrix[0][h][w] = image[h][w].red;
            imageMatrix[1][h][w] = image[h][w].green;
            imageMatrix[2][h][w] = image[h][w].blue;
        
        }
    }
    cout<<imageMatrix[0].size();
    cout<<" "<<imageMatrix[0][0].size()<<endl;
    return imageMatrix;
}

void saveImage(vector<Matrix> &image, string filename)
{
    assert(image.size()==3);

    int height = image[0].size();
    int width = image[0][0].size();
    int x,y;

    cout<<height<<" "<<width<<endl;
    png::image<png::rgb_pixel> imageFile(width, height);

    for (y=0 ; y<height ; y++) {
        for (x=0 ; x<width ; x++) {
            imageFile[y][x].red = image[0][y][x];
            imageFile[y][x].green = image[1][y][x];
            imageFile[y][x].blue = image[2][y][x];
        }
    }
    imageFile.write(filename);
}

vector<Matrix> applyFilter(vector<Matrix> &image, vector<double> &filter){

    assert(image.size()==3 && filter.size()!=0);

    int height = image[0].size();
    int width = image[0][0].size();
    int filterHeight = filter.size();
    int filterWidth = filterHeight;
    int newImageHeight = height;
    int newImageWidth = width - filterWidth + 1;
    int d,i,j,fh,fw;
    int newImageHeight2 = newImageHeight - filterHeight + 1;
    int newImageWidth2 = newImageWidth;

    vector<Matrix> newImage(3, Matrix(newImageHeight, Array(newImageWidth)));
    vector<Matrix> newImage2(3, Matrix(newImageHeight2, Array(newImageWidth2)));

    auto start = chrono::high_resolution_clock::now(); 

    // horizontal pass
    #pragma omp parallel
    {

        #pragma omp master
        {  
            std::cout<<"Threads: "<<omp_get_num_threads()<<endl;
        }

        #pragma omp for private(i,j)
        for (i=0 ; i<newImageHeight ; i++) {

            for (j=(filterWidth/2); j<width - (filterWidth/2); j++) {
                        
                for (int w = 0; w<filterHeight ; w++) {
                   
                    newImage[0][i][j-(filterWidth/2)] += filter[w]*image[0][i][j-(filterWidth/2)+w];
                    newImage[1][i][j-(filterWidth/2)] += filter[w]*image[1][i][j-(filterWidth/2)+w];
                    newImage[2][i][j-(filterWidth/2)] += filter[w]*image[2][i][j-(filterWidth/2)+w];
                            
                }
            }
        }

        #pragma omp barrier

        #pragma omp master
        {
            std::cout<<"horizontal pass complete\n";

        }

        //vertical pass

        #pragma omp for private(i,j)
        for (i=filterHeight/2 ; i<newImageHeight - filterHeight/2 ; i++) {
            for (j=0; j<newImageWidth2 ; j++) {
                //std::cout<<omp_get_thread_num();
                for (int h = 0; h<filterHeight ; h++) {
                    newImage2[0][i-(filterHeight/2)][j] += filter[h]*newImage[0][i-(filterHeight/2)+h][j];
                    newImage2[1][i-(filterHeight/2)][j] += filter[h]*newImage[1][i-(filterHeight/2)+h][j];
                    newImage2[2][i-(filterHeight/2)][j] += filter[h]*newImage[2][i-(filterHeight/2)+h][j];
                }
            }
        }

        #pragma omp master
        {
            std::cout<<"vertical pass complete\n";

        }
    }

    auto end = chrono::high_resolution_clock::now(); 

    double time_taken =  
      chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
  
    time_taken *= 1e-9; 
  
    cout << "Time taken by Filtering is : " << fixed  
         << time_taken << setprecision(9); 
    cout << " sec" << endl;


    return newImage2;
}

vector<Matrix> applyFilter(vector<Matrix> &image, vector<double> &filter, int times)
{
    vector<Matrix> newImage = image;
    for(int i=0 ; i<times ; i++) {
        newImage = applyFilter(newImage, filter);
    }
    return newImage;
}

string substring(char *str);

int main(int argc,char** argv)
{   
    int n_threads;
    cout<<"Threads: ";
    cin>>n_threads;
    omp_set_num_threads(n_threads);

    vector<double> filter = getGaussian(9,9, 10);
    char imageName[30];
    cout << "Loading image..." << endl;
    cout<<"Image name: ";
    cin>>imageName;
    vector<Matrix> image = loadImage(imageName,filter.size(),filter.size());


    cout << "Applying filter..." << endl;

    vector<Matrix> newImage = applyFilter(image, filter,2);
    


    cout << "Saving image..." << endl;
    string suff = "_blur.png";
    string blurredImageName = substring(imageName) + suff;
    saveImage(newImage, blurredImageName);
    cout << "Done!" << endl;
}


string substring(char *str){
    char *c = str;
    string newstr;
    while(*c != '.'){
        newstr += *c;
        c++;
    }
    return newstr;
}