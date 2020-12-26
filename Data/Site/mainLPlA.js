web.actie.ldPl = {
    VarAc: function (val, valNo, ldNo, strNo, pThis) {
        web.actie.updateF(function (pThisF) {
            var pCatVar = vars.cat.ledPlf[ldNo];
            function setValF(xValN, xValW) {
                function argfF(xYx) { var xTYx = -2; for (var yXy in pCatVar[0]) if ((++xTYx === 14 && !(xTYx = 20)) || (xTYx === 24 && !(xTYx = 40)) || xTYx == xYx) return yXy; }
                for (var xT = 0, xM = pCatVar.length, xA = pCatVar[strNo].parChldAr; xT < xM; xT++)
                    if (xT === strNo || xA[xT].checked)
                        if (xValN === 2 || xValN === 4 || xValN === 11) {
                         
                            pCatVar[xT][argfF(xValN)].checked = (function () {

                                if (xValW !== '0') 
                                    return true;
                                
                                
                                    return false;
                                
                            })();
                            
            }
                        else if (xValN === 6) {
                            pCatVar[xT][argfF(xValN)][1].backgroundColor = mathO.cvNClrS(mathO.cvVClr(xValW));
                        }
                        else pCatVar[xT][argfF(xValN)].value = xValW;
            }
            setValF(valNo, val);
            switch (valNo) {
                case 5: //gamPer -> per
                    if (pCatVar[strNo].per.value < val) setValF(23, (function () { if (val && val < 100) return 100; else return val; })());
                    break;
                case 23: //per -> gamper
                    {
                        var buGGf = pCatVar[strNo].gamPer.value;
                        if (buGGf && buGGf > val) setValF(5, val);
                
                    }
                        break;
            }
            pThisF.aFrameF('ld' + mathO.floor(ldNo / 10).toString() + (ldNo % 10).toString() + 'wz@' + mathO.floor(strNo / 10).toString() + (strNo % 10).toString() + mathO.floor(valNo / 10).toString() + (valNo % 10).toString() + '=' + mathO.cvIntStr(val));
        });
    },
    detachStrip: function (pCatVar, strNo) {
        var uit = false;
        for (var xT = 0, xM = pCatVar.length, xA = pCatVar[strNo].parChldAr; xT < xM; xT++)
            if (xT !== strNo && xA[xT].checked && (uit || (uit = true))) xA[xT].checked = pCatVar[xT].parChldAr[strNo].checked = false;
        return uit;
    },
    parChldAF: function (val, ldNo, strNo, clNo, pThis) {
        var pThisF = this;
        web.actie.updateF(function (pThisf) {
            var pCatVar = vars.cat.ledPlf[ldNo];
            pThisF.detachStrip(pCatVar, clNo);
            if (val) {
                var pCat2 = pCatVar[clNo], pCat3 = pCatVar[strNo];
                for (var xT = 0, xCA = pCat2.parChldAr, xM = pCatVar.length, xA = pCat3.parChldAr; xT < xM; xT++)
                    if ((xT === clNo && !(xA[xT].checked = true)) || (xT !== clNo && (xT !== strNo || !(xCA[strNo].checked = true))))
                        xCA[xT].checked = pCatVar[xT].parChldAr[clNo].checked = xA[xT].checked;
                var tel = -2;
                for (var yXy in pCat2)
                    if ((++tel === 14 && !(tel = 20)) || (tel === 24 && !(tel = 40)) || tel >= 0) 
                        if (tel === 2 || tel === 4 || tel === 11)
                            pCat2[yXy].checked = pCat3[yXy].checked;
                        else if (tel === 6) {
                            pCat2[yXy][1].backgroundColor = pCat3[yXy][1].backgroundColor;
                        }
                        else pCat2[yXy].value = pCat3[yXy].value;
            }
            pThisf.aFrameF('ld' + mathO.floor(ldNo / 10).toString() + (ldNo % 10).toString() + (function () { if (!val) return 'dt@'; else return 'at@' + mathO.floor(strNo / 10).toString() + (strNo % 10).toString(); })() + mathO.floor(clNo / 10).toString() + (clNo % 10).toString());
        });
    },
    detChldF: function (ldNo, strNo) {
        var pThisF = this;
        web.actie.updateF(function (pThisf) {
            if (pThisF.detachStrip(vars.cat.ledPlf[ldNo], strNo))
                pThisf.aFrameF('ld' + mathO.floor(ldNo / 10).toString() + (ldNo % 10).toString() + 'dt@' + mathO.floor(strNo / 10).toString() + (strNo % 10).toString());
        });
    },
    resetStrip: function (val, x) {
        var pLedF = web.ledPl, PV = vars.cat.ledPlf[x][val], aN = (function () { var UIT = []; for (var TTT = 0, AARR = ['setLdPl_Clr', 'setLdPl_Hel', 'setLdPl_Gam', 'setLdPl_GamInt']; TTT < 4; TTT++) UIT.push(document.getElementById(AARR[TTT]).children[0].children[1].children[1].children[0]); return UIT; })();
        for (var tag in PV) {
            var P = PV[tag];
            {
                var uit = true;
                switch (tag) {
                    case 'parChldAr': {
                        var elm = document.getElementById('setLdPl_Cl');
                        for (var t, tW, tPlus = tW = t = 0, p, str, m = P.length; ((t.toString() === val && ++t < m) || t < m) && (p = elm.children[(function () { if (!((tW - tPlus) % 5) && tW) tW++, tPlus++; return tW; })()]); t++, tW++) {
                            p.replaceChild(P[t], p.children[0]);
                            if ((str = ' ' + t.toString()) !== (p = p.childNodes[1]).nodeValue) p.nodeValue = str;
                        }
                    } break;
                    case 'randVar': {
                        var elm = document.getElementById('setLdPl_Alg');
                        elm.replaceChild(P, elm.children[0]);
                    } break;
                    case 'gamClr': {
                        var elm = aN[2].children[0].children[0].children[0];
                        elm.replaceChild(P[0], elm.children[0]);
                    } break;
                    default: uit = false; break;
                }
                if (uit) continue;
            }
            for (var t = 0, ar = [
                ['per', [0, 0]], ['rgbPauze', [0, 1]], ['dlay', [0, 2]], ['negDlay', [0, 3]], ['helder', [1, 0]], ['helAmp', [1, 1]],
                ['helPer', [1, 2]], ['helDlay', [1, 3]], ['negHelCur', [1, 4]], ['gamVal', [2, 1]], ['gamInterval', [2, 2]], ['gamIval', [3, 0]],
                ['gamiHel', [3, 1]], ['gamPer', [3, 2]], ['gamPauze', [3, 3]], ['gamDlay', [3, 4]], ['negGamDlay', [3, 5]]
            ], m = ar.length; t < m; t++) if (ar[t][0] === tag) {
                var p = ar[t][1], elm = aN[p[0]].children[p[1]].children[0];
                elm.replaceChild(P, elm.children[0]); break;
            } 
        } 
    }
};