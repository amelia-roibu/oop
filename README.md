# Geography Quizzes – Jocuri educative de geografie

Acest proiect este o suită de mini-jocuri educative pe tema geografiei lumii.
Jocurile testează cunoștințele despre capitale, vecinătăți între țări, emisfere, continente și multe altele.
## Jocuri disponibile

1. **Countryle** – ghicește țara misterioasă pe baza indiciilor geografice (în stil Countryle[*](https://countryle.com/)).
2. **Guess the Capital** – numește cât mai multe capitale corecte într-o limită de timp, pe baza unor țări date aleatoriu.
3. **Guess the Country** – numește cât mai multe țări corecte într-o limită de timp, pe baza capitalelor lor date aleatoriu.
4. **Shortest Path** – construiește drumul geografic cel mai scurt între două țări aleatorii.
5. **Info Point** – explorează țări și află informații utile într-un tur virtual relaxant.

## Cum se folosește

La rularea programului, vei fi întâmpinat de un meniu în care poți alege unul dintre cele 5 jocuri. Niciun meniu nu este case-sensitive.

Instrucțiunile pentru fiecare joc apar automat. Poți scrie `renunt` în orice moment pentru a ieși dintr-un joc. Jocurile de viteză oferă și posibilitatea de a da `pas` dacă te blochezi la o întrebare.

Scorurile sunt calculate diferit în funcție de joc:
- cât mai puține încercări până la răspunsul corect în Countryle
- viteză și răspunsuri corecte pentru quiz-uri (+ penalizări) în Guess the Capital și Guess the Country
- lungime optimă a drumului dintre cele două țări date ca prompt în Shortest Path Game
- număr de țări vizualizate în Info Point

| Laborant  | Link template                                |
|-----------|----------------------------------------------|
| Dragoș B  | https://github.com/Ionnier/oop-template      |

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.

## Cerințe obligatorii pe care le-am avut de respectat în cadrul proiectului:

  - programul a fost scris în C++
  - programul are un meniu interactiv
  - programul nu are erori de compilare
  - fară variabile globale
  - datele membre private (sau protected)
  - GitHub Actions trecute
  - commit-uri pe Git adecvate si punctuale
  - nu există folosiri ale funcționalităților limbajului fără sens
  - nu există folosiri ale funcționlităților limbajului cu scopul de a încălca "legal" o altă regulă
      - folosirea excesivă a claselor friend
      - folosirea excesviă a elementelor statice
  - implementarea este separata de definiție

## Cerințe
1. [x] definirea a minim **2-3 ierarhii de clase** care sa interactioneze in cadrul temei alese (fie prin compunere, agregare sau doar sa apeleze metodele celeilalte intr-un mod logic) (6p)
  - minim o clasa cu:
    - [x] constructori de inițializare [*](https://github.com/Ionnier/poo/tree/main/labs/L02#crearea-obiectelor)
    - [x] constructor supraîncărcat [*](https://github.com/Ionnier/poo/tree/main/labs/L02#supra%C3%AEnc%C4%83rcarea-func%C8%9Biilor)
    - [x] constructori de copiere [*](https://github.com/Ionnier/poo/tree/main/labs/L02#crearea-obiectelor)
    - [x] `operator=` de copiere [*](https://github.com/Ionnier/poo/tree/main/labs/L02#supra%C3%AEnc%C4%83rcarea-operatorilor)
    - [x] destructor [*](https://github.com/Ionnier/poo/tree/main/labs/L02#crearea-obiectelor)
    - [x] `operator<<` pentru afișare (std::ostream) [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L123)
    - [x] `operator>>` pentru citire (std::istream) [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L128)
    - [x] alt operator supraîncărcat ca funcție membră [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L32)
    - [x] alt operator supraîncărcat ca funcție non-membră [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L39) - nu neaparat ca friend
  - in derivate
      - [x] implementarea funcționalităților alese prin [upcast](https://github.com/Ionnier/poo/tree/main/labs/L04#solu%C8%9Bie-func%C8%9Bii-virtuale-late-binding) și [downcast](https://github.com/Ionnier/poo/tree/main/labs/L04#smarter-downcast-dynamic-cast)
        - aceasta va fi făcută prin **2-3** metode specifice temei alese
        - funcțiile pentru citire / afișare sau destructorul nu sunt incluse deși o să trebuiască să le implementați 
      - [x] apelarea constructorului din clasa de bază din [constructori din derivate](https://github.com/Ionnier/poo/tree/main/labs/L04#comportamentul-constructorului-la-derivare)
      - [x] suprascris [cc](https://github.com/Ionnier/poo/tree/main/labs/L04#comportamentul-constructorului-de-copiere-la-derivare)/op= pentru copieri/atribuiri corecte
      - [x] destructor [virtual](https://github.com/Ionnier/poo/tree/main/labs/L04#solu%C8%9Bie-func%C8%9Bii-virtuale-late-binding)
  - pentru celelalte clase se va defini doar ce e nevoie
  - minim o ierarhie mai dezvoltata (cu 2-3 clase dintr-o clasa de baza)
  - ierarhie de clasa se considera si daca exista doar o clasa de bază însă care nu moștenește dintr-o clasă din altă ierarhie
  - cât mai multe `const` [(0.25p)](https://github.com/Ionnier/poo/tree/main/labs/L04#reminder-const-everywhere)
  - funcții și atribute `static` (în clase) [0.5p](https://github.com/Ionnier/poo/tree/main/labs/L04#static)
    - [x] 1+ atribute statice non-triviale 
    - [x] 1+ funcții statice non-triviale 
  - excepții [0.5p](https://github.com/Ionnier/poo/tree/main/labs/L04#exception-handling)
    - porniți de la `std::exception`
    - ilustrați propagarea excepțiilor
    - ilustrati upcasting-ul în blocurile catch
    - minim folosit într-un loc în care tratarea erorilor în modurile clasice este mai dificilă
  - folosirea unei clase abstracte [(0.25p)](https://github.com/Ionnier/poo/tree/main/labs/L04#clase-abstracte)
  - clase template
    - [x] crearea unei clase template [(1p)](https://github.com/Ionnier/poo/tree/main/labs/L08)
    - [x] 2 instanțieri ale acestei clase (0.5p)
  - STL [(0.25p)](https://github.com/Ionnier/poo/tree/main/labs/L07#stl)
    - [x] utilizarea a două structuri (containere) diferite (vector, list, map, pair, unordered set)
    - [x] utilizarea a unui algoritm cu funcție lambda (transform)
  - Design Patterns [(0.75p)](https://github.com/Ionnier/poo/tree/main/labs/L08)
    - [x] utilizarea a două șabloane de proiectare

### Observații

* Pot exista depunctări până la 2p pentru diferite aspecte precum:
  - memory leak-uri
  - nefolosirea destructorului virtual la nevoie
  - abuzarea de diferite concepte (toate funcțiile declarate virtual)
  - apelarea de funcții virtual în constructori

* În general, acestea sunt prezente în [CppCoreGuideline](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md), dar nu e nevoie să parcurgeți documentul, doar să scrieți codul suficient de organizat

* folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.
