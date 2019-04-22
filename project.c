#include <stdio.h>
#include <stdlib.h>


int main()
{
    int c , v;
    readInitialization ("file.txt"  , &c , &v) ;

    /**
        logic function
            - election function electionProcess(votes, c, v); 3 mins
            // c is number of candidates and v is number of votes in the votes send
            - file operations 35 mins
                = readInitialization(fileName, &c, &v) 10 mins
                = generate(c, v, fileName) (random) 5 mins
                = readPartitions(startVoteNumber, partition): votes[v*c] 10 mins


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
    printf("Hello world!\n");
    return 0;
}
