#include <stdio.h>

struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };


extern int TRACE;
extern int YES;
extern int NO;
extern void tolayer2(struct rtpkt packet);

struct distance_table 
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */


extern void read1(FILE *file)
{

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt1.costs[i][j] = 999;
    }
  }

  char *line = NULL;
  size_t len = 0;

  // Read file
  getline(&line, &len, file);
  sscanf(line, "%d %d %d %d", &dt1.costs[0][0], &dt1.costs[1][1], &dt1.costs[2][2], &dt1.costs[3][3]);
}

extern void rtinit1()
{
  /* TODO */
}

extern void rtupdate1(struct rtpkt *rcvdpkt)
{
  /* TODO */
}

void printdt1(void)  
{
  struct distance_table *dtptr = &dt1;

  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}

extern void linkhandler1(int linkid, int newcost)
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
{
  int old_value[4];

  for (int i = 0; i < 4; i++)
  {
    old_value[i] = dt1.costs[i][linkid] - dt1.costs[linkid][linkid];
  }

  // change node 1
  dt1.costs[linkid][linkid] = newcost;

  for (int i = 0; i < 4; i++)
  {
    dt1.costs[i][linkid] = old_value[i] + newcost;
  }

  for (int i = 0; i < 4; i++)
  {
    if (i != 3 && i != 1)
    {
      struct rtpkt r;
      r.sourceid = 1;
      r.destid = i;
      for (int j = 0; j < 4; j++)
      {
        int min = dt1.costs[j][j];
        for (int k = 0; k < 4; k++)
        {
          if (k != i)
          {
            min = min > dt1.costs[j][k] ? dt1.costs[j][k] : min;
          }
        }
        r.mincost[j] = min;
      }

      tolayer2(r);
    }
  }

  // printdt1();
}

extern void print_min_cost1()
{

  int min_cost[4];

  for (int i = 0; i < 4; i++)
  {
    int min = dt1.costs[i][i];
    for (int j = 0; j < 4; j++)
    {
      min = min > dt1.costs[i][j] ? dt1.costs[i][j] : min;
    }

    min_cost[i] = min;
  }

  printf("Min cost %d : %d %d %d %d\n", 1, min_cost[0], min_cost[1],
         min_cost[2], min_cost[3]);
}