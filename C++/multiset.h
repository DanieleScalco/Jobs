#ifndef MULTISET_H
#define MULTISET_H

#include <iostream>
#include <algorithm>

/**
	@brief Classe templata che rappresenta un multinsieme
	
	Classe templata che rappresenta un multinsieme di valori di tipo T.
	M è il funtore di comparazione, mentre U è il funtore di uguaglianza
	degli elementi di tipo T
	
	@param T tipo di dati del multinsieme
	@param M funtore di comparazione tra due dati di tipo T
	@param U funtore di uguaglianza tra due dati di tipo T
*/
template <typename T, typename M, typename U>
class MultiSet {

	/**
		@brief Struct che rappresenta un elemento
		
		Struct che rappresenta un elemento del multinsieme in cui e'
		tenuto il valore di eventuali duplicati dell'elemento
	*/
	struct Elemento {
		
		T valore;	///< Valore dell'elemento
		unsigned int quantita;	///< Quantità di elementi del valore T presente nel MultiSet
		Elemento *next;	///< Puntatore all'elemento successivo del MultiSet
		
		/**
			Costruttore di default di un elemento
			
			@post quantita == 0
			@post next == nullptr
		*/
		Elemento() : quantita(0), next(nullptr) {}
		
		/**
			Costruttore secondario di un elemento
			
			@param v valore dell'elemento
			
			@post valore == v
			@post quantita == 1
			@post next == nullptr
		*/
		explicit Elemento(const T &v) : valore(v), quantita(1), next(nullptr) {}
		
		/**
			Costruttore secondario di un elemento
			
			@param v valore dell'elemento
			
			@post valore == v
			@post quantita == 1
			@post next == nullptr
		*/
		Elemento(const T &v, int q) : valore(v), quantita(q), next(nullptr) {}
		
		/**
			Distruttore di un elemento
		*/
		~Elemento() {
			next = nullptr;
		}
		
	}; // Fine struct elemento
	
	Elemento *_primo;	///< Puntatore al primo elemento del multinsieme
	unsigned int _dimensione;	///< Quantità di elementi totali presenti nel multinsieme
	
	M _minore; ///< Istanza del funtore di confronto (ordinamento, <)
	U _uguale; ///< Istanza del funtore di ordinamento (uguaglianza, =)
	
	/**
		@brief Metodo di supporto per l'aggiunta di un elemento
		
		Metodo di supporto per l'aggiunta di un elemento nel multinsieme
		anche in più di una copia
		
		@param e valore dell'elemento da aggiungere
		@param q quantita di elementi 'e' da aggiungere
	*/
	void aggiungiElemento(const T &e, int q) {
		if (q == 0)	// Se aggiungo un valore di quantità zero non sto aggiungendo niente
			return;
			
		_dimensione += q;	// La dimensione del set viene per forza incrementata
				
		if (_primo == nullptr){
			_primo = new Elemento(e, q);
		} else {
			Elemento *curr = _primo;
			Elemento *preCurr = nullptr;
		
			while (curr != nullptr) {
				if (_uguale(e, curr->valore)) {
					curr->quantita += q;
					return;
				} else if (_minore(e, curr->valore)) {
					if (curr == _primo) {
						_primo = new Elemento(e, q);
						_primo->next = curr;
						return;
					} else {
						preCurr->next = new Elemento(e, q);
						preCurr->next->next = curr;
						return;
					}
				} else {
					preCurr = curr;
					curr = curr->next;
				}
			}
			preCurr->next = new Elemento(e, q);
		}
	}
	
	/**
		@brief Metodo di supporto per la rimozione di un elemento
		
		Metodo di supporto per la rimozione di un elemento nel multinsieme
		(anche in più di uno)
		
		@param e valore dell'elemento da rimuovere
		@param q quantita di elementi 'e' da rimuovere
	*/
	void rimuoviElemento(const T &e, int q) {
		if (this->eVuota()){
			std::cout << "Il MultiSet e' vuoto, non si puo' togliere alcun elemento" << std::endl;
			return;
		}
		if (!this->contains(e)) {
			std::cout << e << " non e' presente nel MultiSet" << std::endl;
		} else {
			Elemento *curr = _primo;
			Elemento *preCurr = nullptr;
			Elemento *tmp = nullptr;

			while (curr != nullptr) {
				if (_uguale(curr->valore, e)) {
					if (q >= curr->quantita) {
						_dimensione -= curr->quantita;
						if (curr == _primo) {
							tmp = curr->next;
							delete _primo;
							_primo = tmp;
						} else {
							preCurr->next = curr->next;
							delete curr;
						}
					} else {
						curr->quantita -= q;
						_dimensione -= q;
					}
					return;
				} else if (_minore(curr->valore, e)) {
					preCurr = curr;
					curr = curr->next;
				}
			}
		}
	}
	
