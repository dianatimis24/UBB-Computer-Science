from src.graph import Graph
from src.undirected_graph import UndirectedGraph
from random import randint


def generate_random_graph(vertices, edges):
    """
    A function that generates a random graph.
    :param vertices: number of wanted vertices
    :param edges: number of wanted edges
    :return: the newly created graph
    """
    graph = Graph(vertices, 0)
    i = 0
    while i < edges:
        x = randint(0, vertices - 1)
        y = randint(0, vertices - 1)
        cost = randint(0, 500)
        if graph.add_edge(x, y, cost):
            i += 1
    return graph


def read_graph_from_file(filename):
    """
    A function that reads a graph from a file.
    :param filename: the name of the file from which we write the graph
    :return: None
    """
    file = open(filename, "r")
    line = file.readline()
    line = line.strip()
    vertices, edges = line.split(' ')
    graph = Graph(int(vertices), int(edges))
    line = file.readline().strip()
    while len(line) > 0:
        line = line.split(' ')
        if len(line) == 1:
            graph.incoming_edges[int(line[0])] = []
            graph.outgoing_edges[int(line[0])] = []
        elif len(line) == 3:
            graph.incoming_edges[int(line[1])].append(int(line[0]))
            graph.outgoing_edges[int(line[0])].append(int(line[1]))
            graph.costs[(int(line[0]), int(line[1]))] = int(line[2])
        line = file.readline().strip()
    file.close()
    return graph


def read_undirected_graph_from_file(filename):
    """
    A function that reads an undirected graph from a file.
    :param filename: the name of the file from which we write the graph
    :return: None
    """
    file = open(filename, "r")
    line = file.readline()
    line = line.strip()
    vertices, edges = line.split(' ')
    undirected_graph = UndirectedGraph(int(vertices), int(edges))
    line = file.readline().strip()
    while len(line) > 0:
        line = line.split(' ')
        if len(line) == 1:
            undirected_graph.neighbors[int(line[0])] = []
        elif len(line) == 3:
            undirected_graph.neighbors[int(line[0])].append(int(line[1]))
            undirected_graph.neighbors[int(line[1])].append(int(line[0]))
            undirected_graph.costs[(int(line[0]), int(line[1]))] = int(line[2])
        line = file.readline().strip()
    file.close()
    return undirected_graph


def write_graph_to_file(graph, filename):
    """
    A function that writes a graph to a file.
    :param graph: the given graph
    :param filename: the name of the file in which we write the graph
    :return: None
    """
    file = open(filename, "w")
    if graph.number_of_edges and graph.number_of_vertices:
        file.write(str(graph.number_of_vertices) + " " + str(graph.number_of_edges) + "\n")
        if len(graph.costs) == 0 and len(graph.incoming_edges) == 0 and len(graph.outgoing_edges) == 0:
            raise ValueError("Graph is empty")
        for key in graph.costs.keys():
            file.write(str(key[0]) + " " + str(key[1]) + " " + str(graph.costs[key]) + "\n")
    else:
        first_line = "We cannot create this graph." + "\n"
        file.write(first_line)
    file.close()


