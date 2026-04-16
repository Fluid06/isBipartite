#pragma once

#include <vector>
#include <cstdint>

/**
 * @brief Výčtový typ barev, kterých může vrchol nabývat
 * 
 * Výčtový typ je využit jako atribut třídy Vertex a slouží primárně k pomyslnému rozdělení vrcholů v grafu do dvou množin.
 * Tento mechanismus může být obzvlášť užitečný při rozhodování o bipartitě daného grafu. Enum může nabývat hodnot od od 0 do 2.
 * 
 * @see Vertex::color
 */
enum Color
{
    NONE, GREEN, RED
};

/**
 * @brief Reprezentuje konkrétní vrchol grafu
 * 
 * Jedná se o pouhý datový kontejner bez větší vnitřní logiky. Ukládá informace o jedinečném indexu jednoznačně identifikujícím
 * aktuální vrchol, dále jeho barvu, tedy do jaké ze dvou, respektive tří, skupin je možné jej zařadit a množinu indexů všech sousedních vrcholů.
 * Množina indexů sousedních vrcholů je realizována pomocí vektoru. Je tedy v paměti uložena v jednom souvislém bloku a přístup k jednotlivým
 * prvkům je možný v konstantním čase.
 */
class Vertex
{
private:
    /**
     * @brief Jedinečný identifikátor vrcholu
     * 
     * Celé nezáporné číslo vyjadřující hodnotu/číslo vrcholu. Rozsah neznaménkového celočíselného 32-bitového čísla je od 0 do 4 294 967 295.
     * Tento rozsah by měl pokrývat potřeby absolutní většiny případů z reálného světa.
     * Hodnoty, kterých může idx reálně v konkrétním případě nabývat, jsou v rozsahu od 0 do n-1, kde n je celkový počet vrcholů v grafu.
     * Tato hodnota je neměnná a zároveň slouží jako přímý index hlavního pole všech uzlů v grafu (std::vector<Vertex> nodes).
     * 
     * @see Graph::nodes
     */
    const uint32_t idx;
    
    /**
     * @brief Aktuální barva vrcholu
     * 
     * Vyjadřuje do jaké ze dvou pomyslných množin vrchol spadá. 
     * Je přidělen během postupného prohledávání metodou Graph::isBipartite. Implicitně je NONE (0).
     * 
     * @see Graph::isBipartite
     */
    Color color = NONE;

    /**
     * @brief Množina indexů sousedních vrcholů
     * 
     * Obsahuje indexy vrcholů, které jsou s aktuálním vrcholem přímo spojeny hranou, tedy indexy sousedních vrcholů.
     * Hodnoty jsou uloženy pomocí vektoru, přístup k jednotlivým hodnotám je tak možný v konstantním čase.
     */
    std::vector<uint32_t> neighbors;
    
public:
    /**
     * @brief Konstruktor třídy Vertex
     * 
     * @param idx Jedinečný index vrcholu
     */
    Vertex(uint32_t idx);

    /**
     * @brief Getter pro atribut idx
     * 
     * Metoda nemění stav instance - read-only metoda.
     * 
     * @return Metoda vrací hodnotu atributu idx aktuální instance vrcholu.
     */
    uint32_t getIdx() const;

    /**
     * @brief Getter pro atribut color
     * 
     * Metoda nemění stav instance - read-only metoda.
     * 
     * @return Metoda vrací hodnotu atributu color aktuální instance vrcholu.
     */
    Color getColor() const;

    /**
     * @brief Setter pro atribut color
     * 
     * @param color Hodnota, která má být atributu color přiřazena.
     * 
     * Metoda přiřadí atributu color hodnotu předanou pomocí parametru.
     * Bez návratové hodnoty.
     * 
     */
    void setColor(Color color);

    /**
     * @brief Getter pro atribut neighbors
     * 
     * Metoda sama o sobě nemění stav instance - read-only metoda.
     * 
     * @return Vrací referenci na vektor obsahující indexy sousedních vrcholů sloužící pouze pro čtení. Data vektoru jsou takto chráněna před nechtěným přepisem.
     * 
     * @see Vertex::neighbors
     */
    const std::vector<uint32_t>& getNeighbors() const;

    /**
     * @brief Metoda pro přidání souseda
     * 
     * @param idx Index vrcholu, který chceme přidat do vektoru indexů sousedních vrcholů.
     * 
     * Jedná se o metodu, která na konec vektoru sousedů pomocí metody push_back(uint32_t) umístí index vrcholu předaný pomocí parametru, tedy přidá souseda aktuální instanci vrcholu.
     * Pokud by přidání nového prvku mělo přesáhnout aktuální kapacitu vektoru, tak vektor kapacitu automaticky navýší. 
     * Metoda tak vytváří orientovanou hranu mezi dvěma vrcholy.
     * 
     * @see Vertex::neighbors
     */
    void addNeighbor(uint32_t idx);
};