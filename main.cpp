#include "multiset.h"
#include <iostream>
#include <cassert>

/**
	@brief Funtore di confronto fra interi
	
	Funtore di confronto tra interi, ritorna true se il primo parametro
	è minore del secondo parametro
*/
struct minoreInt {
	bool operator()(int a, int b) const{
		return a < b;
	}
};

/**
	@brief Funtore di uguaglianza fra interi
	
	Funtore che confronta due interi e ritorna true se il primo parametro
	è uguale del secondo parametro
*/
struct ugualeInt {
	bool operator()(int a, int b) const{
		return a == b;
	}
};

/**
	@brief Test MultiSet<int, minoreInt, ugualeInt>
	
	Test sull'utilizzo di tutte le funzioni di un
	MultiSet<int, minoreInt, ugualeInt>
	
	@post Non sono presenti memory leak
*/
void testMultiSetInt() {
	std::cout << std::endl;
	std::cout << "TEST MULTISET<INT, MINOREINT, UGUALEINT>" << std::endl << std::endl;
	
	// Test costruttore di default
	MultiSet<int, minoreInt, ugualeInt> s1;
	MultiSet<int, minoreInt, ugualeInt> s2;
	
	s1.aggiungiElemento(2);
	s1.aggiungiElemento(2);
	s1.aggiungiElemento(1);
	s1.aggiungiElemento(4);
	s1.aggiungiElemento(3);
	s1.aggiungiElemento(7);
	
	// Test contains, aggiungiElemento
	assert(s1.contains(2));
	assert(!s1.contains(0));
	
	// Test dimensioneSet()
	assert(s1.dimensioneSet() == 6);
	
	// Test << e iteratori 
	std::cout << "Dimensione di s1: " << s1.dimensioneSet() << std::endl;
	std::cout << "Contenuto di s1: " << s1 << std::endl;
	std::cout << "Dimensione di s2: " << s2.dimensioneSet() << std::endl;
	std::cout << "Contenuto di s2: " << s2 << std::endl;
	std::cout << std::endl;

	// Test quanti
	std::cout << "s2 contiene "<< s2.quanti(0) << " zero" << std::endl;
	std::cout << "s1 contiene "<< s1.quanti(3) << " tre" << std::endl;
	assert(s1.quanti(3) == 1);
	std::cout << "s1 contiene "<< s1.quanti(2) << " 2" << std::endl;
	assert(s1.quanti(2) == 2);
	std::cout << "s1 contiene "<< s1.quanti(10) << " dieci" << std::endl;
	assert(s1.quanti(10) == 0);
	std::cout << std::endl;
	
	// Test rimuoviElemento e eVuota
	std::cout << "Se il MultiSet e' vuoto e si prova a togliere un elemento:" << std::endl;
	s2.rimuoviElemento(0);
	std::cout << "Se si prova a togliere un elemento  non presente nel MultiSet:" << std::endl;
	s1.rimuoviElemento(0);
	s1.rimuoviElemento(2);
	s1.rimuoviElemento(2);
	s1.rimuoviElemento(4);
	s1.rimuoviElemento(1);
	assert(s1.dimensioneSet() == 2);
	
	std::cout << "Contenuto di s1 dopo la rimozione di: ";
	std::cout << "\"0, 2, 2, 4, 1\"" << std::endl;
	std::cout << s1 << std::endl;
	std::cout << std::endl;

	MultiSet<int, minoreInt, ugualeInt> s3(s1);
	MultiSet<int, minoreInt, ugualeInt> s4;
	s4 = s1;
	
	// Test cctor e operator=
	std::cout << "s3 costruito con cctor da s1, e ad s4 e' stato assegnato s1" << std::endl;
	std::cout << "Dimensione di s3: " << s3.dimensioneSet() << std::endl;
	std::cout << "Contenuto di s3: " << s3 << std::endl;
	std::cout << "Dimensione di s4: " << s4.dimensioneSet() << std::endl;
	std::cout << "Contenuto di s4: " << s4 << std::endl;
	std::cout << std::endl;

	// Test operator==
	std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
	std::cout << "s1 == s4: " << (s1 == s4) << std::endl;
	s3.rimuoviElemento(7);
	s4.aggiungiElemento(3);
	std::cout << "Dopo aver tolto un sette da s3 e aggiunto un tre a s4 verifichiamo nuovamente:" << std::endl;
	std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
	std::cout << "s1 == s4: " << (s1 == s3) << std::endl;
	std::cout << "Contenuto di s1: " << s1 << std::endl;
	std::cout << "Contenuto di s3: " << s3 << std::endl;
	std::cout << "Contenuto di s4: " << s4 << std::endl;
	std::cout << std::endl;
	
	std::cout << "FINE TEST MULTISET<INT, MINOREINT, UGUALEINT>" << std::endl << std::endl;
	std::cout << std::endl;
} // Test ~MultiSet e eliminaSet

/**
	@brief Struct che rappresenta un punto
	
	Struct che rappresenta un punto in due dimensioni
*/
struct Punto2D {
	int x;
	int y;
	
