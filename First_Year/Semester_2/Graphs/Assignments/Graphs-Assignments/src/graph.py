from copy import deepcopy
from collections import deque
import math


class Graph:
    def __init__(self, number_of_vertices, number_of_edges):
        self.__number_of_vertices = number_of_vertices
        self.__number_of_edges = number_of_edges

        self.__incoming_edges = {}
        self.__outgoing_edges = {}
        self.__costs = {}

        for index in range(number_of_vertices):
            self.__incoming_edges[index] = []
            self.__outgoing_edges[index] = []

    @property
    def number_of_vertices(self):
        return self.__number_of_vertices

    @property
    def number_of_edges(self):
        return self.__number_of_edges

    @property
    def incoming_edges(self):
        return self.__incoming_edges

    @property
    def outgoing_edges(self):
        return self.__outgoing_edges

    @property
    def costs(self):
        return self.__costs

    def set_number_of_vertices(self, number_of_vertices):
        self.__number_of_vertices = number_of_vertices

    def set_number_of_edges(self, number_of_edges):
        self.__number_of_edges = number_of_edges

    def set_incoming_edges(self, incoming_edges):
        self.__incoming_edges = incoming_edges

    def set_outgoing_edges(self, outgoing_edges):
        self.__outgoing_edges = outgoing_edges

    def set_costs(self, costs):
        self.__costs = costs

    def parse_vertices(self):
        """
        Time Complexity - Theta(nr_of_vertices)
        :return: an iterator in the list of vertices
        """
        vertices = list(self.__outgoing_edges.keys())
        for v in vertices:
            yield v

    def parse_inbound_edges(self, vertex):
        """
        Time Complexity - Theta(nr_of_incoming_edges)
        :param vertex: the vertex for which we parse the incoming edges
        :return: an iterator in the dict of inbound edges
        """
        for y in self.__incoming_edges[vertex]:
            yield y

    def parse_outbound_edges(self, vertex):
        """
        Time Complexity - Theta(nr_of_outcoming_edges)
        :param vertex: the vertex for which we parse the outcoming edges
        :return: an iterator in the dict of outbound edges
        """
        for y in self.__outgoing_edges[vertex]:
            yield y

    def parse_cost(self):
        """
        Time Complexity - Theta(nr_of_edges)
        :return: an iterator in the list containing the costs of the edges
        """
        keys = list(self.__costs.keys())
        for key in keys:
            yield key

    def add_vertex(self, vertex):
        """
        Time Complexity - Theta(1)
        :param vertex: the vertex that we want to add
        :return: True if a new vertex was added, False otherwise
        """
        if vertex in self.__outgoing_edges.keys() and vertex in self.__incoming_edges.keys():
            return False
        self.__outgoing_edges[vertex] = []
        self.__incoming_edges[vertex] = []
        self.__number_of_vertices += 1
        return True

    def remove_vertex(self, vertex):
        """
        Time Complexity - Theta(nr_of_incoming_edges + nr_of_outgoing_edges)
        :param vertex: the vertex that we want to delete
        :return: True if the vertex was deleted, False otherwise
        """
        if vertex not in self.__outgoing_edges.keys() and vertex not in self.__incoming_edges.keys():
            return False

        for v in list(self.__outgoing_edges.keys()):
            if vertex in self.__outgoing_edges[v]:
                self.__outgoing_edges[v].remove(vertex)
        for v in list(self.__incoming_edges.keys()):
            if vertex in self.__incoming_edges[v]:
                self.__incoming_edges[v].remove(vertex)

        self.__outgoing_edges.pop(vertex, None)
        self.__incoming_edges.pop(vertex, None)

        for key in list(self.__costs.keys()):
            if key[0] == vertex or key[1] == vertex:
                self.__costs.pop(key)
                self.__number_of_edges -= 1

        self.__number_of_vertices -= 1
        return True

    def add_edge(self, x, y, cost):
        """
        Time Complexity - Theta(1)
        - the time complexity of accessing an element in a dict is Theta(1)
        - the time complexity of appending/adding a new element in a list in Theta(1)
        :param x: starting vertex of an edge
        :param y: final vertex of an edge
        :param cost: the cost of the edge
        :return: True if the edge was added, False otherwise
        """
        if x not in self.__outgoing_edges.keys() or y not in self.__outgoing_edges.keys() or (x, y) in self.__costs.keys():
            return False
        self.__outgoing_edges[x].append(y)
        self.__incoming_edges[y].append(x)
        self.__costs[(x, y)] = cost
        self.__number_of_edges += 1
        return True

    def remove_edge(self, x, y):
        """
        Time Complexity - Theta(1)
        :param x: starting vertex of an edge
        :param y: final vertex of an edge
        :return: True if the edge was deleted, False otherwise
        """
        if x not in self.__outgoing_edges.keys() or y not in self.__outgoing_edges.keys() or (x, y) not in self.__costs.keys():
            return False
        self.__outgoing_edges[x].remove(y)
        self.__incoming_edges[y].remove(x)
        self.__costs.pop((x, y))
        self.__number_of_edges -= 1
        return True

    def in_degree(self, vertex):
        """
        Time Complexity - Theta(1)
        :param vertex: the vertex for which we compute the number of incoming edges
        :return: the number of the incoming edges for that vertex, if it is an existent vertex in the graph, -1 otherwise
        """
        if vertex not in self.__incoming_edges.keys():
            return -1
        return len(self.__incoming_edges[vertex])

    def out_degree(self, vertex):
        """
        Time Complexity - Theta(1)
        :param vertex: the vertex for which we compute the number of outgoing edges
        :return: the number of the outgoing edges for that vertex, if it is an existent vertex in the graph, -1 otherwise
        """
        if vertex not in self.__outgoing_edges.keys():
            return -1
        return len(self.__outgoing_edges[vertex])

    def find_if_edge(self, x, y):
        """
        Time Complexity - Theta(1)
        :param x: starting vertex of an edge
        :param y: final vertex of an edge
        :return: True if the edge is in the graph, False otherwise
        """
        if x in self.__incoming_edges[y]:
            return self.__costs[(x, y)]
        if y in self.__outgoing_edges[x]:
            return self.__costs[(x, y)]
        return False

    def change_cost(self, x, y, new_cost):
        """
        Time Complexity - Theta(1)
        :param x: starting vertex of an edge
        :param y: final vertex of an edge
        :param new_cost: the new cost of the given edge
        :return: True if the cost of the edge was changed, False otherwise
        """
        if (x, y) not in self.__costs.keys():
            return False
        self.__costs[(x, y)] = new_cost
        return True

    def copy_graph(self):
        return deepcopy(self)

    def bfs(self, start_vertex, goal_vertex):
        """
        Time Complexity - O(nr_of_vertices)
        A function that searches for the path between two given vertices and returns it if it exists.
        :param start_vertex: The starting vertex
        :param goal_vertex: The vertex we want to reach
        :return: The path between the two vertices or None if there is no such path
        """
        queue = deque([start_vertex])
        parent = {start_vertex: None}

        while queue:
            current_vertex = queue.popleft()
            if current_vertex == goal_vertex:
                path = []
                while current_vertex is not None:
                    path.append(current_vertex)
                    current_vertex = parent[current_vertex]
                return path[::-1]

            for neighbor in self.__outgoing_edges.get(current_vertex, []):
                if neighbor not in parent:
                    queue.append(neighbor)
                    parent[neighbor] = current_vertex
        return None

    def bellman_ford(self, start_vertex):
        """
        Time Complexity: O(number_of_vertices * number_of_edges)
        Bellman-Ford algorithm extended to find the shortest path from a source vertex to all other vertices in the graph,
        track the path, and detect negative weight cycles that are reachable from the source.
        :param start_vertex: The source vertex
        :return: Tuple containing three elements:
                 - A matrix of distances from the source to each vertex.
                 - A matrix with the path from the source to each vertex.
                 - A boolean indicating whether a negative cycle was detected.
        """
        # Initialize distances and predecessors
        distance = [[float('inf')] * (self.__number_of_vertices + 1) for _ in range(self.__number_of_vertices)]
        predecessor = [[-1] * (self.__number_of_vertices + 1) for _ in range(self.__number_of_vertices)]
        distance[start_vertex][0] = 0

        for k in range(1, self.__number_of_vertices + 1):
            for v in range(self.__number_of_vertices):
                distance[v][k] = distance[v][k - 1]
                predecessor[v][k] = predecessor[v][k - 1]

            for u, v in self.parse_cost():
                if distance[u][k - 1] + self.costs[(u, v)] < distance[v][k]:
                    distance[v][k] = distance[u][k - 1] + self.costs[(u, v)]
                    predecessor[v][k] = u

        # Check for negative weight cycles
        for v in range(self.__number_of_vertices):
            if distance[v][self.__number_of_vertices - 1] < distance[v][self.__number_of_vertices]:
                return distance, predecessor, True

        return distance, predecessor, False

    def topological_sort(self):
        """
        Time Complexity: O(number_of_vertices + number_of_edges)
        A function that performs a topological sort on the graph, determining in this way if it is a DAG.
        :return: A list containing a topological order for the graph or None if the graph is not a DAG
        """
        in_degree = {i: 0 for i in range(self.__number_of_vertices)}
        for v in self.parse_vertices():
            for neighbor in self.parse_outbound_edges(v):
                in_degree[neighbor] += 1

        # Queue for vertices with no incoming edges
        queue = deque([v for v in in_degree if in_degree[v] == 0])
        top_order = []

        while queue:
            vertex = queue.popleft()
            top_order.append(vertex)
            for neighbor in self.parse_outbound_edges(vertex):
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

        # This means there was a cycle, which shouldn't happen in a DAG
        if len(top_order) != self.__number_of_vertices:
            return None
        return top_order

    def is_dag(self):
        """
        A function that checks if the graph is a DAG.
        :return: True if the graph is a DAG, False otherwise
        """
        return self.topological_sort() is not None

    def find_highest_cost_path(self, start, end):
        """
        Time Complexity: O(number_of_vertices + number_of_edges)
        A function that finds a highest cost path between two given vertices in a DAG.
        :param start: The starting vertex
        :param end: The vertex we want to reach
        :return: The highest cost of a path and a path having that cost
        """
        top_order = self.topological_sort()
        if top_order is None:
            return 0, []

        distances = {vertex: float('-inf') for vertex in self.parse_vertices()}
        distances[start] = 0
        predecessor = {vertex: None for vertex in self.parse_vertices()}

        for vertex in top_order:
            if distances[vertex] != float('-inf'):
                for neighbor in self.parse_outbound_edges(vertex):
                    edge_cost = self.__costs[(vertex, neighbor)]
                    new_cost = distances[vertex] + edge_cost
                    if new_cost > distances[neighbor]:
                        distances[neighbor] = new_cost
                        predecessor[neighbor] = vertex

        if distances[end] == float('-inf'):
            return 0, []

        path = []
        current_vertex = end
        while current_vertex is not None:
            path.append(current_vertex)
            current_vertex = predecessor[current_vertex]
        path.reverse()
        return distances[end], path

    def count_paths(self, start, end):
        """
        Time Complexity: O(number_of_vertices + number_of_edges)
        A function that counts the number of paths between two given vertices in a DAG.
        :param start: The starting vertex
        :param end: The vertex we want to reach
        :return: The number of paths
        """
        top_order = self.topological_sort()
        if top_order is None:
            return 0

        path_count = [0] * self.__number_of_vertices
        path_count[start] = 1

        for vertex in top_order:
            if path_count[vertex] > 0:
                for neighbor in self.parse_outbound_edges(vertex):
                    path_count[neighbor] += path_count[vertex]

        return path_count[end]

    def find_lowest_cost_paths(self, start, end):
        """
        Time Complexity: O(number_of_vertices + number_of_edges)
        A function that finds the number of distinct lowest cost paths between two given vertices in a DAG
        :param start: The starting vertex
        :param end: The vertex we want to reach
        :return: The lowest cost of a path and the number of distinct paths having that cost
        """
        top_order = self.topological_sort()
        if top_order is None:
            return 0, 0

        distances = {vertex: float('inf') for vertex in self.parse_vertices()}
        path_count = {vertex: 0 for vertex in self.parse_vertices()}
        distances[start] = 0
        path_count[start] = 1

        for vertex in top_order:
            for neighbor in self.parse_outbound_edges(vertex):
                edge_cost = self.__costs[(vertex, neighbor)]
                new_cost = distances[vertex] + edge_cost
                if new_cost < distances[neighbor]:
                    distances[neighbor] = new_cost
                    path_count[neighbor] = path_count[vertex]
                elif new_cost == distances[neighbor]:
                    path_count[neighbor] += path_count[vertex]

        return distances[end], path_count[end]
