# ZENKU DP2 TODO list for week:

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




# ZENKU DP3 TODO list for week:

## Week 0 TODO:
   1. [X] Connect all filter parts, and try them
        - Done, found several possible optimalisation, from which the best would be to increase usage of global variables, at least for vars, which are sended into depth several times, such as scope ...
   2. [X] Implement, countermeasures, and differentiate them from norm setup, using different command signals
       - Done, needed to implement reset_target (reseting high low signals), becasue of proble of loosing high signal as starting sequence, possible cause, is overflow of measurement data, because of this the reset was impelemnted
   3. [X] Add additional global variable, for all inputs to be same
   4. [X] Try attack on one weight in this case, and what it results int
   
###### Question:
- What is next closest correlation value of found key? 
  - Is there any connection?
  - If there is, can it be compesated for,  or  even delete? 

## Week 1 TODO:
   1. Check errors in documents (cause: before presentation the error was found):
        - Checked, with regex, no missed citations found.
   2. [X] Try out full input, for NO_OPT setup (cause: in OPT setup traces, the CPA didnt fare good, the result aftel filtering werent quite clear).
        - It matches, the problem was in optimization.
   3. [X] Create guiding spectogram from average wave (cause: suspision that the filtering LP and HP, derived from more objective source, such as average of all waves, will offer more general filtering ranges).
       - No observable difference, maiby try on Optimized setup traces.
   4. [ ] Implementation of K-Cross Validation: on 1000 k=4, 2000 k=4, 3200 k=4, 4000 k=4. (cause: effort to make filtering more general and precise)
 


## Week 2 TODO:
   1. [X] Analyza shuffle, with known weights:
        - Pre hodnoty prvych vah, vsetky boli najdene, avsak v inom poradi ako by v skutocnosti mali byt, taktiez ich corellacne oblasti boli dost vyznacne
           - Pravdepodobny dovod: 
             -  a) v ramci prvej vrstvy je iba 5 neuronov, neposkytuje to dostatocne moznosti pre 1000 traces, solution: skus to na architekture s napr. 20 neuronmi <--- Moc to nepomohlo, max znizilo to correlacie, (este budem potrebovat 1x pokus s decimate = 3 a upravou filteringu)
             -  b) random number generation, sa opakuje: solution: skontroluj to v outpute pristroja 
   2. [] Pokus dummy not-opt
        - 1. Norm forward ma tie dummy opperacie mimo multiplikacie a az za layer operations
        - 2. Stale to pada na triggeroch pri dummy operaciach -->  **Timeout in OpenADC capture(), no trigger seen! Trigger forced, data is invalid. Status: 0b**
        - V konecnom dosledku som zmenil nazov funkcie (pre mozny prekriv) a zmenil poradie jej nastavenia na 1. a problem bol vyrieseny... Nechapem
   3. [X] Shuffling, analyza jeho prelomenia https://arxiv.org/pdf/2501.00798
       - Basically, vacsi pocet tracov, na kompenzaciu rand.,
   4. [ ] K-cross validation
       - ...
