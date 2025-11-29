/*

997. Find the Town Judge

In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:

The town judge trusts nobody.
Everybody (except for the town judge) trusts the town judge.
There is exactly one person that satisfies properties 1 and 2.
You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. 
If a trust relationship does not exist in trust array, then such a trust relationship does not exist.

Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.

*/

int findJudge(int n, int** trust, int trustSize, int* trustColSize) 
{
    int people[n + 1];
    memset(people, 0, (n + 1) * sizeof(int));

    for (size_t i = 0; i < (size_t) trustSize; i++)
    {
        people[trust[i][0]] = -1;
        people[trust[i][1]]++;
    }

    for (size_t i = 1; i < (size_t) (n + 1); i++)
        if (people[i] == (n - 1)) return i;
        

    return -1;
}