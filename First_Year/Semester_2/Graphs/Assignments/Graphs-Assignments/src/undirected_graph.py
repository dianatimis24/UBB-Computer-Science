from copy import deepcopy
import heapq


class UndirectedGraph:
    def __init__(self, number_of_vertices, number_of_edges):
        self.__number_of_vertices = number_of_vertices
        self.__number_of_edges = number_of_edges

        self.__neighbors = {}
        self.__costs = {}

        for index in range(number_of_vertices):
            self.__neighbors[index] = []

    @property
    def number_of_vertices(self):
        return self.__number_of_vertices

    @property
    def number_of_edges(self):
        return self.__number_of_edges

    @property
    def neighbors(self):
        return self.__neighbors

    @property
    def costs(self):
        return self.__costs

    def set_number_of_vertices(self, number_of_vertices):
        self.__number_of_vertices = number_of_vertices

    def set_number_of_edges(self, number_of_edges):
        self.__number_of_edges = number_of_edges

    def set_incoming_edges(self, neighbors):
        self.__neighbors = neighbors

    def set_costs(self, costs):
        self.__costs = costs

    def parse_vertices(self):
        """
        Time Complexity - Theta(nr_of_vertices)
        :return: an iterator in the list of vertices
        """
        vertices = list(self.__neighbors.keys())
        for v in vertices:
            yield v

    def parse_neighbors(self, vertex):
        """
        Time Complexity - Theta(nr_of_incoming_edges)
        :param vertex: the vertex for which we parse the neighbors
        :return: an iterator in the dict of neighbors
        """
        for y in self.__neighbors[vertex]:
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
        if vertex in self.__neighbors.keys():
            return False
        self.__neighbors[vertex] = []
        self.__number_of_vertices += 1
        return True

    def remove_vertex(self, vertex):
        """
        Time Complexity - Theta(nr_of_incoming_edges + nr_of_outgoing_edges)
        :param vertex: the vertex that we want to delete
        :return: True if the vertex was deleted, False otherwise
        """
        if vertex not in self.__neighbors.keys():
            return False

        for v in list(self.__neighbors.keys()):
            if vertex in self.__neighbors[v]:
                self.__neighbors[v].remove(vertex)

        self.__neighbors.pop(vertex, None)

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
        if x == y or self.find_if_edge(x, y):
            return False
        self.__neighbors[x].append(y)
        self.__neighbors[y].append(x)
        self.__costs[(x, y)] = cost
        self.__costs[(y, x)] = cost
        self.__number_of_edges += 1
        return True

    def remove_edge(self, x, y):
        """
        Time Complexity - Theta(1)
        :param x: starting vertex of an edge
        :param y: final vertex of an edge
        :return: True if the edge was deleted, False otherwise
        """
        if x == y or not self.find_if_edge(x, y):
            return False
        self.__neighbors[x].remove(y)
        self.__neighbors[y].remove(x)
        self.__costs.pop((x, y))
        self.__costs.pop((y, x))
        self.__number_of_edges -= 1
        return True

    def degree(self, vertex):
        """
        Time Complexity - Theta(1)
        :param vertex: the vertex for which we compute the number of neighbors
        :return: the number of neighbors for that vertex, if it is an existent vertex in the graph, -1 otherwise
        """
        if vertex not in self.__neighbors.keys():
            return -1
        return len(self.__neighbors[vertex])

    def find_if_edge(self, x, y):
        """
        Time Complexity - Theta(1)
        :param x: starting vertex of an edge
        :param y: final vertex of an edge
        :return: True if the edge is in the graph, False otherwise
        """
        return y in self.__neighbors[x]

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

    def dfs_preorder(self, node, mst_edges, visited_dfs, result):
        """
        Time Complexity: O(n)
        A function that performs depth-first search (DFS) in a given Minimum Spanning Tree (MST), from a given
        starting node and stores the preorder traversal of the tree.
        :param node: the current node from which the DFS starts
        :param mst_edges: a dictionary representing the edges of Minimum Spanning Tree (MST)
        :param visited_dfs: a list of visited nodes in the MST
        :param result: a list that collects the node in the DFS traversal order
        :return: None
        """
        visited_dfs.add(node)
        result.append(node)
        for neighbor in mst_edges[node]:
            if neighbor not in visited_dfs:
                self.dfs_preorder(neighbor, mst_edges, visited_dfs, result)

    def hamiltonian_cycle_of_no_more_than_twice_the_minimum_cost(self):
        """
        Time complexity: O(m + n * log n)
        A function that returns a list representing a Hamiltonian cycle of no more than twice the minimum cost,
        using a 2-approximation algorithm (MST (with Prim's Algorithm) + DFS + shortcutting).
        :return:a list of vertices representing a Hamiltonian cycle of no more than twice the minimum cost
        """
        # Building MST using Prim's Algorithm. Time Complexity: O(m + n * log n)
        start = 0
        visited = set()
        mst_edges = {v: [] for v in self.parse_vertices()}
        min_heap = [(0, start, -1)]  # (cost, current_vertex, parent)

        total_vertices = self.__number_of_vertices
        added = 0

        while min_heap and added < total_vertices:
            cost, u, parent = heapq.heappop(min_heap)
            if u in visited:
                continue
            visited.add(u)
            added += 1
            if parent != -1:
                mst_edges[parent].append(u)
                mst_edges[u].append(parent)

            for v in self.parse_neighbors(u):
                if v not in visited:
                    heapq.heappush(min_heap, (self.__costs[(u, v)], v, u))

        # Performing DFS to get preorder traversal. Time Complexity: O(n)
        preorder = []
        self.dfs_preorder(start, mst_edges, set(), preorder)

        # Shortcutting the tour. Time Complexity: O(n)
        seen = set()
        tour = []
        for node in preorder:
            if node not in seen:
                seen.add(node)
                tour.append(node)
        if self.find_if_edge(start, tour[-1]):
            tour.append(start)  # close the cycle
            return tour
        else:
            return []