	Punto2D() : x(0), y(0) {}
	
	Punto2D(int xVal, int yVal) : x(xVal), y(yVal) {}
};

/**
	@brief Funtore di confronto fra punti
	
	Funtore di confronto tra punti in due dimensioni, ritorna true se il
	primo parametro	è minore del secondo parametro.
	Si è assunto arbitrariamente che un punto è minore di un altro se
	ha la coordinata x minore o, in caso di parità, la coordinata y minore
*/
struct minore2D {
	bool operator()(Punto2D a, Punto2D b) const{
		if ((a.x < b.x) || (a.x == b.x && a.y < b.y))
			return true;
		return false;
	}
};

/**
	@brief Funtore di uguaglianza fra interi
	
	Funtore che confronta due interi e ritorna true se il primo parametro
	è uguale del secondo parametro
*/
struct uguale2D {
	bool operator()(Punto2D a, Punto2D b) const{
		return a.x == b.x && a.y == b.y;
	}
}; 

/**
	Ridefinizione dell'operatore << per un punto in due dimensioni
*/
std::ostream& operator<<(std::ostream &os, const Punto2D &p) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

/**
	@brief Test MultiSet<Punto2D, minore2D, uguale2D>
	
	Test sull'utilizzo di tutte le funzioni di un
	MultiSet<Punto2D, minore2D, uguale2D>
	
	@post Non sono presenti memory leak
*/
void testMultiSetPunto2D() {
	std::cout << std::endl;
	std::cout << "TEST MULTISET<PUNTO2D, MINORE2D, UGUALE2D>" << std::endl << std::endl;
	
	// Test ctor default, operator<<, iteratori e dimensioneSet
	MultiSet<Punto2D, minore2D, uguale2D> p1;
	MultiSet<Punto2D, minore2D, uguale2D> p4;
	std::cout << "Dimensione di p1: " << p1.dimensioneSet() << std::endl;
	std::cout << "Contenuto di p1: " << p1 << std::endl << std::endl;
	assert(p1.dimensioneSet() == 0);
	
	Punto2D punto1(2, 2);
	Punto2D punto2(2, 5);
	Punto2D punto3(1, 0);
	Punto2D punto4(4, 1);
	
	// Test aggiungiElemento
	p1.aggiungiElemento(punto1);
	p1.aggiungiElemento(punto1);
	p1.aggiungiElemento(punto2);
	p1.aggiungiElemento(punto3);
	p1.aggiungiElemento(punto4);
	std::cout << "Dimensione di p1: " << p1.dimensioneSet() << std::endl;
	assert(p1.dimensioneSet() == 5);
	std::cout << "Contenuto di p1: " << p1 << std::endl << std::endl;
	
	// Test contains
	Punto2D punto5(10, 10);
	assert(p1.contains(punto2) == true);
	assert(p1.contains(punto5) == false);
	
	// Test quanti
	std::cout << "p1 contiene "<< p1.quanti(punto1) << " (2,2)" << std::endl;
	assert(p1.quanti(punto1) == 2);
	std::cout << "p1 contiene "<< p1.quanti(punto2) << " (2,5)" << std::endl;
	assert(p1.quanti(punto2) == 1);
	std::cout << "p1 contiene "<< p1.quanti(punto5) << " (10,10)" << std::endl;
	assert(p1.quanti(punto5) == 0);
	std::cout << std::endl;
	
	// Test rimuoviElemento e eVuota
	std::cout << "Se si prova a rimuovere un elemento da un MultiSet vuoto: " << std::endl;
	p4.rimuoviElemento(punto1);
	std::cout << "p1 dopo che sono stati tolti (10,10), (2,2) e (2,5)" << std::endl;
	std::cout << "Se si prova a togliere un punto non presente nel MultiSet" << std::endl;
	p1.rimuoviElemento(punto5);
	p1.rimuoviElemento(punto1);
	p1.rimuoviElemento(punto2);
	std::cout << "Dimensione di p1: " << p1.dimensioneSet() << std::endl;
	std::cout << "Contenuto di p1: " << p1 << std::endl << std::endl;
	
	// Test cctor e operator=
	MultiSet<Punto2D, minore2D, uguale2D> p2(p1);
	MultiSet<Punto2D, minore2D, uguale2D> p3;
	p3 = p1;
	std::cout << "p3 costruito con cctor da p1, e a p3 e' stato assegnato p1" << std::endl;
	std::cout << "Dimensione di p2: " << p2.dimensioneSet() << std::endl;
	std::cout << "Contenuto di p2: " << p2 << std::endl;
	std::cout << "Dimensione di p3: " << p3.dimensioneSet() << std::endl;
	std::cout << "Contenuto di p3: " << p3 << std::endl << std::endl;
	
	// Test operator==
	std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
	std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
	p2.rimuoviElemento(punto1);
	p3.aggiungiElemento(punto3);
	std::cout << "Dopo aver tolto un (2,2) da p2 e aggiunto un (1,0) a p3 verifichiamo nuovamente:" << std::endl;
	std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
	std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
	std::cout << "Contenuto di p1: " << p1 << std::endl;
	std::cout << "Contenuto di p2: " << p2 << std::endl;
	std::cout << "Contenuto di p3: " << p3 << std::endl;
	std::cout << std::endl;
	
	std::cout << "FINE TEST MULTISET<PUNTO2D, MINORE2D, UGUALE2D>" << std::endl << std::endl;
	std::cout << std::endl;
} // Test ~MultiSet e eliminaSet