## Week 3 TODO:

   1. [X] Analyza shuffle, pre 7-15-5-4-2, decimate=3
       - Vacsinu sa podarilo extrahovat ale nie vsetky <-- este je to potrebne odskusat bez filtracie 
   2. [X] Analyza dummy, s pridanymi operaciami pred a po mult. 
       -  CPA was succesfull, either way ... <-- try with minimum traces 
      
   3. [X] Find the minimum number of traces for succesfull CPA ...
       - 100 OK, 50 OK, 25 OK 3/2 
   4. [X] Check masking countermeasures and pick one
       - ... For example same as in Present 80, wherein the key are weights
      
   5. [X] Find the work using spectogram and add its info to DP document
       - ... https://www.researchgate.net/profile/Huizhong-Li-7/publication/331625142_Convolutional_Neural_Network_Based_Side-Channel_Attacks_in_Time-Frequency_Representations/links/5fbe2643299bf104cf7557e1/Convolutional-Neural-Network-Based-Side-Channel-Attacks-in-Time-Frequency-Representations.pdf?origin=publication_detail&_tp=eyJjb250ZXh0Ijp7ImZpcnN0UGFnZSI6InB1YmxpY2F0aW9uIiwicGFnZSI6InB1YmxpY2F0aW9uRG93bmxvYWQiLCJwcmV2aW91c1BhZ2UiOiJwdWJsaWNhdGlvbiJ9fQ 
       - Work about chipwhisperer chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://theses.liacs.nl/pdf/2023-2024-AlkemaJDCJorisDuurtCornelis.pdf
   6. [X] Check minimum without filtering, and with, and also with or without countermeasures ...
       - ... 
       - For dummy at 25 traces, the noise was quite substantial and ghost peaks also, but with knowing weight, we found them dominating, over their interval domains.
       - For shuffle at 25 traces, only effect was reordering of their placement in traces. <--- Needs in depth analysis whether the rand indices in each call are same.
       - For (100, 50, 25, 15) without filtering by spectogram, the correlations matrix, was quite more noisy similarly to dummy, but still true weight dominated in their interval domains.
   7. [ ] K-cross validacia ...
      - ..
   8. [ ] Make plan for next week
       - ... 1.)  In depth analysis of rand indices, in each call.
      - [X] 2.)  Improvement in dummy operations by using input values in its multiplication
          - Can be dummy also implemented  inside of multiplication? By adding rand dummy mult value into multiplications, and as second step, divide the resulting number by the the used dummy value (PS: usable only in no-opt, for opt it should delete this meaningless operaition).
      - [X] 3.) Try to think about possible improvment in Shuffle.
          - Get 3 random indices to weights, then sum them, and resulting number use making life harder for attacker, either by masking multiplication, or by doing multiplication using resulting number -- Dummy operations.
          - **Or using those 3 random number, do time offset of operation, for RANDOM (each multiplication need different ofset, othervise elastic fitting can solve this problem) desynchronization of samples, and result in scrabling of correlation.**
      - ... 4.) Try to think and implement mask.
- Questions:   
    1. Why, only first 2 declared functions in Simpleserial work, and others return No trigger seen?
    2. Shuffle doesnt have much of an impact, as previously thought, maximaly, only in aspect of needing exhastive pairing of CPA's weights for knowing AF results?

## Week 4 TODO:

   1. [X] In depth analysis of rand indices, in each call
      - [X] The problem was identified, and solved. The root of problem was repeated call of seeding function, and solution was moving of its implementation to main.
      - [X] With working alg. try to find number of traces needed to somehow mitigate the shufling. Number to try [500,1000,1500,2000, 5000 and 10000 <--- Needs to make some changes to functions, so that correlation doesnt take too much time]
blem was in repeated seeding operation, it was moved to main, where it is called only once <--- done up to 5000, minimal CPA results noted
   2. [X] Enhanced dummy operations
      - [X] Add input into multiplication
      - [X] randomize mult. value participating with input, but ensure that it remains same across, all trace measurements, "dummy weights"
         - Done, not much effect observerd. 
      - [X] TODO, Use dummy operation for desynchronization
        - Done, the effect was quite good, for price of time overhead. It in effect is quite simmilar to shufling. <-- Priority target 


## Week 5 TODO:

   1. [X] Stress testing: With working alg. try to find number of traces needed to somehow mitigate the shufling and dummy. Number to try [6000 and 10000 <--- Needs to make some changes to functions, so that correlation doesnt take too much time]
