#define XTSSIZE 60
struct xts_tab
{
    int xts_quantum; // new time slice
    int xts_tqexp;   // new priority: CPU-intensive (time quantum expired)
    int xts_slpret;  // new priority: I/O-intensive (sleep return)
};
extern struct xts_tab xts_conf[];

struct xts_multifb
{
    int status;       // binary flag: 0 if queue is empty, 1 otherwise
    qid16 queue_head; // index to head of queue
    qid16 queue_tail; // index to tail of queue
};
extern struct xts_multifb xts_ready[];

extern qid16 xts_arr[];
