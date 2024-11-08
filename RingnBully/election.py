import time
import threading

class Node:
    def __init__(self, id):
        self.id = id
        self.coordinator = None

    def initiate_ring_election(self, nodes):
        print(f"Node {self.id} initiates Ring election")
        max_id = max(node.id for node in nodes)
        if self.id == max_id:
            self.coordinator = self.id
            print(f"Node {self.id} becomes the coordinator.")
            return
        next_node = nodes[(nodes.index(self) + 1) % len(nodes)]
        next_node.start_ring_election(nodes)

    def start_ring_election(self, nodes):
        if self.coordinator is None:
            print(f"Node {self.id} passes the election message.")
            time.sleep(1)
            self.initiate_ring_election(nodes)

    def start_bully_election(self, nodes):
        print(f"Node {self.id} starts the Bully election.")
        higher_nodes = [node for node in nodes if node.id > self.id]
        if not higher_nodes:
            self.coordinator = self.id
            print(f"Node {self.id} becomes the coordinator.")
            return
        for higher_node in higher_nodes:
            higher_node.send_bully_election_message()

    def send_bully_election_message(self):
        print(f"Node {self.id} sends Bully election message.")
        time.sleep(1)
        print(f"Node {self.id} received no response, declares itself as coordinator.")
        self.coordinator = self.id

def main():
    nodes = [Node(1), Node(2), Node(3)]

    for node in nodes:
        node.start_bully_election(nodes)
        node.start_ring_election(nodes)

if __name__ == "__main__":
    main()
