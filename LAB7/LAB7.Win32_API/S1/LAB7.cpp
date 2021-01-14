//#include <iostream>
//#include <iomanip>
// 
//int** make( int n )
//{
//   int** c = new int*[n];
//   for( int i=0; i<n; ++i )
//   {
//      c[i] = new int[n];
//      for( int j=0; j<n; ++j)
//      {
//         c[i][j] = rand()%100;
//      }
//   }
//   return c;
//}
// 
// 
//int** copy( int** a, int n )
//{
//   int** c = new int*[n];
//   for( int i=0; i<n; ++i )
//   {
//      c[i] = new int[n];
//      for( int j=0; j<n; ++j)
//      {
//         c[i][j] = a[i][j];
//      }
//   }
//   return c;
//}
// 
//void print(int** a, int n)
//{
//   for( int i=0; i<n; ++i )
//   {
//      for( int j=0; j<n; ++j)
//      {
//         std::cout << std::setw(5) << a[i][j];
//      }
//      std::cout << std::endl;
//   }   
//   std::cout << std::endl;
//}
// 
//void dispose( int**a, int n )
//{
//   for( int i=0; i<n; ++i )
//   {
//      delete [] a[i];
//   }
//   delete [] a;
//}
// 
//void rotate( int** a, int n )
//{
//   int** c = copy( a, n );
//   
//   for( int i=0; i<n; ++i )
//   {
//      for( int j=0; j<n; ++j )
//      {
//         a[j][n-1-i] = c[i][j];
//      }
//   }
//   
//   dispose( c, n );
//}
// 
//int main() {
// 
//   srand(time(0));
//   
//   const int size = 3;
//   
//   int** m = make( size );
//   
//   print( m, size );
// 
//   for( int i=0; i<1; ++i )
//   {
//      rotate( m, size );
//      print( m, size );
//   }
// 
//   dispose( m, size );
//   system("pause");
//   return 0;
//}