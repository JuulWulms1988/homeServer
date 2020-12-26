web.ledPl = {
    updatePr: function (x, y, z) {
        var t = -1, f = function (a) { for (var GG = 0, GGG = a.length; GG < GGG; GG++) if (a[GG] === t) return true; return false; };
        for (p in x) 
            if (!++t) for (var T = 0, P = x[p], P2 = y[t], M = P.length; (T === z && ++T < M) || T < M; T++) {
                if (P[T].checked !== P2[T]) P[T].checked = P2[T];
            }
            
                //funcBox
            else if (f([3, 5, 12])) {
                if (x[p].checked !== y[t])
                    x[p].checked = y[t];
            }
            //%
            else if (t > 7 && t < 11 || f([1, 2, 13, 14])) {
                var bbuFF = mathO.cvV100(mathO.cvN100(y[t])).toString();
                if (x[p].value !== bbuFF) x[p].value = bbuFF;
            }
            //tijd
            else if (f([4, 6, 11, 15, 17, 18])) {
                var bbuFF = mathO.cvNTIJD(y[t]);
                if (x[p].value !== bbuFF) x[p].value = bbuFF;
            }
            //Clr
            else if (t === 7) {
                var pPp = x[p][1], PpP = mathO.cvNClrS(mathO.cvVClr(y[t])); if (pPp.backgroundColor !== PpP) pPp.backgroundColor = PpP;
            }
            //direct
            else if (x[p].value !== y[t].toString()) x[p].value = y[t].toString();
    },
    clrWin: function (uFunc) {
        vars.ffClrWinLdPl = 0; var pWin = web.window;
        pWin.popUp('Kleurkeuze', function () {


            var el = pWin.newIn(), hObj = el.appendChild(document.createElement('div'));
            hObj.setAttribute('class', 'inFrBl'); 
     
            for (var t = 0; t < 19; t++) {
                var elm = document.createElement('div');
                elm.setAttribute('class', 'clrSelectB');
                if (t < 4) elm.classList.add('clrSelectNT');
                else if (t > 15) elm.classList.add('clrSelectNB');
                if (!(t % 4)) elm.classList.add('clrSelectNL');
                else if (!((t + 1) % 4)) elm.classList.add('clrSelectNR');

                (function (x) {
                    elm.onclick = function () {
                        this.classList.add('clrSelectBhov');
                        uFunc((vars.ffClrWinLdPl = x) - 1);
                    }
                })(t + 1);


                var e2 = elm.appendChild(document.createElement('div')); e2.style.backgroundColor = mathO.cvNClrS(mathO.cvVClr(t));
                if (!(t % 4) && t) hObj = el.appendChild(hObj.cloneNode(false));
                hObj.appendChild(elm);
            }
            
            return el;

        }(), {
            propArgF: function () { if (!vars.ffClrWinLdPl) return true; return false; }, extPopF: function () { delete vars.ffClrWinLdPl; }
        });
    },
    window: function (x) {
        function nT(XX) { return document.createTextNode(XX); }
        var P = web.window, pAc = web.actie.ldPl, PL = vars.cat.ledPlf[x], PL0 = PL[0];
        var elm = P.newIn();
        var hObj = document.createElement('div'); hObj.setAttribute('class', 'inFrBl');
        var dObj = document.createElement('div'); dObj.setAttribute('class', 'inFrIBl');
        P.header('Strip & cliënts', dObj);
        {
            var eSub = P.par(true);
            {
                var eOp = document.createElement('select'); eOp.className = 'formSelect'; 
                eOp.id = 'setLdPl_Str';
                eOp.onchange = function () { pAc.resetStrip(this.value, x); };
                for (var t = 0, m = PL.length; t < m; t++) {
                    var eSe = document.createElement('option');
                    eSe.value = t;
                    eSe.text = t.toString();
                    if (!t) eSe.selected = true;
                    eOp.appendChild(eSe);
                }

                var eAr = [[]];
                (eAr[0] = P.cell()).appendChild(eOp);
                eAr[0].appendChild(document.createTextNode(' '));

                (eAr[1] = P.cell()).appendChild(function () { var eEeE = P.but(3, 'Ontkoppel'); eEeE.setAttribute('onclick', 'web.actie.ldPl.detChldF(' + x.toString() + ', document.getElementById(\'setLdPl_Str\').value)'); return eEeE; }());
                eSub.appendChild(P.tab1([eAr], false));
                
                

            } 
                {
                    var eCl = document.createElement('div');
                    eCl.setAttribute('class', 'inFrIBl');
                    eCl.setAttribute('id', 'setLdPl_Cl');
                    eSub.appendChild(this.setCl(eCl, PL0.parChldAr, 0));
                }



            dObj.appendChild(eSub);
        }
        hObj.appendChild(dObj), hObj.appendChild(document.createTextNode('        '));
        dObj = dObj.cloneNode(false);

        P.header('Algemeen', dObj);
        {
            var eSub = P.par(true);
            eSub.setAttribute('id', 'setLdPl_Alg');
            eSub.appendChild(PL0.randVar);
            eSub.appendChild(document.createTextNode('  Kleurstand'));
            dObj.appendChild(eSub);
        }
        elm.appendChild(hObj).appendChild(dObj);


        

        hObj = hObj.cloneNode(false);
        dObj = dObj.cloneNode(false);
        P.header('Kleur', dObj);
        {
            var eSub = P.par(false);
            eSub.setAttribute('id', 'setLdPl_Clr');
            eSub.appendChild(web.code.tab26([[[nT('Periode')], [nT('Pauze')], [nT('Afwijking')], [nT('Negatief')]], [[nT('Waarde')], [PL0.per], [PL0.rgbPauze, nT(' %')], [PL0.dlay], [PL0.negDlay]]]));

            
            dObj.appendChild(eSub);
        }
        hObj.appendChild(dObj), hObj.appendChild(document.createTextNode('        '));
  


        dObj = dObj.cloneNode(false);
        P.header('Helderheid', dObj);
        {
            var eSub = P.par(false);
            eSub.setAttribute('id', 'setLdPl_Hel');
            eSub.appendChild(web.code.tab26([[[nT('Sterkte')], [nT('Amplitude')], [nT('Periode')], [nT('Afwijking')], [nT('Negatief')]], [[nT('Waarde')], [PL0.helder, nT(' %')], [PL0.helAmp, nT(' %')], [PL0.helPer], [PL0.helDlay], [PL0.negHelCur]]]));


            dObj.appendChild(eSub);
        }
        hObj.appendChild(dObj), hObj.appendChild(document.createTextNode('        '));


        
        dObj = dObj.cloneNode(false);
        P.header('Gamma', dObj);
        {
            var eSub = P.par(false);
            eSub.setAttribute('id', 'setLdPl_Gam');
            eSub.appendChild(web.code.tab26([[[nT('Kleur')], [nT('Sterkte')], [nT('Interval')]], [[nT('Waarde')], [function () {
                var ElM = document.createElement('div');
                ElM.setAttribute('class', 'clrSelect');
                ElM.appendChild(PL0.gamClr[0]);
                ElM.onclick = function () {
                    var pVal = this.children[0].style;
                    web.ledPl.clrWin(function (X) {
                        {
                            var ff = mathO.cvNClrS(mathO.cvVClr(X)); if (pVal.backgroundColor === ff) return; else pVal.backgroundColor = ff;
                        } pAc.VarAc(X, 6, x, document.getElementById('setLdPl_Str').value, pVal);
                    });
                };
                return ElM;
            }()], [PL0.gamVal, nT(' %')], [PL0.gamInterval]]]));
            dObj.appendChild(eSub);
        }
        hObj.appendChild(dObj), hObj.appendChild(document.createTextNode('        '));
        dObj = dObj.cloneNode(false);
        P.header('Gamma-interval', dObj);
        {
            var eSub = P.par(false);
            eSub.setAttribute('id', 'setLdPl_GamInt');
            eSub.appendChild(web.code.tab26([[[nT('Sterkte')], [nT('Helderheid')], [nT('Periode')], [nT('Pauze')], [nT('Afwijking')], [nT('Negatief')]], [[nT('Waarde')], [PL0.gamIval, nT(' %')], [PL0.gamiHel, nT(' %')], [PL0.gamPer], [PL0.gamPauze, nT(' %')], [PL0.gamDlay], [PL0.negGamDlay]]]));


            dObj.appendChild(eSub);
        }
        elm.appendChild(hObj).appendChild(dObj);
        return elm;
    },
    setCl: function (elm, ar, not) {
        for (var t, tw = t = 0, m = ar.length; (t === not && ++t < m) || t < m; t++ , tw++) {
            if (!(tw % 5) && tw) elm.appendChild(document.createElement('br'));
            var eEe = elm.appendChild(document.createElement('div')); dom.addCls(eEe, ['inFrIBl', 'inFrIBlTT']);
            eEe.appendChild(ar[t]);
            eEe.appendChild(document.createTextNode(' ' + t.toString()));
        }
        return elm;
    }
};