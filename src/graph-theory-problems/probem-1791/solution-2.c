/*
                    1791. Find Center of Star Graph

There is an undirected star graph consisting of n nodes labeled from 1 to n. 
A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.

You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. 
Return the center of the given star graph.

*/

int findCenter(int **edges, int edgesSize, int *edgesColSize) {
    
    int l_node = -1;
    int r_node = -1;
    int res = -1;
    for (size_t i = 0; i < edgesSize; i++) 
    {
        if (l_node == -1 || r_node == -1)
        {
            l_node = edges[i][0];
            r_node = edges[i][1];
            continue;
        }

        if (l_node == edges[i][0] || r_node == edges[i][0])
            res = edges[i][0];
        
        if (l_node == edges[i][1] || r_node == edges[i][1])
            res = edges[i][1];
    }

    return res;
}