class Node:
    def __init__(self, node_id):
        self.node_id = node_id
        self.crashed = False
        self.neighbors = []
        self.leader = None
        self.received_ok = False
        self.election = False

    def crash(self):
        self.crashed = True

    def add_neighbor(self, neighbor):
        self.neighbors.append(neighbor)

    def initiate_ring_election(self, active):
        if self in active:
            max_id = -1
            coordinator = None
            for node in active:
                if node.node_id > max_id:
                    max_id = node.node_id
                    coordinator = node
            print(f"Node {coordinator.node_id} wins and is elected as the leader.")
            self.acknowledge(coordinator)
        else:
            active.append(self)
            start = self.neighbors[0]
            x = start
            while True:
                if not x.crashed:
                    print(f"Node {self.node_id} passes election to {x.node_id}. Active nodes: {[n.node_id for n in active]}")
                    x.initiate_ring_election(active)
                    break
                else:
                    x = x.neighbors[0]
                if x == start:
                    print(f"Node {self.node_id} found no active nodes to pass to")
                    break

    def acknowledge(self, leader):
        if self.leader and self.leader == leader:
            return
        if not self.crashed and self != leader:
            print(f"Node {self.node_id} acknowledges Node {leader.node_id} as leader")
            self.leader = leader
        for n in self.neighbors:
            n.acknowledge(leader)

    def start_bully_election(self, nodes):
        if self.election:
            return
        print(f"Node {self.node_id} initiates a Bully election")
        higher_nodes = [node for node in nodes if node.node_id > self.node_id]
        for higher_node in higher_nodes:
            print(f"Node {self.node_id} sends election message to Node {higher_node.node_id}")
            response = higher_node.receive_election_message(self)
            if response:
                response.start_bully_election(nodes)
        if not self.received_ok:
            print(f"Node {self.node_id} declares itself as the leader")
            self.declare_leader(nodes)
        self.election = True

    def receive_election_message(self, initiating_node):
        if self.crashed:
            return None
        print(f"Node {self.node_id} sends OK message to Node {initiating_node.node_id}")
        initiating_node.receive_ok_message(self)
        return self

    def receive_ok_message(self, responding_node):
        print(f"Node {self.node_id} receives OK message from Node {responding_node.node_id}")
        self.received_ok = True

    def declare_leader(self, nodes):
        for node in nodes:
            if node != self and not node.crashed:
                node.acknowledge_leader(self)

    def acknowledge_leader(self, leader):
        print(f"Node {self.node_id} acknowledges Node {leader.node_id} as the leader")
        self.leader = leader

def simulate_ring_election(nodes, initial_candidate_id):
    initial_candidate = nodes[initial_candidate_id]
    print(f"Node {initial_candidate.node_id} initiates the Ring Election")
    initial_candidate.initiate_ring_election([])

def simulate_bully_election(nodes, initial_candidate_id):
    initial_candidate = nodes[initial_candidate_id]
    print(f"Node {initial_candidate.node_id} initiates the Bully Election")
    initial_candidate.start_bully_election(nodes)

def main():
    nodes = [Node(i) for i in range(7)]
    for i in range(len(nodes)):
        nodes[i].add_neighbor(nodes[(i + 1) % len(nodes)])

    while True:
        print("\nChoose the election algorithm:")
        print("1. Ring Election")
        print("2. Bully Election")
        print("0. Exit")
        choice = int(input("Enter your choice: "))

        if choice == 1:
            crashed_nodes = [5, 6]  # Adjust crashed nodes as desired
            for node_id in crashed_nodes:
                nodes[node_id].crash()
            initial_candidate_id = int(input("Enter the initial candidate ID for Ring Election: "))
            simulate_ring_election(nodes, initial_candidate_id)

        elif choice == 2:
            crashed_nodes = [3]  # Adjust crashed nodes as desired
            for node_id in crashed_nodes:
                nodes[node_id].crash()
            initial_candidate_id = int(input("Enter the initial candidate ID for Bully Election: "))
            simulate_bully_election(nodes, initial_candidate_id)

        elif choice == 0:
            print("Exiting...")
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