	/**
		@brief Metodo di supporto all'eliminazione di un multinsieme
		
		Metodo ricorsivo per rimuovere dal multinsieme un elemento e
		e tutti i successivi
	*/
	void eliminaSet(const Elemento *e) {
		if (e != nullptr) {
			_dimensione -= e->quantita;
			eliminaSet(e->next);
			delete e;
			e = nullptr;
		}
	}

public:
	
	/**
		Costruttore di default di un multinsieme
		
		@post _primo == nullptr
		@post dimensione == 0
	*/
	MultiSet() : _primo(nullptr), _dimensione(0) {}
	
	/**
		Costruttore per copia di un multinsieme
		
		@param altro multinsieme da copiare
		
		@throw eccezione di allocazione di memoria
	*/
	MultiSet(const MultiSet &altro) : _primo(nullptr), _dimensione(0) {
		Elemento *tmp = altro._primo;
		
		try {
			while(tmp != nullptr) {
				aggiungiElemento(tmp->valore, tmp->quantita);
				tmp = tmp->next;
			}
		} catch (...) {
			std::cout << "Eccezione nel cctor, il MultiSet è stato svuotato" << std::endl;
			eliminaSet();
			throw;
		}
	}
	
	/**
		Costruttore per copia da un multinsieme di tipo differente dal T
		partendo da una sequenza di dati identificata da due iteratori
		generici
		
		@param begin iteratore di inizio della sequenza
		@param end iteratore di fine della sequenza
		
		@throw eccezione di allocazione della memoria
	*/
	template<typename I>
	MultiSet(I inizio, I fine) : _primo(nullptr), _dimensione(0) {
		try{
			while(inizio != fine) {
				aggiungiElemento(static_cast<T>(*inizio), !inizio);
				++inizio;
			}
		}
		catch(...) {
			std::cout << "Eccezione nel costruttore con MultiSet di tipo diverso, il MultiSet è stato svuotato" << std::endl;
			eliminaSet();
			throw;
		}
	}
	
	/**
		Ridefinizione dell'operatore di assegnamento
		
		@param altro multinsieme da assegnare
		
		@return reference al multinsieme
		
		@throw eccezione di allocazione di memoria
	*/
	MultiSet& operator=(const MultiSet &altro) {
		if (this != &altro) {
			MultiSet tmp(altro);
			std::swap(this->_primo, tmp._primo);
			std::swap(this->_dimensione, tmp._dimensione);
		}
		
		return *this;
	}
	
	/**
		Ridefinizione dell'operatore di uguaglianza per multinsiemi
		
		@param altro multinsieme con cui effettuare il confronto
		
		@return true se i due multinsiemi sono uguali, false altrimenti
	*/
	bool operator==(const MultiSet &altro) const{
		MultiSet::const_iterator a, b, fineA, fineB;
		a = begin();
		b = altro.begin();
		fineA = end();
		fineB = altro.end();
		
		while (a != fineA && b != fineB) {
			if (!(_uguale(*a, *b) && !a == !b)) {
				return false;
			}
			a++;
			b++;			
		}
		if (a != fineA || b != fineB)
			return false;
		return true;
	}
	
	/**
		Distruttore del multinsieme
	*/
	~MultiSet() {
		eliminaSet();
	}
	
	/**
		Metodo che ritorna la quantita di elementi totali presenti nel
		multinsieme
		
		@return numero di elementi nel multinsieme
	*/
	int dimensioneSet() const {
		return _dimensione;
	}
	
	/**
		Metodo che svuota un multinsieme
		
		@post _primo == nullptr
		@post _dimensione == 0
	*/
	void eliminaSet() {
		eliminaSet(_primo);
		_primo = nullptr;
	}
	
	/**
		Metodo che dice se il multinsieme contiene uno specifico elemento
		
		@param e di cui verificare la presenza nel multinsieme
		
		@return true se l'elemento e' presente, false altrimenti
	*/
	bool contains(const T &e) const {
		Elemento *tmp = _primo;
		
		while (tmp != nullptr) {
			if (_uguale(tmp->valore, e))
				return true;
			else if (_minore(e, tmp->valore)) {
				return false;
			} else {
				tmp = tmp->next;
			}
		}
		
		return false;
	}
	
	/**
		Metodo per l'aggiunta di un elemento al multinsieme
		
		@param e elemento da aggiungere al multinsieme
	*/
	void aggiungiElemento(const T &e) {
		aggiungiElemento(e, 1);
	}
	
	/**
		Metodo che dice se il multinsieme e' vuoto
		
		@return true se il multinsieme e' vuotom false altrimenti
	*/
	bool eVuota() const {
		if (_primo == nullptr)
			return true;
		else
			return false;
	}
	