blem was in repeated seeding operation, it was moved to main, where it is called only once
      - Result, was still inconclusive, the shuffle was not broken even for 10 000 traces in architecture 7542.
   2. [X] Find/pick suitable masking countermeasure:
      1. Break Input or Weight into parts, for now two, and do 2 operations. eg. I=25, W=10: 11*10=110, 14*10=140  110+140=25*10.   And the brokage can be based on Cifrach (... zabudol som ich preklad v eng.), Random number offset, we can choose it on start of each handling.
         - Optimalization: We set the offset at the start of handling, then during multiplication, we subtract offset from input, if the number is >= offset, and increase counter, before multiplication we use counter as weight and offset as input and add its value to intermediate value. 
         - <-- Inconclusive, the mask from above, is not sufficient as the true value must be deposited as next input, but in this case the information is made visible. Other option is to move leftover from operation to next layer, but that would mean quite overhead.
         - Results:  - The breakage (data spliting) resulted in failure as there is a need for having true input known for next layer.
             - After some optimalizations, the end result was more simple masking countermeasure, but succesfull one. 
                - The end result is in essence basic substitution cypher, which is constrained by number domain employed, so for lower exhaustive search is relative reachable, but for greater number, not so much without supercomputers. Of cource there is difficulty of needing (count_of_number_in_nDomain * min_succesfulCPA_traces) * (finding corresponding combinations)
         - Proposiotion: In essence, the dummy and shuffle have greater potential as compared to current version of optimized Substiution Masking countermeasure. The positive of this countermeasure is that the main and greates overhead is only in first layer, in others there are still some additional operaions, but not as much as in first. Nevertheless this is not quite advantage over dummy, as there is needed only few offset operaions for desynchonizing whole correlation calculation.
         - Enhancements: Possibly introduce into operaion other variable.  
  3. [X] Implement choosen masking countermeasure: results up there. 




## Week 6 TODO:

  1. [X] Testing on 20K - 25K traces, overhead findings
     - In case of Current masking countermeasure, the results were that it was almost breached 
  2. [X] Implement measurement, by sumation of power, and time
     - time in clks, for all options same 48 CLKs
  3. [X] Optimizing current setup and adding libraries 

## Week 7 TODO:

  1. [X] Finishing CPA for first layer's weights
     - Overall all 7 weight were succesfully extracted, for first layer. And as with filtering, the peaks are quite sparse the pick_up is ok. But 2 exceptions were noted, one in case of 7th weigt, where before one of peaks was unknown peak, and when the weight were same after each other, then second one's peak was missing.
  2. [ ] Implement AF result CPA
     - The problem is currently with first layers resulting **a** as they don't match what should be calculated, needs to check in debuging.
     - Continuation from subpoint above. The problem was in correlation function, and that out_data was shown only for first rand_val. After repair the problem was solved, and resulting corelations found placement of AF. With one noted problem, and that is that RELU in current ANN doesnt work.
     - [X] Needs to do path for relu in ANN firmware (if z > 127    alebo to castnem do signed char)
       - The result of patch was that conventional CPA didnt work outside of first neuron, well at least the power traces were magnidute smaller, and still connected to previosu neuron (which is bullshit). 
       - Also the mentioned "problem" was debuged in visual studio code, and there it worked fine.
       - Where is the proble?
     - [X] Needs to implement correlation for following layer, so correlation from 2 sub-point above can be compared, at choosen placement.
       - The experimental function was defined, but whether beacuse there is lack of nonlineariti, the correlations are still shown in previous neurons (tried for third neuron and first weight).
       - A the alg. for finding border, or correlation's comparisons should be done between what? Correlations of weights, of correlations of AF? If weight there is needed to be extracted corresponding weight with high correlation and then derive AF result.
     - !!! Second nice find, is that best experimenting order, is from attack on last weight to first, as last shows only one operation and AF, and first first operation and all operations after it.
  - 


## Week 8 TODO:

  1. [X] Solve problem of relu from previous week.
    - by replacing if else conditioning, and making it somehow like entropy loss function. Also found problem with quantization.
  2. [X] Repair time overhead measurement
  3. [ ] Compsensate for problem with HW32, when quantization was rightly aplied. 
     - Tried different input distributions <-- The results were somehow positive, but necessary fitting will be needed, and only after previously mentioned problem was solved. 
     - Tried HW on different bits of real results, the result were best for 8b, same as its is mostly aplied for busses in device, but the results are fragmentary, and there is need for merging of results, so the final values are true ones.
     - The project leader proposed to change to different leakage model, such as absolute/identity, or stochastic (bit parts) but those were tryod out above <-- needs more thought
     - The problem of HW32 stems from that, the real values have quite range, as compared to possible hamming weight values, that closes gap between correlations to simmilar values.
       - I had tried to decrease possible range of real values by influencing the input into 4-bit range, but the results still arent sufficient.


