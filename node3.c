#include <stdio.h>

struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };
int neighbor3[4] = {0};
struct rtpkt default3;
extern int TRACE;
extern int YES;
extern int NO;
extern void tolayer2(struct rtpkt packet);

struct distance_table
{
  int costs[4][4];
} dt3;


extern void read3(FILE *file)
{
  //  Initialize distance_table to 999
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt3.costs[i][j] = 999;
    }
  }

  char *line = NULL;
  size_t len = 0;

  // Read file
  getline(&line, &len, file);
  sscanf(line, "%d %d %d %d", &dt3.costs[0][0], &dt3.costs[1][1], &dt3.costs[2][2], &dt3.costs[3][3]);

}

extern void rtinit3()
{
	int i;
	struct rtpkt send;
      	send.sourceid = 3;
      	default3.sourceid = 3;
      
	for(i = 0; i < 4; i++){
        	send.mincost[i] = dt3.costs[i][i];
          	default3.mincost[i] = dt3.costs[i][i];
          	if(i == 0 || i == 2)neighbor3[i] = 1;
      	}
      
	for(i = 0; i < 4; i++) {
        	if(neighbor3[i]) {
        		send.destid = i;
        		tolayer2(send);
		}
  	}

}

extern void rtupdate3(struct rtpkt *rcvdpkt)
{
	int src = rcvdpkt->sourceid;
      	int distance = dt3.costs[src][src];
     	int i, j;
	int min_cost;
	
	if(distance == 999) return;
      	
	for(i = 0; i < 4; i++){
        	if(dt3.costs[i][src] != rcvdpkt->mincost[i] + distance){
              		dt3.costs[i][src] = rcvdpkt->mincost[i] + distance;
              		min_cost = dt3.costs[i][i];
              
			for(j = 0;j < 4; j++) {
            			min_cost = min_cost > dt3.costs[i][j] ? dt3.costs[i][j] : min_cost;
              		}
              		
			default3.mincost[i] = min_cost;
              		
			for(j = 0; j < 4; j++) {
                		if(neighbor3[j]) {
                			default3.destid = j;
                			tolayer2(default3);
				}
              		}
      		}
  	}
}

void printdt3(void)
{
  struct distance_table *dtptr = &dt3;

  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}

extern void print_min_cost3()
{

  int min_cost[4];

  for (int i = 0; i < 4; i++)
  {
    int min = dt3.costs[i][i];
    for (int j = 0; j < 4; j++)
    {
      min = min > dt3.costs[i][j] ? dt3.costs[i][j] : min;
    }

    min_cost[i] = min;
  }

  printf("Min cost %d : %d %d %d %d\n", 3, min_cost[0], min_cost[1],
         min_cost[2], min_cost[3]);
}

