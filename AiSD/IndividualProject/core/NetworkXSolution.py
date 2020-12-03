import networkx as nx
import core.DataClasses as dataClasses


def SolutionFinder(readFile: list):
    suppliers = readFile[0]
    pharmacies = readFile[1]
    connections = readFile[2]
    matrix = createConnectionsMatrix(connections)
    n = dataClasses.Supplier.supplierCounter
    G = nx.DiGraph()

    for supplier in suppliers:
        G.add_node(supplier.getID(), subset=1, demand=-(supplier.getDailyProduction()))

    for ind, pharmacy in enumerate(pharmacies):
        if ind % 2 == 0:
            x = 0
        else:
            x = 2
        G.add_node(pharmacy.getID() + n, subset=x, demand=pharmacy.getDailyNeed())

    demand = 0
    for node in G.nodes():
        demand += G.nodes[node]['demand']

    if demand < 0:
        G.add_node("x", demand=abs(demand), subset=2)
    elif demand > 0:
        G.add_node("x", demand=-demand, subset=2)

    for con in connections:
        G.add_edge(con.getSupplierID(), con.getPharmacyID() + n, weight=con.getCost(), capacity=con.getMaxDelivery())
        if demand < 0:
            G.add_edge(con.getSupplierID(), "x", weight=0, capacity=-demand)
        elif demand > 0:
            G.add_edge("x", con.getPharmacyID() + n, weight=0, capacity=demand)

    con1 = nx.capacity_scaling(G)
    con = con1[1]
    for supplier in suppliers:
        for pharmacy in pharmacies:
            x = con[supplier.getID()][pharmacy.getID() + n]
            cost = matrix[supplier.getID()][pharmacy.getID()].getCost()
            if x != 0:
                print(supplier.getName(), " -> ", pharmacy.getName(), "[Koszt: {} * {} = {}zł]".format(x, cost, round(x * cost, 2)))

    print("\n\nKoszt całkowity:", con1[0])


def createConnectionsMatrix(connections: list):
    numberOfPharmacies = dataClasses.Pharmacy.pharmacyCounter
    numberOfSuppliers = dataClasses.Supplier.supplierCounter

    connectionMatrix = [[0] * numberOfPharmacies for i in range(numberOfSuppliers)]

    for connection in connections:
        supplierID = connection.getSupplierID()
        pharmacyID = connection.getPharmacyID()
        connectionMatrix[supplierID][pharmacyID] = connection

    return connectionMatrix
