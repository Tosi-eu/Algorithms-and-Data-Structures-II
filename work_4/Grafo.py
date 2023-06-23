class Grafo:
    def __init__(self):
        self.vertices = {}
    
    def adicionar_vertice(self, vertice):
        self.vertices[vertice] = {}
    
    def adicionar_aresta(self, origem, destino, peso):
        self.vertices[origem][destino] = peso
        self.vertices[destino][origem] = peso
    
    def obter_custo_entrega(self, cliente):
        pizzaria = "Pizzaria"
        distancias = {v: float('inf') for v in self.vertices}
        distancias[pizzaria] = 0

        visitados = set()
        while len(visitados) < len(self.vertices):
            vertice_atual = min((v for v in self.vertices if v not in visitados), key=lambda x: distancias[x])
            visitados.add(vertice_atual)
            for vizinho in self.vertices[vertice_atual]:
                if vizinho not in visitados:
                    novo_custo = distancias[vertice_atual] + self.vertices[vertice_atual][vizinho]
                    if novo_custo < distancias[vizinho]:
                        distancias[vizinho] = novo_custo
        
        custos_entrega = []
        for c in cliente:
            custo = 1.50 + 0.2 * distancias[c]
            custos_entrega.append('{:.2f}'.format(custo))
        
        return custos_entrega
