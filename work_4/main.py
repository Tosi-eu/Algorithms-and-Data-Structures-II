from Grafo import Grafo

def main():
    # Leitura da entrada
    n = int(input())
    grafo = Grafo()
    for _ in range(n):
        vertice = input()
        grafo.adicionar_vertice(vertice)
    
    m = int(input())
    for _ in range(m):
        origem, destino, peso = input().split()
        peso = float(peso)
        grafo.adicionar_aresta(origem, destino, peso)
    
    q = int(input())
    clientes = []
    for _ in range(q):
        cliente = input()
        clientes.append(cliente)
    
    # Cálculo dos custos de entrega
    custos_entrega = grafo.obter_custo_entrega(clientes)
    
    # Impressão da saída
    for custo in custos_entrega:
        print(custo)


if __name__ == "__main__":
    main()
