from collections import deque

class Graph:
    def __init__(self, adjacency_list):
        self.adjacency_list = adjacency_list

    def a_star_search(self, start, finish):
        # Initialize data structures
        open_set = deque([start])
        came_from = {}
        g_score = {node: float('inf') for node in self.adjacency_list}
        g_score[start] = 0

        while open_set:
            current_node = open_set.popleft()

            if current_node == finish:
                # Reconstruct the path
                path = []
                while current_node in came_from:
                    path.append(current_node)
                    current_node = came_from[current_node]
                path.append(start)
                path.reverse()
                return path

            for neighbor, cost in self.adjacency_list[current_node]:
                tentative_g_score = g_score[current_node] + cost
                if tentative_g_score < g_score[neighbor]:
                    g_score[neighbor] = tentative_g_score
                    came_from[neighbor] = current_node
                    open_set.append(neighbor)

        return None  # No path found

# Example -> (will likely require modifications to add it to the pipeline) 
adjacency_list = {
    'A': [('B', 1), ('C', 3), ('D', 7)],
    'B': [('D', 5)],
    'C': [('D', 12)]
    # List of nodes ^ (will likely require modifications to add it to the pipeline)
}

graph = Graph(adjacency_list)
start_node = 'A'
finish_node = 'D'
result_path = graph.a_star_search(start_node, finish_node)
print("Optimal path:", result_path)
