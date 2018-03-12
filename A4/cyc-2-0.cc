/* Subject: Contest submission for problem #2, file 2.cc */
/* cyc@imail.EECS.Berkeley.EDU */
/* Wed Sep 10 23:29:54 PDT 2003 */
/*___CONTEST_SUBMISSION___ cyc 2 */
// Chris Crutchfield
// 9/10/03
// Estimated time: 3 hours
// Actual time: 2.5 hours
// Comments: I really am clueless when it comes to coding in C++, 
// so this is the ugliest code i've ever produced.  I apologize if you're planning on reading this.


#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;


int vlength = 0;
class loop;
class loop
{
public:
  int number;
  bool toobig;
  loop *next;
  loop();
  int num(int len);
  loop *index(int length);
};

loop::loop()
{
  toobig = false;
  number = 0;
  next = NULL;
}

loop * loop::index(int length)
{
  loop *tmp = this;
  for(int i = 0; i < length; i++)
    tmp = tmp->next;
  return tmp;
}

int loop::num(int index)
{
  loop *tmp = this;
  for(int i = 0; i < index; i++)
    tmp = tmp->next;
  return tmp->number;
}
 
void resize(loop *root, int size)
{
  loop *tmp = root;
  for(int i = 0; i < size - 1; i++)
    {
      tmp->next = new loop();
      tmp = tmp->next;
    }
  tmp->next = root;
}

int test(loop clock, int length, int max)
{
  for(int i = 0; i < length; i++)
    {
      if(clock.num(i) + clock.num(i + 1) + clock.num(i + 2) > max)
	return 0;
    }

  return 1;
}

vector<loop> c_generate(int n, int max, int count, int len, vector<loop> mat)
{
  int iter = 0, t = 0;
  loop templ;
      for(int i = 0; i < len; i++)
	if(test(mat[i], count, max) == 0)
	  {
	    mat[i].toobig = true;
	    iter++;
	  }
      
      vector<loop> temp(len - iter);

      for(int i = 0; i < len; i++)
	{
	  if(mat[i].toobig != true)
	    {
	      temp[t] = mat[i];
	      t++;
	    }
	}
      mat = temp;
      len = len - iter;
      
  vector<loop> tmp(count * len);

  for(int i = 0; i < len * count; i++)
    resize(&(tmp[i]), count + 1);

  
  if(count != n)
    {
      for(int i = 0; i < len; i++)
	for(int j = count * i; j < count * (i + 1); j++)
	  for(int k = 0; k <= count; k++)
	    if(k == (i + 1) * count - j)
	      tmp[j].index(k)->number = count + 1;
	    else if(k > (i + 1) * count - j)
	      tmp[j].index(k)->number = mat[i].num(k - 1);
	    else
	      tmp[j].index(k)->number = mat[i].num(k);
	   
      return c_generate(n, max, count + 1, count * len, tmp);
    }
  vlength = len;
  return mat;
}


void clock_test(int j)
{
  int size, max_sum, count = 0;
  vector<loop> mat;
  vector<loop> num(1);
  resize(&num[0], 3);
  num[0].index(0)->number = 1;
  num[0].index(1)->number = 2;
  num[0].index(2)->number = 3;

  cin >> size >> max_sum;

  mat = c_generate(size, max_sum, 3, 1, num);

  for(int i = 0; i < vlength; i++)
    count += test(mat[i], size, max_sum);
  
  if(j == 0)
    {
      cout << "Permutation size:    " << size << endl;
      cout << "Maximum triplet sum: " << endl;
      cout << max_sum << " Valid permutations:  " << count << endl;
    }
  else
    {
      cout << "Permutation size:    " << size << endl;
      cout << "Maximum triplet sum: " << max_sum << endl;
      cout << "Valid permutations:  " << count << endl;
    }
}

int main()
{
  int iter;

  cin >> iter;

  for(int i = 0; i < iter; i++)
    clock_test(i);

    exit(0);
}
