#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void search(double *a,int n,double query )				// A function to check whether query is present in the array and to measure the time taken 
{
	for(int i=0;i<n;++i)
	  if(a[i]== query)									// If the query element is found in the array return back to main
		break;
}

int main(int argc, char *argv[])						// Using command line arguments to read inputs from the user
{
	
	int n;
	n=atoi(argv[1]); 
	clock_t t1,t2;										// clock_t variable declared to measure start and end time
	srand(time(NULL));
	
	for(int k=n; k<=n*64; k*=2)							// Running the iterations for value of k = n ,n *2 , n*4 , n*8 till n *64  ( n* (2^6))
	{
		double a[k];									// Declaring a double array of size k

		for(int i=0; i<k; ++i)							// Intialisation of array with random floating point numbers
			{
			a[i]=rand()+(rand()%10000)/10000.0;			// Random double numbers are generated by adding random integer with a random integer number between 0 and 9999 multiplied by 10^-6
			}
	
		double time,total_time=0;						// Declaration of variables for time for single query(time) and 100000 queries(total time)
	
		for(int j=0; j<10000; ++j)						// To search for random query 10000 times
		{
			t1=clock();									// Start time for a search query

			int coin=rand()%2;							// Tossing of coin
			double q=rand()+(double)(rand()%10000)/10000.0;		// Generating a random  float number
			
			int b=rand()%k;								// Generating a random integer between 0 and k-1
			
			if(coin==0)									// If tossed coin is Heads
				{
				search(a,k,q);							// Calling  search function with query as random double
				}
			else										// If tossed coin is tails
				{
				search(a,k,a[b]);						// Calling  search function with query as an random element in the array
				}

			t2=clock();									// End time for a search query	
			time=(double)(t2-t1);
			time/=CLOCKS_PER_SEC;						// Converting the time into seconds	
			
			total_time+=time;							// Adding the time for 10000 queries
		}	
	printf("%d\t%f\n",k,total_time/10000);				// Printing the average time for each query
	}

	return 0;
}

