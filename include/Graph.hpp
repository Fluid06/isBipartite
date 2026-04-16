#pragma once

#include <vector>
#include <stack>
#include "Vertex.hpp"

/**
 * @brief Reprezentuje graf složen z jednotlivých vrcholů spojených hranami
 * 
 * Graf může být nesouvislý, cyklický a vnitřně je implementován jako neorientovaný.
 * Třída má jeden atribut a to je vektor obsahující objekty třídy Vertex, tedy všechny vrcholy tvořící graf. 
 * Díky tomuto vektoru můžeme přistupovat k libovolné instanci vrcholu v konstantním čase.
 * Vrcholy jsou v paměti umístěny v jednom souvislém bloku, což procesoru značně usnadňuje přístup k jednotlivým vrcholům v paměti.
 */
class Graph
{
private:
    /**
    * @brief Množina všech vrcholů v grafu
    * 
    * Vektor obsahuje všechny instance třídy Vertex, které se v grafu nacházejí.
    */
    std::vector<Vertex> vertices;

public:
    /**
     * @brief Konstruktor třídy Graph
     * 
     * @param vertexCount Počet vrcholů, které graf obsahuje
     * 
     * Konstruktor nejprve na vektor vertices zavolá metodu reserve(size_t), která předem alokuje místo o velikosti potřebné
     * k uložení všech instancí vrcholů (vertexCount * sizeof(Vertex)) v jednom souvislém bloku paměti.
     * Díky tomu nemusí vektor s přibývajícím počtem prvků navyšovat svou kapacitu a opakovaně tak realokovat místo na haldě.
     * 
     * Metoda n-krát, kdy n je vertexCount, volá na vektor vertices metodu emplace_back(uint32_t), 
     * která na konec vektoru vkládá prvek, jehož konstruktoru jsou předány argumenty této metody.
     * 
     * @par Použité zdroje:
     * - [CPlusPlus vector::reserve](https://cplusplus.com/reference/vector/vector/reserve/)
     * - [CPlusPlus vector::emplace_back](https://cplusplus.com/reference/vector/vector/emplace_back/)
     * 
     * @see Graph::vertices
     */
    Graph(uint32_t vertexCount);

    /**
     * @brief Metoda pro vytvoření hrany
     * 
     * @param v1 Index prvního z vrcholů, mezi kterými vytváříme hranu
     * @param v2 Index druhého z vrcholů, mezi kterými vytváříme hranu
     * 
     * Metoda nejprve pomocí hodnoty prvního parametru (v1; index konkrétního vrcholu) získá z vektoru vrcholů (std::vector<Vertex> vertices), pomocí metody at(size_t),
     * konkrétní objekt třídy Vertex a zavolá jeho metodu addNeighbor(uint32_t), která do vnitřního vektoru (std::vector<uint32_t> neighbors) daného objektu přídá index předaný druhým parametrem.
     * Jelikož je graf neorientovaný, je proces vykonán znovu, ale s prohozenými hodnotami.
     *
     * @see Vertex::addNeighbor
     * @see Vertex::neighbors
     */
    void addEdge(uint32_t v1, uint32_t v2);

    /**
     * @brief Metoda zjišťující bipartititu grafu
     * 
     * @return Návratovou hodnotou je logická hodnota vyjadřující zda je graf bipartitní či nikoliv.
     * 
     * @retval true Graf je bipartitní
     * @retval false Graf není bipartitní
     * 
     * Principem ověření bipartity je rozdělení vrcholů do dvou množin s tím, že dva sousední vrcholy nesmí ležet ve stejné množině. Vrcholy není potřeba doslovně přidávat do množin, ale stačí je nějak označit.
     * Vrcholům je přidělena barva (GREEN, RED), která vrcholy pomyslně rozděluje na dvě množiny.
     * Lze tedy říct, že žádný ze sousedních vrcholů nesmí mít stejnou barvu jako zrovna zkoumaný vrchol.
     * 
     * Konkrétních metod pro ověření bipartity grafu je několik. Mezi ty základní patří průchod do hloubky (DFS) a průchod do šířky (BFS). Oba způsoby mohou navíc být realizovány jak imperativně, tak rekurzivně.
     * Tato konkrétní metoda využívá průchodu do hloubky. V případě, kdy by vyhledávání bylo realizováno pomocí rekurze, tak by pří obrovském množství vrcholů mohlo eventuelně dojít k nedostatku místa na zásobníku.
     * Z tohoto důvodu je zde využitý imperativní způsob průchodu do hloubky, který využívá datové struktury zvané zásobník (std::stack).
     * 
     * Nejprve je vytvořen objekt zásobníku obsahující indexy vrcholů, které čekají na zpracování.
     * Následně je pro každý jeden vrchol v grafu vykonáno několik kroků.
     * 
     * Jestliže se jedná o vrchol, který už má přidělenou barvu (vertex.getColor() != NONE), lze s jistotou říct, že i všechny jeho sousední vrcholy jsou již označeny barvou a nedochazí u nich ke kolizi, proto je možné následující kroky přeskočit.
     * 
     * Pokud vrchol ještě není označen barvou, je mu přiřazena výchozí barva (GREEN) a jeho index je přidán do zásobníku.
     * 
     * Následuje cyklus s podmínkou na konci, který beží dokud zásobník není prázdný.
     * V tomto cyklu se získá index z vrcholu zásobníku a následně je ze zásobníku odebrán.
     * 
     * Pro každého souseda vrcholu s daným indexem je následně ověřeno podmínkou zdali už nemá přiřazenou barvu.
     * Pokud sousední vrchol barvu má a shoduje s barvou aktuálně zkoumaného vrcholu (neighborColor == currentColor), můžeme ihned vrátit hodnotu false, protože se jedná o porušení základního pravidla bipartitního grafu.
     * Pokud sousední vrchol barvu má a zároveň nebyla splněna předchozí podmínka (neighborColor == NONE), tedy logicky má sousední vrchol jinou barvu než aktuálně zkoumaný vrchol, pravidlo bipartity je splněno a můžeme přejít na zkoumání dalšího ze sousedních vrcholů.
     * Pokud sousední vrchol barvu ještě nemá, je mu přiřazena jiná barva než má vrchol, jehož sousedi jsou zkoumáni. Index tohoto sousedního vrcholu je pak umístněn na vrchol zásobníku a jelikož ukončovací podmínka cyklu s podmínkou na konci (!stack.empty()) není splněna, pro jeho sousedy je celý proces vykonán znovu.
     * 
     * Jakmile je průchod všemi vrcholy v grafu dokončen a nedošlo ke kolizi barev, graf musí být bipartitní - je vrácena hodnota true.
     */
    bool isBipartite();
};