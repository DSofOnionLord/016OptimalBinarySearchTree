1) 오름차순으로 정열된 n개의 정수로 구성된 optimal binary search tree를 구성하시오. 
	%cat input.txt
	 4   16				// n = 4, m = 16
	10   15   20   25		// 오름차순으로 정렬된 n개의 정수
	 3    3    1    1		// p0= 3/m, p1= 3/m, p2= 1/m, p3= 1/m
  2    3    1    1    1		// q0= 2/m, q1= 3/m, q2= 1/m, q3= 1/m


%cat output.txt
OBST의 cost는 2입니다. 		// 32/m = 32/16 = 2	

CBT 1번 노드 = 15
CBT 2번 노드 = 10
CBT 3번 노드 = 20
CBT 7번 노드 = 25