## Week 9-10 TODO:

  1. [X] Continue with fitting, or trying new leakage models, with express purpose of succesfull CPA on int16 intermediate vals.
     - [X] Done 5x Experiment with different researches


## Week 11 TODO:
  1. [X] Try out last planned experiment, and send results to DP leader
     - [X] CPA was succesfull, but domination for all 0th weights across first layer werent quite great. 
     - [ ] TODO ADD CONCRETE CASES
       - dec 1 5000 Top HW-165-BiteSeparate Parts 4, Jump False
       - vanilla 16-bitparts, jump-false, BiteSeparated, Big Endian, 2000, Decimate1, VariationFalse
       - NAME-HW_16bit_intermediateVal_BitePartsSeparated_SignedSpecial_BP1_JFalse_DEC1_T2000_VFalse_E-big_TPint16_VBCS-VanillaBiteCorrSum_W0_CPA_DominantToTrueComparison
       - NAME-HW_16bit_intermediateVal_BitePartsSeparated_C_Endian_BP16_JFalse_DEC1_T2000_VFalse_E-little_TPint16_VBCS-VanillaBiteCorrSum_W0_CPA_TrueToDominantComparison
  2. [X] Finish Border CPA
     1. [ ] Try out combination of countermeasures on if possible int16, if not then on int8  -- MUST
     2. [X] Checkout CPA on FA result after repair in int8 (if possible int16)   (found additional error, the uset weights werent trasposed)              -- MUST
        - Correct weight groups, result in one dominant peak in interval of one layer, and several dominat peaks in next layer (possible use for identifiing next layer). 
        - Bit shifted weights Still Result in no high peaks in resulting correlation vector
     3. [X] Find Border:
        - TODO: Get all results for all previous neruons, but used needs to be list from only one (for finding it's corresponding weights in next layer).
        - Basically identify multiplication domain of choosen neuron
        - And above mentioned neuron do 2 sets of correlations calculations:
          - 1. When rand_inputs are the initial rand_inputs
          - 2. When rand_inputs are resulting values of each run, from one neuron
          - 3. Compare correlation results -- If they are significant, then continue with attack on neuron's weights.
          - 4. PS: the lenght of multiplication area is also significant giveaway. If it is same lenght as previous ones, then it has high propability to belong to previous one layer, only if the it is n+1 in layer, so the number of certain previous layers, neurons are same as input layer, then the propabilty comes into question. 
          - 5.  **RESULTS**: the Border finding was succesfull. Found 2 ways to do it: **First** when doing CPA of each neuron, it has one dominant correlation in current layer - known multiplication field of trace, and several corresponding to it's output used as input in next layer (Here we can determine the next layer). **Second aproach**, similarly to previous one, we determine output of one neruon, and do whole weight_h interval correlation calculation, similarly it's peaks beside one in current layer should all be in next one. [X]
  3. [ ] Tryout autocorrelation                                                            -- Postponed
  4. [ ] Get overhead for each countermeasure.                                             -- MUST 
  5. [X] Make skeleton of this semester's addition to DP document. 



- TODO:
  - Meaurements: property trig_count: int
  - 0. K-cross validation
  - 1. Try combination of countermeasures
  - 2. Optimalization of countermeasures <-- for now optimization is moot, max optimization for desynchronization, as for shufling and also desynchr. it more or less depends on used random generator. For the masking, the current efforts needed to develop/find/optimize current masking countermeasure outweight needs of currently more needed research directions.
  - 4. Article image 6,7. . Calc. needed number of traces https://past.date-conference.com/proceedings-archive/2022/pdf/0242.pdf, vzorec (3), page 3
  - PS: Change to all positive correlation in corr_comp, beacuse for now it is now doing it [X] it uses abs()
  - TODO: refactor seeting of coorrelation trace_len view, in analyser, in general it is blind parameter
  - 5. Try similar aproach as with spectogram, but here use autocorrelation as means of finding patterns