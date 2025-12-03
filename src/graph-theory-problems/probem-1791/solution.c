/*
                    1791. Find Center of Star Graph

There is an undirected star graph consisting of n nodes labeled from 1 to n. 
A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.

You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. 
Return the center of the given star graph.

*/

int findCenter(int /*const*/ **edges, int edgesSize, int /*const*/ *edgesColSize) {
    
    size_t nodes_max_cnt = edgesSize * *edgesColSize;
    int nodes[nodes_max_cnt + 1];
    size_t node_ctn = 0;
    int res = 0;
    
    memset(nodes, 0, nodes_max_cnt * sizeof(int));
    
    for (size_t i = 0; i < edgesSize; i++) 
    {
        if (nodes[edges[i][0]]++ == 0) node_ctn++;
        if (nodes[edges[i][1]]++ == 0) node_ctn++;
    }
        
    for (size_t i = 1; i < nodes_max_cnt; i++)
    {
        if (nodes[i] == (node_ctn - 1))
        {
            res = i;
            break;
        }            
    }
    return res;
}