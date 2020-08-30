int hasCycle(Graph g)
{
   int i;
   visited = calloc(g->nV,sizeof(int));
   i = dfsCycleCheck(g, 0);
   free(visited);
   return i;
}
