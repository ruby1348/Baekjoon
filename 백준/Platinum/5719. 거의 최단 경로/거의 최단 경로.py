import heapq
import sys

INF = sys.maxsize

def dijkstra_path(n, m, start, end, graph) :
    distance = [INF] * n
    prev = [[] for _ in range(n)]
    distance[start] = 0

    pq = []
    heapq.heappush(pq, (0, start))

    while pq :
        dist, vert = heapq.heappop(pq)

        # 최단 거리가 아니면 무시
        if dist > distance[vert] :
            continue

        for graph_vert, graph_dist in graph[vert] :
            new_dist = dist + graph_dist
            if new_dist < distance[graph_vert] :
                distance[graph_vert] = new_dist
                prev[graph_vert] = [vert]
                heapq.heappush(pq, (new_dist, graph_vert))
            elif new_dist == distance[graph_vert] :
                prev[graph_vert].append(vert)

    return distance, prev

def dijkstra(n, m, start, end) :
    graph = [[] for _ in range(n)]

    # 그래프 입력
    for i in range(m) :
        a, b, c = map(int, sys.stdin.readline().split())
        graph[a].append([b, c]) #first 목적지, second 거리

    distance, prev = dijkstra_path(n, m, start, end, graph)
    shortestDistance = distance[end] #최단 거리

    if shortestDistance == INF :
        return -1

    # 최단 경로 간선들 제거
    queue = [end]
    visited = [False] * n

    while queue:
        current = queue.pop(0)
        if visited[current]:
            continue
        visited[current] = True

        for parent in prev[current] :
            for j in graph[parent] :
                if j[0] == current :
                    j[1] = INF
                    break
            queue.append(parent)
            
    distance, _ = dijkstra_path(n, m, start, end, graph)
    result = distance[end]
    if result == INF : return -1
    else : return result

while 1 :
    n, m = map(int, sys.stdin.readline().split())
    if n == 0 and m == 0 : break
    start, end = map(int, sys.stdin.readline().split())
    result = dijkstra(n, m, start, end)
    sys.stdout.write(str(result) + "\n")