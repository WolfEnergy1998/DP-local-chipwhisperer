# ZENKU TODO list for week:

## Week 6. TODO:
   - **List of TODO for weekend and tuesday**:
     1. [X] Pridaj vracanie secret value a ich spracovanie/ulozenie pre danu vzorku v ramci firmwaru a v ramci campturing funkcie.
     2. [X] Na zaklade vratenych secret values pri vykresleni plotov korelacie, vykresli i korelaciu spravnej hodnoty, inou farbou.
     3. [X] Uprav funkciu pre identifikaciu correct correlation nasledovne: 
        1. [X] Aby brala hodnoty z vacsieho rozsahu od globalneho maxima/staci posielat specificku treshold value
        2. [X] Aby sa vykonavala 2. extrakcia lokalnych maxim <--- je potrebne aby  si vyhodily 0 hodnoty v korelacii, a zmensila sa dlzka korelacneho vektora, ale zachovali sa indx. z povodneho vektora
     4. [ ] Skus sa pozriet na problem korelacie pre 0-value secret. <-- No progress

## Week 7. TODO:
   - **List of TODO for weekend and tuesday**:
     1. [X] Expand set of possible weight to whole subset of 8-bit values eg. {0,..., 256}
        - We have tried to expand the set on which we do CPA. But we met with quite un/expected proble, and that is staci-property of previous local max extraction
        It needs to be  fitted to current setup of firmware for it  to work, as with many multiplications, we are meeting ghost peaks, no peaks (0, and few values).
        - And overall the current mechanism is quite unstable/unfitted. I have added 2 more options for local maxims extractions, but ... so far none has shown  great promise.
     2. [X] Try to work on problem of 0 weight, well at least to extent that you have several ideas about the problem 
        - <--- None found so far, when value is 0, then result of 
        multiplication is 0 also,  (**in ANN we can expand formula on which we create leakage model, to include also sumation of previous value**, but here it is non-relevant)
        In essence, when the secret value is 0 mult is also 0, even thought random value may be all the time different, there is no variation to speak of and as such
        no correlation to look for. Only solution which comes to mind about this is expand that formula, but this does not take into account that the 0-secret value is 
        first secret value, if this is true, then addition is moot.
     3. [ ] (Optional) check the traces with those 4 derivated graphs, and make list of their characteristics as compared to the correlation map of 2deg. loc. maxs
         - <-- Paused
  - Notes/Problems: 
    -  For some reason the capturing didnt stop at low(), but continued this is verified with pictures without800_tmp_corr with_sendback_800_tmp_corr, where we can see
    a difference, even thought all the setting were same, but one detail, in without... the fulling buffer with secret values was commented, and with... uncommented. 
    This was solved by fulling buffer on start of the function. But even then it is possible risk (and quite hight as the device/program doesnt act as it should)
    - Value 1 is also problematic, it shows quite high correlation on many places: (vector for 0-option of local maxim extraction) [1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 4, 1, 5, 1, 1, 7, 1, 8, 9, 1, 1, 10, 1, 11, 12, 1, 1, 13, 1, 14, 15, 1, 1, 1, 1, 17, 1, 1, 18, 1, 1, 19, 1, 1, 20, 1, 1, 21, 1, 1, 22, 1, 1, 23, 1, 1, 24, 1, 1, 25, 1, 1, 26, 1, 1, 27, 1, 1, 28, 1, 1, 29, 1, 1, 30, 1, 1, 31, 1, 1, 1, 1, 33, 1, 1, 34, 1, 1, 35, 1, 1, 1, 1, 37, 1, 1, 38, 1, 1, 39, 1, 1, 40, 1, 1, 41, 1, 1, 42, 1, 1, 43, 1, 1, 44, 1, 1, 45, 1, 1, 46, 1, 1, 47, 1, 1, 1, 1, 49, 1]
## Week 8. Verification of Correlation function:
  - **List of TODO for week 8th weekend and next tuesday**
    1. [X] Create additional firmware for ANN, where the ann will be basic neuro, with X multiplications <-- It works, well at least target correlation is about >0.9
    2. [X] Try to verify effectivnes/correctnes off correlation algorithm <-- tried for 2 0th weight values, it worked
    3. [ ] If results from previous point are inconclusive, create virual traces where you will generate signa
(in certain time samples, add HW of multiplication <-- normalized), add noise <-- normalized

