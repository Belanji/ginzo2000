#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
void read_check(int read_status, int line);

int main(int argc, char **argv)
{
  int x[3], lmin, lmax;
  int comparison_column;
  double n[3],l[3],m[3],S,P;	
  FILE * ic_file; 
  char *file_to_slice, string_placeholder[400];
  int read_status;
  int reading_line=1;

  //printf("argv=%s.\n\n",argv[2]);



  if ( argc<5 || argc >5 )
    {

      printf(" Usage:\n\n ginzo2000 comparison_column min_value max_value file_to_cut.\n\n");
      printf("planetocut: integer represententing the plane (yz=1,xz=2 and yx=3).\n");

    }

  comparison_column=atoi(argv[1]);
  lmin=atoi(argv[2]);
  lmax=atoi(argv[3]);
  file_to_slice=argv[4];


  ic_file=fopen(file_to_slice,"r");
  printf("x,y,z,nx,ny,nz,lx,ly,lz,S,P\n");

  if (ic_file== NULL)
    {
      printf("Unable to find the input file.\nPlease, stop drinking at work.\n\nAborting the program.\n\n");
      exit(0);
    }

  //get the file header:
  fgets(string_placeholder,400,ic_file);
  reading_line++;



  
  //Let's work:
  fgets(string_placeholder,400,ic_file);


  while( feof(ic_file) == 0 )
    {
      
      read_status=sscanf(string_placeholder,"%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",&x[0],&x[1],&x[2],&n[0],&n[1],&n[2],&l[0],&l[1],&l[2],&S,&P);
      read_check(read_status,reading_line);


      if( lmin < x[comparison_column] && x[comparison_column] < lmax )
	{
		  
	  printf("%d,%d,%d,%.3lf,%.3lf,%.3lf,%.3lf,%.3lf,%.3lf,%.3lf,%.3lf\n", x[0],x[1],x[2], n[0], n[1], n[2], l[0], l[1], l[2],S, P);

	}
      reading_line++;

      fgets(string_placeholder,400,ic_file);
    }    
}

void read_check(int read_status, int line)
{

  if(read_status != 11)
    {
      printf("Failed to read the inicitial condtion file line number %d between field numbers %d-%d.\n Aborting the program.\n\n",line,read_status,read_status+1);
      exit(0);
    }

}
