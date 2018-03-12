/* Subject: Contest submission for problem #2, file 2.java */
/* cs61a-mb@imail.EECS.Berkeley.EDU */
/* Thu Sep 11 00:17:02 PDT 2003 */
/*___CONTEST_SUBMISSION___ cs61a-mb 2 */
/**
 * Author Vik Singh
 * CS 198-1
 * Permutations, Problem 2, Week 2
 * Estimated time: 2.5 hours
 * Actual Time: 1 hour and 54 minutes
 * 9/7/2003
 */

import java.io.*;

class Main
{
   static final boolean CONDITION = true; // Do NOT report individual permutations

   int totalPerms = 0;

   int face[];     // Clock face
   int size;       // Number of entries
   int maxSum;     // Maximum allowed triplet sum

//default constructor P2, takes in size and maxSum

   Main(int n, int maxVal)
   {
      size = n;  maxSum = maxVal;

      face = new int [n]; //creates face of clock with array
      for ( int j = 0 ; j < n; j++ )
         face[j] = n-j;   //backwards, high to low order array

   // face[1] becomes the holder, fixed position for values
   // because I want the function to eventually check element [0]
   
      swap (0, 1, face);
   }

   static void swap (int a, int b, int[] c) //puts element [0] in [1]
   {  int x = c[a]; c[a] = c[b]; c[b] = x;  } //defined in sun's java
                                              //tutorial

   public static void main (String[] args) throws IOException {
   	
	ReadTokensFromInput rt = new ReadTokensFromInput();
    int numSets = rt.next();
    
	for (int count = 0; count < numSets; count++) {
		
		Main clock;  //instantiate a P2 object, clock
		int size;
		int max;

		size = rt.next();
		max = rt.next();
		
		clock = new Main(size, max); //initiliazes the clock object 
		clock.permute(0);          //all the calculations
		
		System.out.println("Permutation size:    " + size);
		System.out.println("Maximum triplet sum: " + max);
		System.out.println("Valid permutations:  " + clock.totalPerms + "\n");
	}

	System.exit(0);
   }

   void permute (int currentPerm)
   {  int j;

   // check the first loop
      if (currentPerm == 0)
      {
         permute(2); //because position 1 is fixed
         for (j = 2; j < size; j++)
         {
            swap (0, j, face); //changes order of values in clock
                               // except at position 1
                               
            permute (2); //to avoid too many nested loops
         }
      }
   
   // permutations of 2 and up
   
      else if (currentPerm < size-1)
      {  int pairSum = face[currentPerm-2] + face[currentPerm-1]; //check[0] & [1]

      // check the first perm call
      
         if (face[currentPerm]+pairSum <= maxSum)
            permute (currentPerm+1);

      // for the rest, check, swap, recurse, swap back
      
         for (j = currentPerm+1; j < size; j++)
         {
            swap (j, currentPerm, face);
            
         // keep going if it doesn't meet condition specified
         
            if ( face[currentPerm]+pairSum > maxSum )
               continue;
               
         // check for mirror-image
         
            if (currentPerm == 2 && face[0] > face[currentPerm])
               continue;
            permute (currentPerm+1);
         }
         
      // Regenerate the array
      
         int fix = face[currentPerm];

         for (j = currentPerm+1; j < size; j++)
            face[j-1] = face[j];
         face[size-1] = fix;

      }
      
   // check permutation
   
      else if (check(currentPerm))
         process();
   }

   void process ()
   {
      if (!CONDITION)
         report ();
      ++totalPerms;
   }
   void report  ()
   {
      for (int j = 0; j < size; j++)
         if (face[j] < 10)
            System.out.print ("  " + face[j]);
         else
            System.out.print (" "  + face[j]);
      System.out.println();
   }

   boolean check (int pos)
   {  int total = face[pos-2] + face[pos-1] + face[pos];

      if (total > maxSum)
         return false;

      if (pos == size-1)
      {
         total = face[pos-1] + face[pos] + face[0];
         if ( total > maxSum )
            return false;
         total = face[pos] + face[0] + face[1];
         if ( total > maxSum )
            return false;
      }
      return true;
   } // end check()
}

class ReadTokensFromInput {
	
	private StreamTokenizer st;
	
	public ReadTokensFromInput() throws IOException, 
	NullPointerException {
		st = new StreamTokenizer 
		(new BufferedReader(new InputStreamReader (System.in)));
	}
	
	public int current() throws IOException, NumberFormatException,
	NullPointerException {
		return (int)st.nval;
	}
	
	public int next() throws IOException, NumberFormatException,
	NullPointerException {
		st.nextToken();
		return (int)st.nval;
	}
	
}
