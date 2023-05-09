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

De asemenea, fiecare problemă mai poate conține și un fișier `mirrors.json` unde se află linkuri
pe platforme unde se pot rezolva problemele. Acesta va avea structura următoare:

```
{
    "InfoArena": "https://infoarena.ro/problema/scara5",
    "PBInfo": "https://www.pbinfo.ro/probleme/3049/scara2"
}
```

# README.md

Fiecare fișier poate avea un README.md. Scriptul de mai sus va modifica acest fișier și va adăuga
un rezumat la sfârșit cu ce chestii care lipsesc. Este foarte important să nu se modifice nimic la partea
generată. Dacă pentru un README încă nu s-a generat nimic, să fie două "\n"-uri la sfârșit, altfel
README-ul va arăta urât.

# Generated Summary

# arhiva-info

## lot

### 2023

#### ziua-1

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| apa | Ok | Ok | Gol | Ok |  |
| benzi | Ok | Incomplet | Gol | Ok |  |
| sirdacic | Ok | Ok | Gol | Ok |  |

## oji

### 2022

#### 10

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| circular | Ok | Ok | Ok | Gol | [pbinfo](https://www.pbinfo.ro/probleme/4097/circular1) |
| pulsar | Ok | Ok | Ok | Gol | [pbinfo](https://www.pbinfo.ro/probleme/4098/pulsar) |
| transport | Ok | Incomplet | Ok | Gol | [pbinfo](https://www.pbinfo.ro/probleme/4099/transport) |

#### 11-12

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| dulciuri | Ok | Ok | Ok | Gol | [Kilonova](https://kilonova.ro/problems/133), [pbinfo](https://www.pbinfo.ro/probleme/4113/dulciuri) |
| investitie | Ok | Incomplet | Ok | Gol | [Kilonova](https://kilonova.ro/problems/134), [pbinfo](https://www.pbinfo.ro/probleme/4115/investitie) |
| superhedgy | Ok | Ok | Ok | Gol | [Kilonova](https://kilonova.ro/problems/135), [pbinfo](https://www.pbinfo.ro/probleme/4116/superhedgy) |

#### 9

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| balba | Ok | Ok | Ok | Gol | [pbinfo](https://www.pbinfo.ro/probleme/4096/balba) |
| oneout | Ok | Incomplet | Ok | Gol | [pbinfo](https://www.pbinfo.ro/probleme/4094/oneout) |
| pergament | Ok | Ok | Ok | Gol | [pbinfo](https://www.pbinfo.ro/probleme/4095/pergament) |

### 2023

#### 10

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| arhitect | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/504), [pbinfo](https://www.pbinfo.ro/probleme/4392/arhitect) |
| bingo | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/503), [pbinfo](https://www.pbinfo.ro/probleme/4390/bingo) |
| fotbal | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/505), [pbinfo](https://www.pbinfo.ro/probleme/4394/fotbal2) |

#### 11-12

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| parcare | Ok | Incomplet | Ok | Gol | [Kilonova](https://kilonova.ro/problems/500), [pbinfo](https://www.pbinfo.ro/probleme/4413/parcare2) |
| turcane | Ok | Ok | Ok | Gol | [Kilonova](https://kilonova.ro/problems/501), [pbinfo](https://www.pbinfo.ro/probleme/4410/turcane) |
| veri | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/502), [pbinfo](https://www.pbinfo.ro/probleme/4411/veri) |

#### 9

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| cufere | Ok | Ok | Ok | Gol | [Kilonova](https://kilonova.ro/problems/508), [pbinfo](https://www.pbinfo.ro/probleme/4393/cufere) |
| fibosnek | Ok | Incomplet | Ok | Gol | [Kilonova](https://kilonova.ro/problems/506), [pbinfo](https://www.pbinfo.ro/probleme/4406/fibosnek) |
| partitura | Ok | Ok | Ok | Gol | [Kilonova](https://kilonova.ro/problems/507), [pbinfo](https://www.pbinfo.ro/probleme/4407/partitura) |

## oni

### 2019

#### 10

##### ziua-1

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| artifact | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/artifact), [pbinfo](https://www.pbinfo.ro/probleme/3048/artifact) |
| scara | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/scara5), [pbinfo](https://www.pbinfo.ro/probleme/3049/scara2) |
| walle | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/walle), [pbinfo](https://www.pbinfo.ro/probleme/3056/walle) |

##### ziua-2

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| nozero | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/nozero), [pbinfo](https://www.pbinfo.ro/probleme/3052/nozero) |
| pericol | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/pericol), [pbinfo](https://www.pbinfo.ro/probleme/3055/pericol) |
| vip | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/vip), [pbinfo](https://www.pbinfo.ro/probleme/3058/vip) |

#### 11-12

##### ziua-1

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| lexicografic | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/lexicografic), [Kilonova](https://kilonova.ro/problems/7), [pbinfo](https://www.pbinfo.ro/probleme/3059/lexicografic) |
| oracol | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/oracol), [Kilonova](https://kilonova.ro/problems/10), [pbinfo](https://www.pbinfo.ro/probleme/3061/oracol) |
| treeGCD | Ok | Ok | Ok | Gol | [Infoarena](https://infoarena.ro/problema/treegcd), [Kilonova](https://kilonova.ro/problems/11) |

##### ziua-2

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| compact | Ok | Ok | Ok | Gol | [Infoarena](https://infoarena.ro/problema/compact3), [Kilonova](https://kilonova.ro/problems/12) |
| hipersimetrie | Ok | Ok | Ok | Gol | [Infoarena](https://infoarena.ro/problema/hipersimetrie), [Kilonova](https://kilonova.ro/problems/13) |
| linegraph | Ok | Ok | Ok | Gol | [Infoarena](https://infoarena.ro/problema/linegraph), [Kilonova](https://kilonova.ro/problems/14) |

#### 9

##### ziua-1

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| amat | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/amat), [pbinfo](https://www.pbinfo.ro/probleme/3042/amat) |
| comun | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/comun), [pbinfo](https://www.pbinfo.ro/probleme/3044/comun1) |
| pro3 | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/pro3), [pbinfo](https://www.pbinfo.ro/probleme/3045/pro3) |

##### ziua-2

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| cub | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/cub5), [pbinfo](https://www.pbinfo.ro/probleme/3043/cub3) |
| fibofrac | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/fibofrac), [pbinfo](https://www.pbinfo.ro/probleme/3047/fibofrac) |
| telefon | Ok | Ok | Ok | Ok | [Infoarena](https://infoarena.ro/problema/telefon3), [pbinfo](https://www.pbinfo.ro/probleme/3046/telefon) |

#### baraj

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| anarhie | Ok | Ok | Gol | Gol | [Infoarena](https://infoarena.ro/problema/anarhie), [Kilonova](https://kilonova.ro/problems/409) |
| dag | Ok | Ok | Gol | Gol | [Infoarena](https://infoarena.ro/problema/dag), [Kilonova](https://kilonova.ro/problems/410) |
| takara | Ok | Ok | Gol | Gol | [Infoarena](https://infoarena.ro/problema/takara), [Kilonova](https://kilonova.ro/problems/411) |

### 2023

#### 10

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| arcade | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/535) |
| comun | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/536) |
| matrice | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/537) |

#### 11-12

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| biom | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/532) |
| keidei | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/533) |
| xidartros | Ok | Incomplet | Ok | Ok | [Kilonova](https://kilonova.ro/problems/534) |

#### 9

| Nume | Enunt | Teste | Editorial | Surse | Mirrors |
| ---- | ----- | ----- | --------- | ----- | ------- |
| bolovani | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/539) |
| nisip | Ok | Incomplet | Ok | Ok | [Kilonova](https://kilonova.ro/problems/540) |
| pietricele | Ok | Ok | Ok | Ok | [Kilonova](https://kilonova.ro/problems/538) |
