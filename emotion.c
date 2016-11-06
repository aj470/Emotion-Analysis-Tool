// Ayush Joshi 
// Pa2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
  char c;
  int occur;
  int super;
  char flag ;  
  struct node *next[26];
};


struct node *root;
int j=0;
FILE *WF;
int total = 0;
int Grand_total =0;
struct node *new_node(char w)
{
  struct node *temp = (struct node*)calloc(1,sizeof(struct node));
  temp->c = w;
  return temp;
};

void insert_word(char word[])
{
  struct node *ptr = root;     
  struct node *temp;           
  int word_len = strlen(word);      
  int index;                   
  int i = 0;

  while(word[i] != '\0')
  {
    index = ((int)word[i] - (int)'a');
    if(ptr->next[index] == NULL)
    {
       temp = new_node(word[i]);
       ptr->next[index] = temp;
       ptr = temp;
      if(i == word_len - 1)
      {
         ptr->flag = 'E';
      }
    }
    else
    {   
      ptr = ptr->next[index]; 
      if(i == word_len - 1)
       {
        ptr->flag = 'E';
	  }
     } 
     i++; 
  } 
    return;
}

void read_dict(FILE *di_f)
{
  char word[100]; 
  char c;         
  int i = 0;      
  int k = 0;
  while(fscanf(di_f, "%c", &c) != EOF)
    {
      if (isalpha(c))
  	  {
  	    word[i] = tolower(c);
	    k = i;
	    i++;
  	  }
      else
  	 {
	   word[k+1] = '\0';
  	   insert_word(word);
	   memset(&word[0], '\0', strlen(word));
	   i = 0;
	   k = 0;
  	}
    }
    return;
}

void match_str(char word[]) 
{
  struct node *p = root;
  int index;
  int word_len = strlen(word);
  int i = 0;
    int j=0;
   char match[100];
  while(word[i]!='\0')  
	{
     	 index = ((int)word[i] - (int)'a');              
         if (p->next[index] == NULL)
	   	{
		  	return;
		  }
      
     		else if (p->next[index] != NULL)
       		 {
			     	p = p->next[index];
				match[j] = p->c;
				if(word_len-1 == i)
				  {  
				    if(word[i] == match[j])
				      {
				       	  p->occur++;
					  break;
				       }
				    else
				      {
					continue;
				      }
				   }
				else
	        		{
				  p->super++;
				}
		}
	         j++;
		 i++;
       }
  return;
}

void create_files()
{
  char file[20];
  sprintf(file,"out%d.txt",j);
  WF= fopen(file,"w");
  return;
}


void print_result(struct node *root, char word[100], int z)
{
  struct node *p = root;
  int i = 0;

  if (p == NULL)
	{
    	return;
  }

  if (p->flag == 'E' && p->occur>0) 
    {
      total = total + p->occur;
           word[z] = 0;     
     
	    fprintf(WF,"%s %d\n", word, p->occur);
    }

  word[z + 1] = '\0';
   while(i<26)
    {
      word[z] = 'a' + i;
      print_result(p->next[i], word, z + 1);
      i++;
    }
    word[z] = '\0';
       
}


void free_root(struct node *root)
{
  int i;

  for(i = 0; i < 26; i++)
  {
    if(root->next[i] != NULL)
    {
      free_root(root->next[i]);
      root->next[i] = NULL;
    }
  }

  free(root);
  root = NULL;
}

int main(int argc, char** argv)
{
  FILE* map;
  FILE* di_f;
  FILE* da_f;

  char dic_f[20];
  char dat_f[20];
  if (argc != 2)
    {
      printf("invalid input\n");
      return 0;
    }

  map = fopen(argv[1], "r");

  if (map == NULL)
    {
      printf("invalid input\n");
      return 0;
    }

  int positive = 0;
  int negative = 0;
   int k = 0;
   int i = 0;
   char c;
   char word[100];
    while (fscanf(map, "%s %s", dic_f, dat_f) != EOF)
    { 
               root = (struct node*)malloc(sizeof(struct node));                               
	      di_f = fopen(dic_f, "r");
	      da_f = fopen(dat_f, "r");
	    
  	      read_dict(di_f);
	      fclose(di_f);

	  while(fscanf(da_f, "%c", &c) != EOF)
	    {
	      if (isalpha(c))
		{
		  word[i] = tolower(c);
		  k=i;
		  i++;
		}
	      else
		{
		      word[k+1] = '\0'; 
		      match_str(word);
		      memset(&word[0],'\0', strlen(word));
		      i = 0;
		      k = 0;
		 
		}
	    }	 
	
          fclose(da_f);
          j++;
	  //	  printf("\n\n%d\n\n", j);
	  create_files();
	  print_result(root, word, 0);
	  fprintf(WF,"TOTAL : %d\n",total);
	  Grand_total = Grand_total + total;
	  if(j==1)
	    {
	      positive = total;
	      printf("positive %d\n", positive);
	      total = 0;
	    }
	  else
	    {
	      negative = total;
	      printf("negative %d\n", negative);
	      total =0;
	    }
	   free_root(root);
	  fclose(WF);
    }

  fclose(map);

  printf("Grand Total: %d \n", Grand_total);
  //  printf("positive percentage: %d  \n", (positive)/(Grand_total));
  // printf("negative percentage: %d  \n",(negative)/(Grand_total));

  return 0;
}
