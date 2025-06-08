#include <stdio.h>

struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };
int neighbor2[4] = {0};
struct rtpkt default2;
extern int TRACE;
extern int YES;
extern int NO;
extern void tolayer2(struct rtpkt packet);

struct distance_table
{
  int costs[4][4];
} dt2;


extern void read2(FILE *file)
{
  //  Initialize distance_table to 999
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt2.costs[i][j] = 999;
    }
  }

  char *line = NULL;
  size_t len = 0;

  // Read file
  getline(&line, &len, file);
  sscanf(line, "%d %d %d %d", &dt2.costs[0][0], &dt2.costs[1][1], &dt2.costs[2][2], &dt2.costs[3][3]);

}

extern void rtinit2()
{
	int i;
	struct rtpkt send;
      	send.sourceid = 2;
      	default2.sourceid = 2;
      	
	for(i = 0; i < 4; i++){
        	send.mincost[i] = dt2.costs[i][i];
          	default2.mincost[i] = dt2.costs[i][i];
          	if(i != 2)neighbor2[i] = 1;
      	}
      
	for(i = 0; i < 4; i++) {
        	if(neighbor2[i]) {
        		send.destid = i;
        		tolayer2(send);
		}
  	}
}

extern void rtupdate2(struct rtpkt *rcvdpkt)
{
	int src = rcvdpkt->sourceid;
      	int distance = dt2.costs[src][src];
     	int i, j;
	int min_cost;

	if(distance == 999) return;
      	for(i = 0; i < 4; i++){
        	if(dt2.costs[i][src] != rcvdpkt->mincost[i] + distance){
              		dt2.costs[i][src] = rcvdpkt->mincost[i] + distance;
              		min_cost = dt2.costs[i][i];
              		
			for(j = 0;j < 4; j++) {
            			min_cost = min_cost > dt2.costs[i][j] ? dt2.costs[i][j] : min_cost;
              		}
              		
			default2.mincost[i] = min_cost;
              		
			for(j = 0; j < 4; j++) {
                		if(neighbor2[j]) {
                			default2.destid = j;
                			tolayer2(default2);
				}
              		}
      		}
  	}
}

void printdt2(void)
{
  struct distance_table *dtptr = &dt2;

  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
     dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
     dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
     dtptr->costs[3][1],dtptr->costs[3][3]);
}

extern void print_min_cost2()
{

  int min_cost[4];

  for (int i = 0; i < 4; i++)
  {
    int min = dt2.costs[i][i];
    for (int j = 0; j < 4; j++)
    {
      min = min > dt2.costs[i][j] ? dt2.costs[i][j] : min;
    }

    min_cost[i] = min;
  }

  printf("Min cost %d : %d %d %d %d\n", 2, min_cost[0], min_cost[1],
         min_cost[2], min_cost[3]);
}