/**
	@brief Funtore di confronto fra double
	
	Funtore di confronto tra double, ritorna true se il primo parametro
	è minore del secondo parametro
*/
struct minoreDouble {
	bool operator()(double a, double b) const{
		return a < b;
	}
};

/**
	@brief Funtore di uguaglianza fra double
	
	Funtore che confronta due double e ritorna true se il primo parametro
	è uguale del secondo parametro
*/
struct ugualeDouble {
	bool operator()(double a, double b) const{
		return a == b;
	}
};

/**
	@brief Test del costruttore per iteratori
	
	Test del costruttore che prende in input gli iteratori di inizio e
	fine di una sequenza di dati di un tipo differente
	(in questo caso si passa da double a int)
	
	@post Non sono presenti memory leak
*/
void testCostruttoreIteratori() {
	std::cout << std::endl;
	std::cout << "TEST TEMPLATE<TYPENAME I>MULTISET(I INIZIO, I FINE)" << std::endl << std::endl;
	
	MultiSet<double, minoreDouble, ugualeDouble> d1;
	d1.aggiungiElemento(2.2);
	d1.aggiungiElemento(2.2);
	d1.aggiungiElemento(5.7);
	
	std::cout << "MultiSet di double d1" << std::endl;
	std::cout << "Dimensione di d1: " << d1.dimensioneSet() << std::endl;
	std::cout << "Contenuto di d1: " << d1 << std::endl << std::endl;
	
	
	MultiSet<int, minoreInt, ugualeInt> i1(d1.begin(), d1.end());
	
	std::cout << "MultiSet di int i1 costruito a partire dal MultiSet di double d1:" << std::endl;
	std::cout << "Dimensione di i1: " << i1.dimensioneSet() << std::endl;
	std::cout << "Contenuto di di1: " << i1 << std::endl << std::endl;
	
	std::cout << "FINE TEST TEMPLATE<TYPENAME I>MULTISET(I INIZIO, I FINE)" << std::endl << std::endl;
	std::cout << std::endl;
}

void testConstMultiSetInt() {
	std::cout << std::endl;
	std::cout << "TEST CONST MULTISET<INT, MINOREINT, UGUALEINT>" << std::endl << std::endl;
	std::cout << "Di seguito una serie di test applicati ad un Multiset di int costante" << std::endl;
	std::cout << std::endl;
	
	MultiSet<int, minoreInt, ugualeInt> s1;
	
	s1.aggiungiElemento(2);
	s1.aggiungiElemento(2);
	s1.aggiungiElemento(1);
	
	const MultiSet<int, minoreInt, ugualeInt> s2(s1);
	
	// Test <<
	std::cout << "Multinsieme s1: " << s2 << std::endl;
	std::cout << "Multinsieme costante s2 costruito come copia di s1: " << s2 << std::endl;
	
	// Test contains
	assert(s2.contains(2));
	assert(!s2.contains(0));
	
	// Test dimensioneSet()
	std::cout << "La sua dimensione e' " << s2.dimensioneSet() << std::endl;
	assert(s2.dimensioneSet() == 3);
	std::cout << std::endl;

	// Test quanti
	std::cout << "s2 contiene " << s2.quanti(0) << " zero" << std::endl;
	assert(s2.quanti(0) == 0);
	std::cout << "s2 contiene " << s2.quanti(2) << " 2" << std::endl;
	assert(s1.quanti(2) == 2);
	std::cout << std::endl;
	
	// Test eVuota
	std::cout << "s2 e' vuoto? ";
	if (s2.eVuota()) {
		std::cout << "Sì" << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}
	
	// Test operator==
	std::cout << "s1 == s2: ";
	if (s2 == s1) {
		std::cout << "Sì" << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}
	
	// I seguenti metodi non funzionano in quanto non sono const
	// s2.aggiungiElemento(2);
	// s2.rimuoviElemento(2);
	// s2 = s1;
	// s2.eliminaSet();
	
	std::cout << std::endl;
	std::cout << "FINE TEST CONST MULTISET<INT, MINOREINT, UGUALEINT>" << std::endl << std::endl;
	std::cout << std::endl;
}

int main() {
	
	testMultiSetInt();
	
	testMultiSetPunto2D();
	
	testCostruttoreIteratori();
	
	testConstMultiSetInt();
	
	std::cout << "Fine progetto esame C++" << std::endl;
	
	return 0;
}