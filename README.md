# Arhiva de info

O arhivă care sper să devină cât se poate de completă cu probleme din trecut de la olimpiade 
de info.

Concursurile la care mă gândeam că trebuie track-uite ar fi:

* OJI / ONI
* Loturi
* BOI
* CEOI
* IATI

Pentru a contribui, vezi [aici](CONTRIBUTING.md). Orice issue este bine-venit. La fel și pull request-urile, dar citește secțiunea de contribuții mai întâi.

# Utilizare arhivă

Pe GitHub nu poți să descarci subdirectoare particulare. Pentru asta, poți folosi [download-directory](https://download-directory.github.io/).

# Format arhivă

O problemă trebuie să aibă patru directoare: enunt, teste, editorial, surse. Foarte important să
fie cu litere mici toate. Opțional, poate exista și câte un README.md ca să poate fi citit ușor. De asemenea pentru a merge cu 
[scriptul](https://github.com/tincaMatei/arhiva-info-summary) de aici care se uită peste tot și face un rezumat este să existe 
o linie goală la sfârșitul readme-ului ca să nu arate urât formatarea.

Dacă pentru o problemă nu s-a găsit ceva, de exemplu teste, sau ceva, puneți un fișier `missing.md`. Dacă ați găsit ceva, dar
nu este complet sau este ceva stricat la structură, atunci puneți un fișier `broken.md`.
În mod similar, fișierele trebuie să aibă litere mici, deoarece scriptul este case-sensitive.

Pentru o colecție mai mare de probleme, se pot pune oricum, dar ar fi bine să existe o ordine. Pentru
alte concursuri nu știu cum ar fi mai bine făcut, dar pentru OJI/ONI, structura arată ceva de genul:

```
ONI/
├─ 2019/
│  ├─ 9/
│  ├─ 10/
│  │  ├─ ziua-1/
│  │  │  ├─ scara/
│  │  │  │  ├─ enunt/
│  │  │  │  ├─ teste/
│  │  │  │  ├─ editorial/
│  │  │  │  ├─ surse/
│  │  │  ├─ walle/
│  │  │  ├─ artifact/
│  │  ├─ ziua-2/
│  ├─ 11-12/
│  ├─ baraj/
```

Nu mi-e 100% clar cum ar trebui făcut cu problemele interactive. Cred ca cel mai bine ar fi ca în 
teste să se pună și interactorul. Dacă nu există interactor, se pune imediat un "broken.md".

O altă chestie despre conținut, ar fi bine să fie cât mai aproape de realitate. De exemplu, 
la niște probleme am vrut să le iau de pe Infoarena, dar am găsit până la urmă testele originale.
Dacă nu se găsește nimic pentru un concurs, atunci vom pune niște variante alternative.

Pentru problemele care au teste gigantice, probabil nu le voi pune pe GitHub, mai bine punem un 
readme în fișierul cu teste care să aibă un link care duce la teste. De preferat, linkul acela 
ar trebui să fie unul care să nu crape.

# README.md

Fiecare fișier poate avea un README.md. Scriptul de mai sus va modifica acest fișier și va adăuga
un rezumat la sfârșit cu ce chestii care lipsesc. Este foarte important să nu se modifice nimic la partea
generată. Dacă pentru un README încă nu s-a generat nimic, să fie două "\n"-uri la sfârșit, altfel
README-ul va arăta urât.

# Generated Summary

# arhiva-info

## oji

### 2022

#### 10

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| circular | Ok | Ok | Ok | Gol |
| pulsar | Ok | Ok | Ok | Gol |
| transport | Ok | Incomplet | Ok | Gol |

#### 11-12

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| dulciuri | Ok | Ok | Ok | Gol |
| investitie | Ok | Incomplet | Ok | Gol |
| superhedgy | Ok | Ok | Ok | Gol |

#### 9

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| balba | Ok | Ok | Ok | Gol |
| oneout | Ok | Incomplet | Ok | Gol |
| pergament | Ok | Ok | Ok | Gol |

### 2023

#### 10

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| arhitect | Ok | Ok | Ok | Gol |
| bingo | Ok | Ok | Ok | Gol |
| fotbal | Ok | Ok | Ok | Gol |

#### 11-12

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| parcare | Ok | Incomplet | Ok | Gol |
| turcane | Ok | Ok | Ok | Gol |
| veri | Ok | Ok | Ok | Gol |

#### 9

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| cufere | Ok | Ok | Ok | Gol |
| fibosnek | Ok | Incomplet | Ok | Gol |
| partitura | Ok | Ok | Ok | Gol |

## oni

### 2019

#### 10

##### ziua-1

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| artifact | Ok | Ok | Ok | Ok |
| scara | Ok | Ok | Ok | Ok |
| walle | Ok | Ok | Ok | Ok |

##### ziua-2

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| nozero | Ok | Ok | Ok | Ok |
| pericol | Ok | Ok | Ok | Ok |
| vip | Ok | Ok | Ok | Ok |

#### 11-12

##### ziua-1

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| lexicografic | Ok | Ok | Ok | Ok |
| oracol | Ok | Ok | Ok | Ok |
| treeGCD | Ok | Ok | Ok | Gol |

##### ziua-2

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| compact | Ok | Ok | Ok | Gol |
| hipersimetrie | Ok | Ok | Ok | Gol |
| linegraph | Ok | Ok | Ok | Gol |

#### 9

##### ziua-1

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| amat | Ok | Ok | Ok | Ok |
| comun | Ok | Ok | Ok | Ok |
| pro3 | Ok | Ok | Ok | Ok |

##### ziua-2

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| cub | Ok | Ok | Ok | Ok |
| fibofrac | Ok | Ok | Ok | Ok |
| telefon | Ok | Ok | Ok | Ok |

#### baraj

| Nume | Enunt | Teste | Editorial | Surse |
| ---- | ----- | ----- | --------- | ----- |
| anarhie | Ok | Ok | Gol | Gol |
| dag | Ok | Ok | Gol | Gol |
| takara | Ok | Ok | Gol | Gol |
