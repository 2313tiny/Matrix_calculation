#include<iostream>
#include<fstream>
#include<cassert>
#include<iomanip>

//###################################################
//###################################################
// #### DATA PART, STRUCTURE PART ##################
//###################################################
//###################################################


struct Matrix
{

	const unsigned int m_row;
	const unsigned int m_col;
	
	int * m_array;

	//##### ctor_1
	Matrix( const unsigned int R ,const  unsigned int C)
		: m_row(R), m_col(C )
	{
		m_array = new int [R*C]; 
	}

	int getMatrixRow()
	{
		return m_row;
	}

	int getMatrixCol()
	{
		return m_col;
	}

	int & operator()( const int i,const int j)
	{
		return m_array[ getMatrixCol() * i + j ];
	}

};




struct ReadFile
{
	const char * filename;
	std::ifstream file_stream;


	//#ctor_1
	ReadFile (const char * fn):filename(fn)
	{
		file_stream.open( filename, std::ios::in);
	    	assert(file_stream.is_open() &&  "File opening");
	}

	bool my_read(int &i)
	{
	//	file_stream.ignore();       //this case read but not correct
	//	file_stream.ignore(1,' ');
	//	file_stream.ignore(1,EOF);
		if( file_stream >> i )
		{
			// i= 12;
			file_stream.get()>> i ;//i = 12;
			//	std::cout << i  << " ";
		}

		else
		{
			return false;
		}
		return true;
	}

	//destructor
	~ReadFile()
	{
		file_stream.close();	}

};

struct WriteFile
{
	const char *filename;
	std::ofstream file_stream;	

	//construtor
	WriteFile( const char * fn):filename(fn)
	{
		file_stream.open( filename, std::ios::out);
		assert( file_stream.is_open() && " File opening");
	}

	bool my_write( int & i)
	{
		if( file_stream << i)
		{
		   //	std::cout << i << " ";
		}
		else
		{
			return false;
		}
		return true;
	}


	//destructor
	~WriteFile()
	{
		file_stream.close();		
	}	


};


//###################################################
//###################################################
//######PROCEDURE PART, ALGORITHM PART##############
//###################################################



bool readMatrix( Matrix & to ,  ReadFile & from )
{
	from.file_stream.ignore(1,'#');
	from.file_stream.ignore(1,EOF);
	from.file_stream.ignore(2,EOF);
	int x= 0;
	for( int i = 0; i < to.getMatrixRow(); ++i)
	{
		for(int j= 0; j < to.getMatrixCol(); ++j)
		{
			if(from.my_read(x) )			
			{
				to(i,j) = x;
		  	//std::cout << to( i, j ) << " "; test	
			}
			else
			{
		// std::cout << "Can not read file... "<< &from <<  std::endl; 
				return false;
			}
		} //end for(j;j;j)
	//		  std::cout << "\n";//test
	}//end for(i;i;i)
		from.file_stream.ignore(1,EOF); 
	//	std::cout << "\n" ; // space between matrixes
	return true;
	std::cout << " ------readMatrix ---DONE \n";
	
}

void addMatrix( Matrix & from1 , Matrix & from2 , Matrix & to )
{

	assert( from1.getMatrixRow() == from2.getMatrixRow());
	assert( from1.getMatrixCol() == from2.getMatrixCol());
	for(int i = 0; i < from1.getMatrixRow();++i )
	{
		for(int j = 0; j < from2.getMatrixCol(); ++j)
		{
			to(i,j) = from1(i,j) + from2(i,j);
		//	std::cout << std::setw(2) << to(i,j)<< " " ; //test
		}//end for(j;j;j;)
	//		std::cout << std::endl; //test
	}//end for(i;i;i)
//	std::cout << " -------addMatrix ---DONE \n";
}

void multMatrix( Matrix & from1 ,  Matrix & from2, Matrix & to )
{
	assert( from1.getMatrixCol() == from2.getMatrixRow());
	assert( from1.getMatrixRow() == to.getMatrixRow() );
	assert( from2.getMatrixCol() == to.getMatrixCol());

	for(int i = 0 ; i < from1.getMatrixRow(); ++i)	
	{
		//int s = 0;
		for( int j = 0; j < from2.getMatrixCol(); ++j)
		{
			int s = 0;
			for( int k = 0; k < from1.getMatrixCol(); ++k)
			{
				s += from1(i,k)* from2(k,j);
			}
			to(i,j) = s;
	//		std::cout << s << " ";
		}
	//	std::cout << std::endl;
	}	
}

bool  writeMatrix( Matrix & from  ,WriteFile & to )
{
	int p = 1;
	to.file_stream.put('#');
	to.file_stream << p <<"  ";
	to.file_stream << "\n";	
	for( int i = 0; i < from.getMatrixRow(); ++i )
	{ 
		for( int k = 0; k < from.getMatrixCol(); ++k)
		{
			if( to.my_write( from(i,k)  ))
			{
			//	to.my_write( from(i,k));
				to.file_stream.put(' ');
			}
			else
			{
	//	  std::cout <<"Can not write file..." << &from << std::endl;
			return false;
			}
		}//end for(k;k;k)
		to.file_stream << "\n";	
	//	std::cout << std::endl;
 		
	}//end for(i;i;i)
	return true;
}

void InputMatrixDimensions( unsigned int & M, 
			    unsigned int & N,
			    unsigned int & K,
			    unsigned int & HOW_MANY)
{
	std::cout << "Please enter A & B matrix Row\n ";
	std::cout << " M = ";
	std::cin >> M; //remove after test
	
	std::cout << "Please enter A & B matrix Columns\n ";
	std::cout << " N = ";
	std::cin >> N; //remove after test
		

	std::cout << "Please enter A & B matrix Columns\n ";
	std::cout << " K = ";
	std::cin >> K; //remove after test
	std::cout << std::endl;	

	std::cout << "How many matrix you need to check\n";
	std::cin >> HOW_MANY;
	std::cout << std::endl;

}


int main()
{
	unsigned int M = 0;
	unsigned int N = 0;
	unsigned int K = 0;
	unsigned int HOW_MANY = 0;
	
	InputMatrixDimensions( M, N, K , HOW_MANY );

	Matrix A(M,N), B(M,N), AB(M,N),
	       C(N,K), D(N,K ), CD(N,K), ABCD(M,K);

	ReadFile ra("a.txt"), rb("b.txt"), rc("c.txt"), rd("d.txt");
	WriteFile wa("result.txt");
/*
	readMatrix(A, ra );
	readMatrix(B, rb );
	addMatrix( A, B, AB);
	
	readMatrix(C, rc);
	readMatrix(D, rd);
	addMatrix( C, D, CD);

	multMatrix(AB, CD, ABCD);

	writeMatrix( ABCD, wa);
*/


	while( readMatrix(A,ra) && readMatrix(B,rb) && readMatrix(C,rc) &&
		 readMatrix(D,rd)   )
	{
		addMatrix(C,D, CD);
		addMatrix(A,B, AB);
		multMatrix(AB, CD, ABCD);
		
		writeMatrix(ABCD, wa);
	}
		


	std::cout << "\n+++++++++++++ ALL CURRENT +++++++++++"<< std::endl;
	return 0;

}
