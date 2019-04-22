#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULTFILENAME "data.txt"

void shuffle(int *array, size_t n);
void generateVotes(int c, int v, const char *fileName);

void initializeArray(int *result, int siz);
void electionProcess(int *votes,int v, int c, int *result);
void readInitialization(const char *fileName,int *c,int *v);

bool* whoIsM3ana;
void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void generateVotes(int c, int v, const char *fileName)
{
    FILE *fp = fopen(fileName, "w");
    fprintf(fp,"%d\n",c);
    fprintf(fp,"%d\n",v);

    int* vote = malloc(c*sizeof(int));
    int i;

    for(i=0;i<c;i++)
    {
        vote[i] = i+1;
    }
    while(v--)
    {
        shuffle(vote,c);
        fprintf(fp,"%d",vote[0]);
        for(i=1;i<c;i++)
        {
            fprintf(fp," %d",vote[i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void initializeArray(int *result, int siz)
{
    result = malloc(siz * sizeof(int));
    int i;
    for(i=0;i<siz;i++)
        result[i]=0;
}

void electionProcess(int *votes,int v, int c, int *result)
{
    int vCounter, cCounter, voteTo;
    initializeArray(result,c);
    for(vCounter=0; vCounter<v; vCounter++)
    {
        for(cCounter=0;cCounter<c;cCounter++)
        {
            if(whoIsM3ana[votes[(vCounter*c)+cCounter]])
            {
                voteTo = cCounter;
            }
        }
        result[voteTo] += 1;
    }
}

void readInitialization(const char *fileName,int *c,int *v)
{
    FILE *fp = fopen(fileName, "r");
    fscanf(fp,"%d\n%d\n", c, v);
    fclose(fp);
}

int main()
{
    int c , v, option;
    char fileName[256];
    printf("0 = generate\n1 = read from file\nanyNumber = exit\n$ ");
    scanf("%d",&option);
    switch(option)
    {
    case 0:
        printf("Enter # of candidates and # of voters like 'c v': $ ");
        scanf("%d %d",&c,&v);
        generateVotes(c,v,DEFAULTFILENAME);
        break;
    case 1:
        printf("Enter File Name: $ ");
        scanf("%s",fileName);
        readInitialization(fileName, &c, &v);
        break;
    default:
        return 0;

    }
//    scanf("%d %d %s",&c,&v, fileName);
//    generateVotes(c,v,fileName);
//
//    scanf("%s",fileName);
//    printf("%s",fileName);
//    readInitialization(fileName, &c, &v);
    printf("\n%d %d", c, v);

//    readInitialization ("file.txt"  , &c , &v);

    /**
        logic function
            - election function electionProcess(votes, v, c, *result); 3 mins
            // c is number of candidates and v is number of votes in the votes send
            - file operations 35 mins
                = readInitialization(fileName, *c, *v) 10 mins
                = generateVotes(c, v, fileName) (random) 5 mins
                = readPartitions(startVoteNumber, partition, c, *votes): votes[v*c] 10 mins


        parallel process
            - divide to processes
            - sum the result

    **/

    /// ask for read or generate

    /// read the initialize ones (C,V)

    /// declare the arrays needed with c,v and calculate partitions and the reminder

    /**
        the master process will send for each process the partition range it will work for

        we should have an array of booleans called whoIsM3ana[] describes which one is still m3ana or left (true = m3ana, false = me4M3ana)
        initial all of them are true

        each process should do the following:
            - read its partition
            - electing the first round
                you should have a function called
                electionProcess(votes)
                {
                    for each vote
                        loop on it to the first one who is m3ana
                }

        master sum all the results to one and select the winner (more than 50%) or go to the next round
            if we went to the next round
                we should update the array whoIsM3ana[] with how is still m3ana and who is not
                nextRoundCounterArray[2] counters for the next two candidates

                each process should do the following:
                    - if the read is gone read it again
                    - electing the second round (call the electionProcess function )
                    you should have a function called
                    electionProcess(votes)
                    {
                        for each vote
                            loop on it to the first one who is m3ana
                    }

                master sum all the results to one and select the winner and output it

    **/
    return 0;
}
