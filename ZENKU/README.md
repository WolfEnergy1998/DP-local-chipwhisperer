# ZENKU TODO list for week:

## Week 7. TODO:
   - **List of todo for weekend and tuesday**:
     1. [X] Pridaj vracanie secret value a ich spracovanie/ulozenie pre danu vzorku v ramci firmwaru a v ramci campturing funkcie.
     2. [X] Na zaklade vratenych secret values pri vykresleni plotov korelacie, vykresli i korelaciu spravnej hodnoty, inou farbou.
     3. [X] Uprav funkciu pre identifikaciu correct correlation nasledovne: 
        1. [X] Aby brala hodnoty z vacsieho rozsahu od globalneho maxima/staci posielat specificku treshold value
        2. [X] Aby sa vykonavala 2. extrakcia lokalnych maxim <--- je potrebne aby  si vyhodily 0 hodnoty v korelacii, a zmensila sa dlzka korelacneho vektora, ale zachovali sa indx. z povodneho vektora
     4. [ ] Skus sa pozriet na problem korelacie pre 0-value secret.