## 9th week  
  1. [X] verify correlation function, on simulated data traces <-- Mixed results, for simulated traces the existing correlations methods proved more effective, while for the ones measured from ANN on CW, my method had more visible results.
     2. There is a need to apply k-fold cross validation, and p-value in my method, it had positive results in existing methods
  2. [X] try out several methods of correlation, such as scipy.correlation ...
  3. [ ] try methods such as k-fold cross correlation, or p-value, for deleting ghost peaks and false peaks

## 10th week 
  0. [X] Check/compare corr. results of ANN traces, on mine and np/scipy.pearsonr, try out p_value filtering. <--- For mine implementation of p_value, the result was visible, but in astronomicaly small p_values (TODO NEEDS TO ASK???)
  1. [X] Check quantization, if it is rightly done. <--- Quantization was verified and there were done small modifications, main area of modification needs/will be done in analysis. Because the quantization only, limits the interval of  secret key's values and input values, but  not the intemediate values.
  2. [X] If point 2. has an effect, do extraction <--- IT IS MESS, logically it should work, but it is unbelievable volatile
  3. [X] If point 2. has no effect, try debug the code, in C interpreter and check bit values of variables <-- Bit values checked, changed all int8_t to uint8_t and changed relu function mechanism, to [if z > 127 a = 0 else a = z]
       --> Still the result are confusing, needs additional debugging at wendsday.
     - 3.12.2024: - Po vypnuti Optimalizacie u ANN, vysledne korelacne matice uz boli vyerohodnejsie, dalej my ostava odskusat, ci problem je v metode vypoctu korelacie, alebo v pretipovani na uintX_t


## 12th week
 1. [X] Try old, pre quantization efforts ANN, and try on it current methods of CPA
   - TODO: just build old one and run it throught basic treatment
   - Old one has quite visible correlation peaks, while also more expansive network. The peaks are quite close to each other sample wise.
   - For the newest, the correlations for right weight are mostly visible in HW(int), others not so much, this is mainly beacause the correlation of each right weight are peaks of its domain, but their distance is quite significant, in sense of correlation height.
   - Another observed characteristic was that HW(int) is predisposited for non-parite weight, while the parite-ones are missing from the results.
2. [X] Try inbuild methods of Pearson Correlation, +p-value usage, and optionaly refresh efforts for weight extraction
	- TODO: use it one the one from previous point, and also with newest one iteration of ANN
3. [X] Try to continue efforts of SPA, by using diff_wave, on different architectures
	- TODO: just use it on the ones wiht better result from previous points, also try to set greater number of sampled points, or set decimate to 2>
    - SPA was succesfull, wherein the Relu for each hidden_neuron was seen, and sig for each output_neuron was seen
4. [ ] At last, try use of Float point function for HW calculation, maiby it could bring new inspiration for unsigned char
	TODO: check the code which was sent to you be the project leader, about similar impelentation but for floating point, there I saw different HW calc function based on the standard for floating point, while this is nice, we cant forget that unsigned char, as all data types, are not only composed of the value, but contain also different informations, the best example would be uin8_t, where this influecnce could be  quite be  felt. 

5. [X] Try to figure out what causes that correlation cloud after about 10K sample, by comparing old iteration with current one, so much difference there shouldn't be.
    -- Mainly visible for HW(int), where 255 is prevalent, for others it disapears mostly, if opt. is turned on then it dissapears also for HW(int). Otherwise it was also observed that its prevalence was smaller when z was added into Neuron var..
    -- Possible cause: In memory values (permeating values),

   - Optional: If you have time, check what causes those warnings in the building process.
   - TODO start writing Impementation in overleaf, 0. Choosen ANN, 1. Quantization (Each method CHAR, UINT8_T, UNSIGNED CHAR), 2. Correlation analysis (1.,2.,3.,4. method),3. Weight extraction method (1.,2.,3.,4)

      Questions:
          1. Why does the trace, differs so much when the rand is on and off (i mean rand setting of weights)
          2. Why does the time needed for calculation of correlation, increase exp. with number of traces, to 1K it is acceptable, about 45sek, but with 3K it goes into 9min., and 10K 1.15hod.

## 13th week
   1. [X] Create function which will take correlation matrix and true secret key, and output grahp wherein true secret correlation is red and others are all gray
   2. [X] Continue with SPA, this time on level of multiplications
   3. [ ] Consider which parts are to be included in Documents (parts as graphs)
   4. [ ] (Optional/Wendsday) Try k-cross validation