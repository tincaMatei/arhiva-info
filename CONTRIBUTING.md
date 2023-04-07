# Contribuții

Există două moduri principale de a face contribuții. Fie varianta mai complicată, dar care ar fi recomandată, fie varianta mai ușoară.
O să prezint varianta mai ușoară mai întâi.

Pentru început, trebuie adunate toate lucrurile legate de o problemă descrise [aici](https://github.com/tincaMatei/arhiva-info#format-arhiv%C4%83). 
Dacă nu s-a găsit ceva, de exemplu teste, pune un fișier numit `missing.md` (atenție să fie litere mici) în care explici situația. Dacă ceva este greșit la
ce ai, atunci pune un fișier `broken.md` în care, în mod similar, explici situația.

Am rugămintea ca pentru toate lucrurile să se găsească variante cât mai aproape de original. De exemplu, aș prefera pentru teste să am testele care s-au folosit la olimpiadă pe CMS. Dacă nu există acestea, atunci și testele descărcate de pe vreun Online Judge sunt bune. Pe scurt, căutați mai întâi varianta originală, iar dacă nu ați găsit nimic, folosiți alternative.

Detalii importante care se află și pe formularul din issue-uri/pull request-uri:

* Fiecare problemă are patru directoare: `enunt`, `teste`, `editorial` și `surse`. M-am asigurat că aceste directoare nu conțin diacritice, sunt formate doar din litere mici și sunt scrise exact la fel cum sunt puse la alte probleme.
* Toate directoarele din problemă conțin măcar un fișier. Dacă nu am găsit ceva, de exemplu `teste`, atunci am pus un fișier `missing.md` în care explic situația și eventual niște alternative. Dacă există niște teste, dar nu există toate lucrurile necesare, sau ceva nu este corect, am pus fișierul `broken.md` în care explic ce este stricat.
* M-am asigurat că testele în total nu depășesc 50 Mb. Dacă depășesc chiar și cu o arhivă, atunci am pus un fișier "broken.md" în care să pun un link la teste.
* Fișierele `broken.md` sau `missing.md` sunt formate din litere mici (dacă există).
* Nu am adăugat niciun fișier în plus, doar fiecare problemă și ce este nevoie pentru fiecare.
* Am adăugat, dacă există, un fișier care să conțină linkuri pe alte online judge-uri cu problema.
* În fișierul `teste`, am adăugat într-un `README.md` regexul folosit în concurs (pentru punctarea testelor). Dacă nu am găsit, atunci am pus un fișier `broken.md`.
* În fișierul `enunt`, am adăugat într-un `README.md` limita de timp și de memorie pe problemă. Dacă nu am găsit, atunci am pus un fișier `broken.md`.

## Varianta cu pull request

1. Fork-uiește repository-ul.
2. Adaugă fișierele de la probleme în repository.
3. Creează un pull request folosind template-ul de creat o problemă.
4. Completează datele din pull request.
5. Așteaptă. Trebuie să verific manual că totul este în regulă.

## Varianta prin issue-uri

Dacă nu vrei să descarci repository-ul din diferite motive, atunci varianta asta este mai ușoară. Practic, doar pui un link cu ce am eu nevoie și de acolo fac eu pull request-ul.

1. Pune fișierele fie într-un zip, fie pe o platformă de împărtășit fișiere (ex. Google Drive).
2. Creează un issue folosind template-ul de adăugat probleme.
3. Completează datele din issue.
4. Așteaptă. Trebuie să verific că totul este în regulă.
