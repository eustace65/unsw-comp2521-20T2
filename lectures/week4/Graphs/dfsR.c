// for adjacency matrix

void dfsR(Graph g, Vertex v)
{
   visited[v] = order++;
   Vertex w;
   // foreach (w in neighbours(v))
   for (w = 0; w < g->nV; w++) {
      if (g->edges[v][w] && visited[w] == -1) 
         dfsR(g, w);
   }
}

// for adjacency list

void dfsR(Graph g, Vertex v)
{
   visited[v] = order++;
   Vertex w;
   // foreach (w in neighbours(v))
   ListNode *curr;
   for (curr = g->neighbours[v]; curr != NULL; curr = curr->next)
      w = curr->vertex;
      if (visited[w] == -1) 
         dfsR(g, w);
   }
}
