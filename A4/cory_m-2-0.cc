/* Subject: Contest submission for problem #2, file 2.cc */
/* cory_m@imail.EECS.Berkeley.EDU */
/* Thu Sep 11 05:30:10 PDT 2003 */
/*___CONTEST_SUBMISSION___ cory_m 2 */
//#include <contest.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
bool enumeratePermutations(int n, int k, int j[]);

struct list_perm {
	int x;
   struct list_perm * next;
   struct list_perm * prev;
};

typedef struct list_perm permutation;


struct all_perm {
	permutation *x;
   struct all_perm * next;
};

typedef struct all_perm permList;

permutation* makePerm(int permSize, int permArray[13])
{
	int i;
	permutation* perm= (permutation*)malloc(sizeof(permutation));
	permutation* permStart=perm;
	permutation* permPtr=perm;
	for(i=0;i<permSize-1;i++)
	{
		perm= (permutation*)malloc(sizeof(permutation));
		permPtr->next = perm;
		perm->prev=permPtr;
		permPtr->x = permArray[i];
		permPtr = perm;
	}
	perm->x=permArray[i];
	perm->next=permStart;
	permStart->prev=perm;
	
	while((permStart->x)!=1){
		permStart=permStart->next;
	}
	return permStart;
}
void freePerm(permutation* a)
{
	while((a->x)!=1){
		a=a->next;
	}
	a=a->next;
	permutation* curr = a;
	permutation* next= a->next;
	free(curr);
	while(next->x!=1){
		curr=next;
		next=next->next;
		free(curr);
		
	}
	free(next);

}
bool comparePerm(permutation* a,permutation* b){
	while(a->x!=1)
		a=a->next;
	while(b->x!=1)
		b=b->next;
	
	//compare if a=b 
	bool same = true;
	a=a->next;
	b=b->next;
	while((a->x)!=1)
	{
		if((a->x)!=(b->x))
			same = false;
		a=a->next;
		b=b->next;
	}
	if(same)
		return true;

	//compare if a = b reverse
	while(a->x!=1)
		a=a->next;
	while(b->x!=1)
		b=b->next;
	a=a->next;
	b=b->prev;
	while((a->x)!=1)
	{
		if((a->x)!=(b->x))
			return false;
		a=a->next;
		b=b->prev;
	}
	return true;
}
void addPerm(permList * root,permutation *a){
	permList* perm= (permList*)malloc(sizeof(permList));
	perm->x=a;
	perm->next=NULL;
	while(root->next != NULL)
		root =root->next;	
	root->next=perm;
}

bool findPerm(permutation* y , permList * list)
{
	do{

		if(comparePerm(list->x,y))
			return true;
		list=list->next;
	}while(list != NULL);
	return false;
}
bool checkPerm(int size,int a[13] , int maxSum){
	for(int i=0;i<size-2;i++)
		if(a[i]+a[i+1]+a[i+2]>maxSum)
			return false;
	if(a[0]+a[size-2]+a[size-1]>maxSum)
		return false;
	if(a[0]+a[1]+a[size-1]>maxSum)
		return false;
	return true;

}
void printPerm(permutation * a){
	printf("%d ",a->x);
	a=a->next;
	while((a->x)!=1){
		printf("%d ",a->x);
		a=a->next;
	}
	printf("\n");
}

void printAllPerm(permList * root){
	printPerm(root->x);
	root=root->next;
	while(root!=NULL){
		printPerm(root->x);
		root=root->next;
	}
}

int countAllPerm(permList * root){
	int num=1;
	root=root->next;
	while(root!=NULL){
		num++;
		root=root->next;
	}
	return num;
}



int main(void)
{
	//FILE *input=fopen("e.in","r");
	int numRepeat,
		permSize,
		maxSum;

	//fscanf(input,"%d",&numRepeat);
	scanf("%d",&numRepeat);
	for(int k=0;k<numRepeat;k++){
		//fscanf(input,"%d %d",&permSize,&maxSum );
		scanf("%d %d",&permSize,&maxSum );

		permList* listRoot= (permList*)malloc(sizeof(permList));
		
		int permArray[13]={1,2,3,4,5,6,7,8,9,10,11,12,13};
		permutation* first=makePerm(permSize,permArray);

		listRoot->next=NULL;
		listRoot->x=first;
		permutation* newPerm;
		
		int comb[13] = {-1};
		while(enumeratePermutations(permSize-1, permSize-1, comb)){
			for(int j=0;j<permSize-1;j++){
				permArray[j+1]=comb[j]+2;
				//printf("%d ",comb[j]);
			}
			//printf("\n");
			if(checkPerm(permSize,permArray,maxSum))
			{
				newPerm=makePerm(permSize,permArray);
				//printPerm(newPerm);
				if(!findPerm(newPerm,listRoot))
					addPerm(listRoot,newPerm);
				else 
					freePerm(newPerm);
			}
		}
		printf("Permutation size:\t%d\nMaximum triplet sum:\t%d\nValid permutations:\t%d\n\n",permSize,maxSum,countAllPerm(listRoot)-1);
	
	}
	exit(0);
	return 0;

	
}


bool enumeratePermutations(int n, int k, int j[])
{
    int i;
    if(j[0] < 0){
        for(i = 0; i < n; ++i){
            j[i] = i;
        }
        int start = k;
        int end = n - 1;
        int t;
        while(start < end){
            t = j[start];
            j[start++] = j[end];
            j[end--] = t;
        }
        return true;
    } else {
        for(i = n - 2; i >= 0 && j[i] >= j[i+1]; --i){}
        if(i < 0){
            return false;
        } else {
            int least = i + 1;
            for(int m = i + 2; m < n; ++m){
                if(j[m] < j[least] && j[m] > j[i]){
                    least = m;
                }
            }
            int t = j[i];
            j[i] = j[least];
            j[least] = t;
            if(k - 1 > i){
                int start = i + 1;
                int end = n - 1;
                while(start < end){
                    t = j[start];
                    j[start++] = j[end];
                    j[end--] = t;
                }
                start = k;
                end = n - 1;
                while(start < end){
                    t = j[start];
                    j[start++] = j[end];
                    j[end--] = t;
                }
            }
            return true;
        }
    }
}


