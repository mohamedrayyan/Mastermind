/* 
* File:    Iris.h
* Author:  Mohamed Rayyan
* Created on September 13, 2019, 19:33
*/

#include "Iris.h"

void Iris::fil(Data &temp) {
    if(int(log[fllw].r) == 0 && int(log[fllw].w) == 0) {
        dummy = log[fllw].guess[0];
        skipped++;
        if(lead + 1 <= 9) lead++;
    }

    if(range[lead] == '9') {
        temp.guess[0] = '9';
        temp.guess[1] = '9';
        temp.guess[2] = dummy;
        temp.guess[3] = dummy;
        lead++;
        return;
    }
    else if(lead+1<=9) {
        for(int i = 0; i < 4; i++) {
            if(i <= 1) temp.guess[i] = range[lead];
            else temp.guess[i] = range[lead+1];
        }
        lead++;
        return;
    }
}
void Iris::swap(Data &temp, Data log, int n) {
    switch(n) {
        case 4: {
            temp.guess[0] = log.guess[1];
            temp.guess[1] = log.guess[0];
            temp.guess[2] = log.guess[3];
            temp.guess[3] = log.guess[2];
            break;
        }
        case 2: {
            if(swapped) {
                swapped = false;
                temp.guess = log.guess;
                temp.guess[0] = log.guess[1];
                temp.guess[1] = log.guess[0];
            }
            else {
                temp.guess[0] = log.guess[1];
                temp.guess[1] = log.guess[0];
                temp.guess[2] = log.guess[3];
                temp.guess[3] = log.guess[2];
            }
            break;
        }
    }
}
bool Iris::inNtPssibl(Data log) {
    set<char>::iterator itr;
    for(itr = ntPssibl.begin(); itr != ntPssibl.end(); itr++) {
        if(log.guess[3] == *itr) {
            return true;
        }
    }
}
bool Iris::inPssibl(Data log) {
    for(int i = 0; i < pssibl.size(); i++) {
        if(log.guess[3] == pssibl[i].c) {
            indx = i;
            return true;
        }
    }
}
void Iris::addToNtPssibll() {
    ntPssibl.insert(log[log.size()-1].guess[3]);

    for(int i = (log.size()-1); i >= 0; i--) {
        logir = log[i].r;
        logiw = log[i].w;

        if(logir + logiw == 0) {
            ntPssibl.insert(log[i].guess[0]);
            ntPssibl.insert(log[i].guess[3]);
        }
        else if(inNtPssibl(log[i])) {
            Detail temp;
            temp.c = log[i].guess[0];
            temp.s = logir;
            temp.h = logiw;
            pssibl.push_back(temp);
        }
        else if(inPssibl(log[i])) {
            pssibls = pssibl[indx].s;
            pssiblh = pssibl[indx].h;

            int s = abs(logir - pssiblh);
            int h = abs(logiw - pssibls);

            if(logir + logiw == 3 && pssibls + pssiblh == 2) {
                if(logir > logiw) {
                    Detail temp;
                    temp.c = log[i].guess[0];
                    temp.s = 1;
                    temp.h = 0;

                    pssibl.push_back(temp);
                }
                else if(logir < logiw) {
                    Detail temp;
                    temp.c = log[i].guess[0];
                    temp.s = 0;
                    temp.h = 1;

                    pssibl.push_back(temp);
                }
            }  
            else if(s + h == 0 || pssiblh + pssibls == logir + logiw) {
                ntPssibl.insert(log[i].guess[0]);
            }
            else {
                Detail temp;
                temp.c = log[i].guess[0];
                temp.s = s;
                temp.h = h;

                pssibl.push_back(temp);
            }
        }
    }
}
void Iris::yosheveti(Data &temp) {
    int doubl = 0;

    for(int i = 0; i < pssibl.size(); i++) {
        pssibls = pssibl[i].s;
        pssiblh = pssibl[i].h;

        if(pssibls + pssiblh >= 2) {
            doubl = i;
        }
        if(pssibls >= 1) {
            for(int k = 0; k < pssibls; k++) {
                if(temp.guess[k] == 32) {
                    temp.guess[k] = pssibl[i].c;
                }
                else {
                    temp.guess[k+1] = pssibl[i].c;
                }
            }
        }
        if(pssibl[i].h >= 1) {
            for(int k = 0; k < pssiblh; k++) {
                if(pssiblh > 1) {
                    for(int p = 2; p < 4; p++) {
                        if(temp.guess[p] == 32) {
                            temp.guess[p] = pssibl[i].c;
                        }
                    }
                }
                else {
                    for(int p = 2; p < 3; p++) {
                        if(temp.guess[p] == 32) {
                            temp.guess[p] = pssibl[i].c;
                        }
                        else {
                            temp.guess[p+1] = pssibl[i].c;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < temp.guess.length(); i++) {
        if(temp.guess[i] == 32) {
            temp.guess[i] = pssibl[doubl].c;
        }
    }
}
void Iris::eval(){
    string check="    ";
    string temp = guess;
    rr=0,rw=0;
    //Check how many are in the right place
    for(int i=0;i<code.length();i++){
        if(code[i]==temp[i]){
            rr++;
            check[i]='x';
            temp[i]='x';
        }
    }
    //Check how many are in the wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==temp[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
}
Iris::Iris() {

}
Iris::~Iris() {
    skipped  = 0;
    counter  = -1;
    fllw     = 0;
    log.clear();
    pssibl.clear();
    ntPssibl.clear();
    range    = "0123456789";
    lead     = 1;
    indx     = 0;
    logir    = 0;
    logiw    = 0;
    pssibls  = 0;
    pssiblh  = 0;
    dummy    = '\n';
    swapped  = true;
    first    = true;
}
void Iris::AI() {
    fllw = counter;
    counter++;

    Data temp;

    // base condition for first guess
    if(counter == 0) {
        temp.guess = "0011";
        log.push_back(temp);
        guess = temp.guess;
        eval();
        return;
    }

    log[fllw].r = rr;
    log[fllw].w = rw;

    if(counter + skipped > 9) {
        if(int(log[fllw].w) == 4) {
            swap(temp, log[fllw], 4);
            log.push_back(temp);
            guess = temp.guess;
            eval();
            return;
        }
        else if(int(log[fllw].w) + int(log[fllw].r) == 4) {
            swap(temp, log[fllw], 2);
            log.push_back(temp);
            guess = temp.guess;
            eval();
            return;
        }
    }

    if(int(log[fllw].r) == 4) {
        guess = "";
        return;
    }

    if(counter + skipped <= 9) {
        fil(temp);
        log.push_back(temp);
    }
    else {
        if(first) {
            first = false;
            addToNtPssibll();
        }

        yosheveti(temp);
        log.push_back(temp);
    }
    guess = temp.guess;
    eval();
    return;
}
string  &Iris::stCode() {
    return code;
}
string Iris::gtCode() {
    return code;
}
string Iris::gtGuess() {
    return guess;
}
char Iris::gtRR() {
    return rr;
}
char Iris::gtRW() {
    return rw;
}