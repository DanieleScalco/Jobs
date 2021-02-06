-- 1. Selezionare il nome della regione seguito dal numero di abitanti, chiamando tale quantità
-- “popolazione”. Ordinare i risultati in ordine decrescente di popolazione.
SELECT r.nome, SUM(c.popolazione) popolazione
FROM regione r
	JOIN provincia p ON r.codice_istat = p.codice_istat_regione
    JOIN comune c ON c.codice_istat_provincia = p.codice_istat
GROUP BY r.nome
ORDER BY popolazione DESC;


-- 2. Selezionare il nome della regione seguito dai casi positivi in tutta la regione al 31 maggio,
-- chiamando quest’ultima quantità “casi_covid_al_31_maggio”. Ordinare il risultato in ordine decrescente
-- di casi positivi.
SELECT r.nome, SUM(c.casi_positivi_totali) casi_covid_al_31_maggio
FROM regione r
	JOIN provincia p ON r.codice_istat = p.codice_istat_regione 
    JOIN casi_covid c ON c.codice_istat_provincia = p.codice_istat
WHERE c.data = "2020-05-31"
GROUP BY r.nome
ORDER BY casi_covid_al_31_maggio DESC;

-- 3. Selezionare il nome della regione e il numero di casi positivi totali diviso il numero di abitanti
-- della regione moltiplicato per 100 (ovvero la percentuale di positivi) al 31 maggio, solo per le regioni
-- con una percentuale di positivi superiore allo 0.5%. Chiamare la quantità da calcolare
-- “percentuale_positivi_al_31_maggio” e ordinare il risultato in ordine decrescente di percentuale.
SELECT regione.nome, ((casi_covid_al_31_maggio / popolazione) * 100) AS percentuale_positivi_al_31_maggio
FROM	(SELECT r.nome, SUM(c.popolazione) popolazione
		FROM regione r
			JOIN provincia p ON r.codice_istat = p.codice_istat_regione
			JOIN comune c ON c.codice_istat_provincia = p.codice_istat
		GROUP BY r.nome) AS regione
        JOIN
		(SELECT r.nome, SUM(c.casi_positivi_totali) casi_covid_al_31_maggio
		FROM regione r
			JOIN provincia p ON r.codice_istat = p.codice_istat_regione 
			JOIN casi_covid c ON c.codice_istat_provincia = p.codice_istat
		WHERE c.data = "2020-05-31"
		GROUP BY r.nome) AS casi ON casi.nome = regione.nome
WHERE ((casi_covid_al_31_maggio / popolazione) * 100) > 0.5
GROUP BY regione.nome
ORDER BY percentuale_positivi_al_31_maggio DESC;

-- 4. Per ogni regione (rappresentata solo dal nome), contare il numero di province e di comuni,
-- chiamando rispettivamente questi campi “numero_province” e “numero_comuni”.
SELECT r.nome, COUNT(*) province, SUM(comuni) comuni
	FROM regione r
		JOIN provincia p ON r.codice_istat = p.codice_istat_regione
		JOIN	(SELECT p.nome, COUNT(*) comuni
				FROM provincia p
					JOIN comune c ON c.codice_istat_provincia = p.codice_istat
				GROUP BY p.nome) AS prov_comuni ON prov_comuni.nome = p.nome
	GROUP BY r.nome;

-- 5. Selezionare, per ogni provincia (rappresentata da codice_istat, nome e abbreviazione), il numero
-- di acquisizioni totali fatte (una acquisizione = un record in “casi_covid”), indicando questa quantità
-- con “numero_acquisizioni”.
SELECT p.codice_istat, p.nome, p.abbreviazione, COUNT(*) numero_acquisizione
FROM provincia p
	JOIN casi_covid c ON p.codice_istat = c.codice_istat_provincia
GROUP BY p.codice_istat;