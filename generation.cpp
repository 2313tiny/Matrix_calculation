#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>

#include<iostream>

//########### STRUCTURES
//############VARIABLE##################

struct FileWriter
{
	const char * fileName;
	std::ofstream like_pipe;


	//#constructor_1
	FileWriter( const char * fn ):fileName(fn)
	{
		like_pipe.open(fileName,std::ios::out);
	}
	

	bool  write(int x)
	{
		if( like_pipe.is_open() )
		{
			like_pipe << std::setw(3) <<  x  ;
		}
		else
		{
			std::cout << "Something WRONG...SORRY\n";
		}
	}

	bool write( char c)
	{
		if( like_pipe.is_open() )
		{
			if (c == '#') {
				like_pipe << c; 
			}
			else
			{
				like_pipe << std::endl;
				return false;
			}		//end insert if	like_pipe << c ;
		}
		else
		{
			std::cout << "I can not write your character\n";
		}
		return true;
	}	

	//destructor
	~FileWriter()
	{
		like_pipe.close();
	}
 
};


//-----OPERATION---------
//----Function , Algorithm------

void fillMatrixValue( FileWriter & fw, unsigned int row, unsigned int col, 
			unsigned int HOW_MANY_EXAMPLE)
{
	

	for( int many = 0; many < HOW_MANY_EXAMPLE; ++many)
	 {
	fw.write( '#' );
	fw.write( many + 1); //test
	fw.write('n');

	for( int i = 0; i < row; ++i)
	{
		for( int j = 0; j < col ; ++j)
			{
			int x = 0;
			x= rand()%10 +1;
			fw.write(x);	
		//	fw.write( i + j); //test
			} //end for(j;j;j)
		fw.write('n');		 
		}//end for(i;i;i )
	 fw.write('n');
	} // end for( many; many; many)
}


void InsertMatrixDimensions(unsigned int & M, unsigned int & N, unsigned int &  K,
			    unsigned int & HOW_MANY)
{
	std::cout << "Enter M , N & K for generating  \n";
	std::cout << " M x N  for A & B matrixes\n";
	std::cout << " N x K  for C & D matrixes\n ";

	std::cout << "M = ";
	std::cin  >> M; //test  open comment after test
	std::cout << " N = ";
	std::cin  >> N ; //test open comment after test
	std::cout << " K = ";
	std::cin  >> K;  //test open comment after test

	std::cout << "Enter HOW MANY example of matrix you need (number 1 to 1000)\n";
	std::cout <<  "HOW MANY MATRIXES EXAMPLES -> ";
	std::cin >> HOW_MANY; //test  open comment after test

	
	std::cout << "Please wait...." << std::endl;
}

int main()
{
	unsigned int M = 0;
	unsigned int N = 0;
	unsigned int K = 0;
	unsigned int HOW_MANY = 0;

	srand( time(NULL));// need for random value

	InsertMatrixDimensions( M, N , K, HOW_MANY);	

	FileWriter wa("a.txt"),wb("b.txt"), wc("c.txt"), wd("d.txt");



	fillMatrixValue( wa , M, N, HOW_MANY);
	fillMatrixValue( wb , M, N, HOW_MANY);
	fillMatrixValue( wc , N, K, HOW_MANY);
	fillMatrixValue( wd , N, K, HOW_MANY);		

	
	std::cout << " ++++++ main from generator.cpp ++++" << std::endl;
	return 0;	
	
}