	/**
		Metodo per la rimozione di un elemento dal multinsieme
		
		@param e elemento da togliere dal multinsieme
	*/
	void rimuoviElemento(const T &e) {
		rimuoviElemento(e, 1);
	}
	
	/**
		Metodo che restituisce il numero di occorrenze di un elemento nel
		multinsieme
		
		@param e elemento di cui si vuole conoscere le occorrenze
		
		@return numero di occorrenze dell'elemento cercato
	*/
	int quanti(const T &e) const {
		if (!this->contains(e))
			return 0;
		else {
			Elemento *curr = _primo;
			bool trovato = false;
			while (!trovato) {
				if (_uguale(curr->valore, e))
					return curr->quantita;
				else
					curr = curr->next;
			}
		}
		return 0;
	}
	
	
	
	
	
	/**
		@brief classe che rappresenta un iteratore costante
		
		Classe che rappresenta un iteratore costante di tipo forward
	*/
	class const_iterator {
			
	public:
		typedef T                         value_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

		/**
			Costruttore di default dell'iteratore
		*/
		const_iterator() : ptr(nullptr){
			
		}
		
		/**
			Costruttore per copira dell'iteratore
			
			@param other altro iteratore da assegnare
			
			@return reference all'iteratore
		*/
		const_iterator(const const_iterator &other) : ptr(other.ptr){
			
		}
		
		/**
			Ridefinizione operatore di assegnamento per un iteratore
			
			@param other iteratore
		*/
		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
			return *this;
		}
		
		/**
			Distruttore dell'iteratore
		*/
		~const_iterator() {}
		
		/**
			Ridefinizione operatore *
			
			@return reference al valore dell'elemento puntato
			dall'iteratore
		*/
		reference operator*() const {
			return ptr->valore;
		}
		
		/**
			Ridefinizione operatore ->
			
			@return puntatore al valore dell'elemento puntato
			dall'iteratore
		*/
		pointer operator->() const {
			return &(ptr->valore);
		}
		
		/**
			Ridefinizione operatore ++ postfisso
			
			@return iteratore allo stesso elemento di prima della chiamata 
		*/
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			ptr = ptr->next;
			return tmp;
		}
		
		/**
			Ridefinizione operatore ++ prefisso
			
			@return iteratore all'elemento successivo
		*/
		const_iterator& operator++() {
			ptr = ptr->next;
			return *this;
		}
		
		/**
			Ridefinizione operatore ==
			
			@param other altro iteratore con cui fare il confronto
			
			@return true se gli iteratori sono uguali, false altrimenti
		*/
		bool operator==(const const_iterator &other) const {
			return ptr == other.ptr;
		}
		
		/**
			Ridefinizione operatore !=
			
			@param other altro iteratore con cui fare il confronto
			
			@return true se gli iteratori sono diversi, false altrimenti
		*/
		bool operator!=(const const_iterator &other) const {
			return ptr != other.ptr;
		}
		
		/**
			Ridefinizione operatore !
			Utilizzato per sapere quanti sono gli elementi di ugual valore
			a quello puntato dall'iteratore
			
			@return numero di occorrenze dell'elemento puntato
		*/
		int operator!() const {
			return ptr->quantita;
		}

	private:
	
		const Elemento *ptr;	///< Puntatore ad un elemento costante
		
		friend class MultiSet;
		
		/**
			Costruttore secondario di un iteratore
			
			@param e puntatore all'elemento che si vuol far puntare
			all'iteratore
		*/
		const_iterator(const Elemento *e) : ptr(e) {}
				
	}; // fine classe const_iterator
	
	/**
		Metodo che resituisce un iteratore costante al primo elemento
		del multinsieme
		
		@return iteratore che punta al primo elemento
	*/
	const_iterator begin() const {
		return const_iterator(_primo);
	}
	
	/**
		Metodo che resituisce un iteratore costante alla fine del
		multinsieme
		
		@return iteratore che punta alla fine del multinsieme
	*/
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	
}; //Fine classe MultiSet





/**
	Ridefinizione dell'operatore di stream per la stampa del contenuto del MultiSet
	
	@param os stream di output
	@param s multinsieme da stampare
	
	@return reference allo stream di output
*/
template<typename T, typename M, typename U>
std::ostream& operator<<(std::ostream &os, const MultiSet<T, M, U> &s) {
	
	typename MultiSet<T, M, U>::const_iterator i, ie;
	
	i = s.begin();
	ie = s.end();
	
	if (i == ie)
		std::cout << "Il Multiset e' vuoto";
	
	while (i != ie) {
		os << "<" << *i << ", " << !i << ">";
		++i;
		if (i != ie)
			os << ", ";
	}
	
	return os;
}







#endif