class UI:
    def __init__(self):
        self.__graphs = []
        self.__current = None

    def switch_graph_ui(self):
        """
        A function that switches the current graph.
        :return: None
        """
        print("You are on the graph number: {}".format(self.__current))
        print("Available graphs: from 0 - {}".format(str(len(self.__graphs) - 1)))
        number = int(input("Enter the graph number you want to switch to: "))
        if not 0 <= number < len(self.__graphs):
            raise ValueError("Trying to switch to a non existing graph!")
        self.__current = number

    def add_empty_graph(self):
        """
        A function that adds an empty graph.
        :return: None
        """
        if self.__current is None:
            self.__current = 0
        graph = Graph(0, 0)
        self.__graphs.append(graph)
        self.__current = len(self.__graphs) - 1

    def create_random_graph_ui(self):
        """
        A function that creates a random graph with a given number of vertices and edges or
        returns a message if the given number of edges is too bigger.
        :return: None
        """
        vertices = int(input("Enter the number of vertices: "))
        edges = int(input("Enter the number of edges: "))
        if edges > vertices * vertices:
            print("Too many edges!")
        else:
            graph = generate_random_graph(vertices, edges)
            if self.__current is None:
                self.__current = 0
            self.__graphs.append(graph)
            self.__current = len(self.__graphs) - 1

    def get_number_of_vertices_ui(self):
        """
        A function that prints the number of vertices of the current graph.
        :return: None
        """
        print("The number of vertices is: {}.".format(self.__graphs[self.__current].number_of_vertices))

    def get_number_of_edges_ui(self):
        """
        A function that prints the number of edges of the current graph.
        :return: None
        """
        print("The number of edges is: {}.".format(self.__graphs[self.__current].number_of_edges))

    def list_all_outgoing(self):
        """
        A function that lists all the outgoing edges of the current graph.
        :return: None
        """
        for x in self.__graphs[self.__current].parse_vertices():
            line = str(x) + " :"
            for y in self.__graphs[self.__current].parse_outbound_edges(x):
                line = line + " " + str(y)
            print(line)

    def list_outgoing(self):
        """
        A function that lists the outgoing edges of a given vertex from the current graph.
        :return: None
        """
        vertex = int(input("Enter the vertex: "))
        if vertex not in self.__graphs[self.__current].parse_vertices():
            raise ValueError("Cannot list outgoing edges of this vertex, because it does not exist!")
        else:
            line = str(vertex) + " :"
            for y in self.__graphs[self.__current].parse_outbound_edges(vertex):
                line = line + " " + "({}, {})".format(str(vertex), str(y))
            print(line)

    def list_all_incoming(self):
        """
        A function that lists all the incoming edges of the current graph.
        :return: None
        """
        for x in self.__graphs[self.__current].parse_vertices():
            line = str(x) + " :"
            for y in self.__graphs[self.__current].parse_inbound_edges(x):
                line = line + " " + str(y)
            print(line)

    def list_incoming(self):
        """
        A function that lists the incoming edges of a given vertex from the current graph.
        :return: None
        """
        vertex = int(input("Enter the vertex: "))
        if vertex not in self.__graphs[self.__current].parse_vertices():
            raise ValueError("Cannot list inbound of this vertex, it does not exist!")
        else:
            line = str(vertex) + " :"
            for y in self.__graphs[self.__current].parse_inbound_edges(vertex):
                line = line + " " + "({}, {})".format(str(y), str(vertex))
            print(line)

    def list_all_costs(self):
        """
        A function that lists all the edges and their costs from the current graph.
        :return: None
        """
        for key in self.__graphs[self.__current].parse_cost():
            line = "({}, {})".format(key[0], key[1]) + " :" + str(self.__graphs[self.__current].costs[key])
            print(line)

    def parse_all_vertices(self):
        """
        A function that parses all the vertices of the current graph.
        :return: None
        """
        for vertex in self.__graphs[self.__current].parse_vertices():
            print("{}".format(vertex))

    def add_vertex_ui(self):
        """
        A function that adds a vertex to the current graph and prints a message if the vertex was added or not.
        :return: None
        """
        vertex = int(input("Enter the new vertex: "))
        added = self.__graphs[self.__current].add_vertex(vertex)
        if added:
            print("Vertex added successfully!")
        else:
            print("Cannot add this vertex, because it already exists!")

    def delete_vertex_ui(self):
        """
        A function that deletes a vertex from the current graph and prints a message if the vertex was deleted or not.
        :return: None
        """
        vertex = int(input("Enter the vertex to be deleted: "))
        deleted = self.__graphs[self.__current].remove_vertex(vertex)
        if deleted:
            print("Vertex deleted successfully!")
        else:
            print("Cannot delete this vertex, because it does not exist!")

    def add_edge_ui(self):
        """
        A function that adds an edge to the current graph and prints a message if the edge was added or not.
        :return: None
        """
        print("Add an edge (an edge is (x, y))")
        vertex_x = int(input("Enter x = "))
        vertex_y = int(input("Enter y = "))
        cost = int(input("Enter the cost of the edge: "))
        added = self.__graphs[self.__current].add_edge(vertex_x, vertex_y, cost)
        if added:
            print("Edge added successfully!")
        else:
            print("Cannot add this edge, because it already exists!")

    def remove_edge_ui(self):
        """
        A function that deletes an edge from the current graph and prints a message if the edge was deleted or not.
        :return: None
        """
        print("Remove an edge (an edge is (x, y))")
        vertex_x = int(input("Enter x = "))
        vertex_y = int(input("Enter y = "))
        deleted = self.__graphs[self.__current].remove_edge(vertex_x, vertex_y)
        if deleted:
            print("Edge deleted successfully!")
        else:
            print("Cannot remove this edge, because it does not exist!")

    def modify_cost_ui(self):
        """
        A function that modifies the cost of a given edge in the current graph and prints a message if the cost was modified or not.
        :return: None
        """
        print("Modify the cost of an edge (an edge is (x, y))")
        vertex_x = int(input("Enter x = "))
        vertex_y = int(input("Enter y = "))
        cost = int(input("Enter the cost of the edge: "))
        changed = self.__graphs[self.__current].change_cost(vertex_x, vertex_y, cost)
        if changed:
            print("Cost modified successfully!")
        else:
            print("Cannot modify the cost, because the edge does not exist!")

    def get_in_degree_ui(self):
        """
        A function that gets the in degree of a given vertex from the current graph and prints a message with the in degree of the vertex.
        :return: None
        """
        vertex = int(input("Enter the vertex: "))
        degree = self.__graphs[self.__current].in_degree(vertex)
        if degree == -1:
            print("The vertex does not exist!")
        else:
            print("The in degree of the vertex {} is {}.".format(vertex, degree))

    def get_out_degree_ui(self):
        """
        A function that gets the out degree of a given vertex from the current graph and prints a message with the out degree of the vertex.
        :return: None
        """
        vertex = int(input("Enter the vertex: "))
        degree = self.__graphs[self.__current].out_degree(vertex)
        if degree == -1:
            print("The vertex does not exist!")
        else:
            print("The out degree of the vertex {} is {}.".format(vertex, degree))

    def check_if_edge_ui(self):
        """
        A function that checks if there is an edge between two vertices in the current graph and prints a message with that edge and its cost.
        :return: None
        """
        vertex_x = int(input("Enter x = "))
        vertex_y = int(input("Enter y = "))
        edge = self.__graphs[self.__current].find_if_edge(vertex_x, vertex_y)
        if edge is not False:
            print("({}, {}) is an edge and its cost is {}!".format(vertex_x, vertex_y, edge))
        else:
            print("({}, {}) is not an edge!".format(vertex_x, vertex_y))

    def copy_current_graph_ui(self):
        """
        A function that makes a copy of the current graph.
        :return: None
        """
        copy = self.__graphs[self.__current].copy_graph()
        self.__graphs.append(copy)

    def read_graph_from_file_ui(self):
        """
        A function that reads a graph from a file.
        :return: None
        """
        filename = input("Enter the name of the file: ")
        if self.__current is None:
            self.__current = 0
        graph = read_graph_from_file(filename)
        self.__graphs.append(graph)
        self.__current = len(self.__graphs) - 1

    def read_undirected_graph_from_file_ui(self):
        """
        A function that reads an undirected graph from a file.
        :return: None
        """
        filename = input("Enter the name of the file: ")
        if self.__current is None:
            self.__current = 0
        graph = read_undirected_graph_from_file(filename)
        self.__graphs.append(graph)
        self.__current = len(self.__graphs) - 1

    def write_graph_to_file_ui(self):
        """
        A function that writes the current graph to a file.
        :return: None
        """
        current_graph = self.__graphs[self.__current]
        output_file = "random_graph" + str(self.__current) + ".txt"
        write_graph_to_file(current_graph, output_file)

    def write_modified_graph_to_file_ui(self):
        """
        A function that writes the modified graph to a file.
        :return: None
        """
        current_graph = self.__graphs[self.__current]
        output_file = "modified_graph" + str(self.__current) + ".txt"
        write_graph_to_file(current_graph, output_file)

    def find_lowest_length_path(self):
        """
        A function that finds in the current graph the shortest path between two given vertices.
        :return: None, but it prints the path and its length or a message if there is no such path
        """
        start_vertex = int(input("Enter the start vertex: "))
        goal_vertex = int(input("Enter the goal vertex: "))
        path = self.__graphs[self.__current].bfs(start_vertex, goal_vertex)
        if path is not None:
            print(f"The shortest path from {start_vertex} to {goal_vertex} has the length = {len(path) - 1} "
                  f"and is as follows:\n{path}.\n")
        else:
            print(f"There is no path from {start_vertex} to {goal_vertex}.\n")

    def find_lowest_cost_path(self):
        """
        A function that finds in the current graph the path with the smallest cost between two given vertices.
        :return: None, but it prints the cost and the corresponding path or a message if there is no such path
        """
        start_vertex = int(input("Enter the start vertex: "))
        goal_vertex = int(input("Enter the goal vertex: "))
        distance, predecessor, has_negative_cycle = self.__graphs[self.__current].bellman_ford(start_vertex)

        if has_negative_cycle:
            print("Negative cost cycle detected, reachable from vertex {}!".format(start_vertex))
        else:
            n = len(distance[0]) - 1
            minimum_cost = float('inf')
            best_k = -1
            for k in range(n + 1):
                if distance[goal_vertex][k] < minimum_cost:
                    minimum_cost = distance[goal_vertex][k]
                    best_k = k

            if minimum_cost == float('inf'):
                print(f"Vertex {goal_vertex} is unreachable from {start_vertex}.")
                return

            path = []
            current = goal_vertex
            k = best_k
            while current is not None and k >= 0:
                path.insert(0, current)
                current = predecessor[current][k]
                k -= 1
            print(f"The path is {path} and the cost is {minimum_cost}.\n")

    def check_dag_ui(self):
        """
        A function that checks if the current graph is a DAG and prints a topological sorting if it is a DAG.
        :return: None, but it prints a message if the graph is not a DAG, or a topological order otherwise
        """
        if self.__current is None:
            print("No graph selected.")
            return

        graph = self.__graphs[self.__current]
        if graph.is_dag():
            topological_order = graph.topological_sort()
            print("The graph is a DAG. Topological order is:")
            print(topological_order)
        else:
            print("The graph is not a DAG.")

    def find_highest_cost_path_ui_DAG(self):
        """
        A function that finds a highest cost path between two given vertices in a DAG and that cost.
        :return: None, but it prints a message if the graph is not a DAG, or a highest cost path and that cost otherwise
        """
        if self.__current is None:
            print("No graph selected.")
            return

        graph = self.__graphs[self.__current]
        if not graph.is_dag():
            print("The graph is not a DAG. Cannot find paths.")
            return

        start = int(input("Enter the start vertex: "))
        end = int(input("Enter the end vertex: "))
        max_cost, path = graph.find_highest_cost_path(start, end)
        if len(path) == 0:
            print(f"No paths available from {start} to {end}.")
        else:
            print(f"Maximum cost from {start} to {end} is {max_cost} and one of the paths having this cost is:\n{path}.")

    def count_paths_ui(self):
        """
        A function that finds the total number of paths between two vertices in a DAG.
        :return: None, but it prints a message if the graph is not a DAG, or the number of paths otherwise
        """
        if self.__current is None:
            print("No graph selected.")
            return

        graph = self.__graphs[self.__current]
        if not graph.is_dag():
            print("The graph is not a DAG. Cannot count paths.")
            return

        start = int(input("Enter the start vertex: "))
        end = int(input("Enter the end vertex: "))
        num_paths = graph.count_paths(start, end)
        print(f"The number of distinct paths from vertex {start} to vertex {end} is {num_paths}.")

    def find_lowest_cost_paths_ui_DAG(self):
        """
        A function that finds the number of lowest cost paths between two given vertices in a DAG and that cost.
        :return: None, but it prints a message if the graph is not a DAG, or the number of lowest cost paths and that cost otherwise
        """
        if self.__current is None:
            print("No graph selected.")
            return

        graph = self.__graphs[self.__current]
        if not graph.is_dag():
            print("The graph is not a DAG. Cannot find paths.")
            return

        start = int(input("Enter the start vertex: "))
        end = int(input("Enter the end vertex: "))
        min_cost, count_paths = graph.find_lowest_cost_paths(start, end)
        if count_paths == 0:
            print(f"No paths available from {start} to {end}.")
        else:
            print(f"Minimum cost from {start} to {end} is {min_cost} with {count_paths} distinct path(s).")

    def hamiltonian_cycle_of_no_more_than_twice_the_minimum_cost_ui(self):
        """
        A function that finds a Hamiltonian cycle of no more than twice the minimum cost and prints it in an undirected graph.
        :return: None, but it prints the Hamiltonian cycle
        """
        self.read_undirected_graph_from_file_ui()
        undirected_graph = self.__graphs[self.__current]
        hamiltonian_cycle = undirected_graph.hamiltonian_cycle_of_no_more_than_twice_the_minimum_cost()
        if len(hamiltonian_cycle) == 0:
           print("No Hamiltonian cycle!\n")
           return
        print(f"A Hamiltonian cycle of cost no more than twice the minimum cost is:\n{hamiltonian_cycle}")

    def print_menu(self):
        """
        A function that prints the menu of the application.
        :return: None
        """
        print("Graph Operations Menu\n" +
              "---------------------\n" +
              "0. Exit\n\n" +
              "Graph Initialization\n" +
              "1. Create a random graph with specified number of vertices and edges.\n" +
              "2. Read the graph from a text file.\n" +
              "3. Write the graph in a text file.\n" +
              "4. Switch the graph.\n" +
              "5. Add an empty graph.\n\n" +
              "Graph Properties\n" +
              "6. Get the number of vertices.\n" +
              "7. Get the number of edges.\n" +
              "8. Get the in degree of a vertex.\n" +
              "9. Get the out degree of a vertex.\n" +
              "10. Parse all the vertices.\n\n" +
              "Edge and Vertex Operations\n" +
              "11. Add a vertex.\n" +
              "12. Remove a vertex.\n" +
              "13. Add an edge.\n" +
              "14. Remove an edge.\n" +
              "15. Modify the cost of an edge.\n\n" +
              "Graph Analysis\n" +
              "16. List the outgoing edges of a given vertex.\n" +
              "17. List all outgoing vertices of the graph.\n" +
              "18. List the incoming edges of a given vertex.\n" +
              "19. List all incoming vertices of the graph.\n" +
              "20. List the edges and their costs.\n" +
              "21. Check if there is an edge between two given vertices.\n" +
              "22. Make a copy of the graph.\n\n" +
              "Modified Files\n" +
              "23. Write the modified graph in a text file.\n\n" +
              "New Requirements\n" +
              "24. Find the shortest path between two given vertices.\n" +
              "25. Find the lowest cost path between two given vertices.\n" +
              "26. Check if the graph is a DAG and perform topological sorting.\n" +
              "27. Find a highest cost path between two vertices in a DAG.\n" +
              "28. Find the number of distinct paths between two vertices in a DAG.\n" +
              "29. Find the number of distinct lowest cost paths between two vertices in a DAG.\n" +
              "30. Find a Hamiltonian cycle of no more than twice the minimum cost in an undirected graph.\n")

    def start_ui(self):
        print("Welcome!")
        done = False
        self.add_empty_graph()
        print("The current graph is an empty graph!")
        command_dict = {"1": self.create_random_graph_ui,
                        "2": self.read_graph_from_file_ui,
                        "3": self.write_graph_to_file_ui,
                        "4": self.switch_graph_ui,
                        "5": self.add_empty_graph,
                        "6": self.get_number_of_vertices_ui,
                        "7": self.get_number_of_edges_ui,
                        "8": self.get_in_degree_ui,
                        "9": self.get_out_degree_ui,
                        "10": self.parse_all_vertices,
                        "11": self.add_vertex_ui,
                        "12": self.delete_vertex_ui,
                        "13": self.add_edge_ui,
                        "14": self.remove_edge_ui,
                        "15": self.modify_cost_ui,
                        "16": self.list_outgoing,
                        "17": self.list_all_outgoing,
                        "18": self.list_incoming,
                        "19": self.list_all_incoming,
                        "20": self.list_all_costs,
                        "21": self.check_if_edge_ui,
                        "22": self.copy_current_graph_ui,
                        "23": self.write_modified_graph_to_file_ui,
                        "24": self.find_lowest_length_path,
                        "25": self.find_lowest_cost_path,
                        "26": self.check_dag_ui,
                        "27": self.find_highest_cost_path_ui_DAG,
                        "28": self.count_paths_ui,
                        "29": self.find_lowest_cost_paths_ui_DAG,
                        "30": self.hamiltonian_cycle_of_no_more_than_twice_the_minimum_cost_ui
                        }
        while not done:
            try:
                self.print_menu()
                option = input("Enter a command from the menu: ")
                if option == "0":
                    done = True
                    print("\nGoodbye! :)")
                elif option in command_dict:
                    command_dict[option]()
                else:
                    print("\nInvalid command! Try again!\n\n")
            except Exception as e:
                print(str(e))
