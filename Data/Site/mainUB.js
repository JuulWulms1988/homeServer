web.upbar = {
    openF0: function (naFunc, eU0) {
        var elmUpbar0 = document.createElement('div'); elmUpbar0.classList.add('upbar0div');
        var eU02 = elmUpbar0.cloneNode(true),
            eU02S = eU02.style,
            eU0S = elmUpbar0.style,
            eU0C = eU0.obj = document.createElement('div');
        eU0C.classList.add('inFrame');

        var pNm = vars.cat.naam[0];

        var eFSO = document.createElement('div');

        eFSO.classList.add('barbut');
        eFSO.onclick = this.evBut0F; eFSO.appendChild(document.createTextNode(pNm[0]));
        eU0C.appendChild(eFSO); eU0C.style.opacity = 0;
        elmUpbar0.appendChild(eU0C);
        var afstW = mathO.floor(dom.getRec(elmUpbar0).width);
        eU02S.padding = '0px';
        eU02S.width = '0px'; eU02S.height = '58px';
        var subT_end = 20, r = 0, subT = 0; var subAcc = mathO.acc(afstW, subT_end);
        var subButVal = setInterval(function () {
            var flag;
            if (++subT < subT_end) {
                r = afstW - mathO.sT(subAcc, subT_end - subT);
                if (r >= 2) eU02S.width = (r - 2).toString() + 'px';
                return;
            }
            document.body.replaceChild(elmUpbar0, eU02), clearInterval(subButVal); naFunc();
        }, 50); document.body.appendChild(eU02);
    },
    butF: function (ar) {
        delete web.upbar.butF;
        var out = document.createElement('div'); out.classList.add('inFrame');
        for (var t = 0, m = ar.length; t < m; t++) {
            var elm = document.createElement('div');
            elm.classList.add('barbut'); elm.appendChild(document.createTextNode(ar[t]));
            elm.setAttribute('onclick', 'web.upbar.mainLink([0, ' + t.toString() + '])');
            out.appendChild(elm);
        }
        return out;
    },
    mainLink: function (x) {
        if ('mLinkBl' in this) { delete this.mLinkBl; return; }
        if (x[0] === 0) return;
        var niet, dFade, pAn = web.anim, pWU = web.upbar, afstN = pWU.t_afstN, eC = pWU.t_u0CE, tElC = pWU.t_u0tElCE, eU0 = pWU.t_u0E, eU00 = eU0.firstChild, eU000 = eU00.firstChild, pNow = vars.upBarV, eCC = pWU.t_u0CCE, eCCC = pWU.t_u0CCCE, eCCCS = eCCC.classList;
        for (var t = 0, a = ['t_u0CCCE', 't_afstN', 't_u0CCE', 't_u0E', 't_u0tElCE', 't_u0CE'], m = a.length; t < m; t++) delete pWU[a[t]];
        eCCCS.add('barbut'), eCCCS.remove('barB0S');
        if (x[1] !== pNow[1]) {
            niet = false; dFade = eC.firstChild; var af; if (x[1] > pNow[1]) af = 1; else af = 0;
            var elm = eCC.childNodes[x[1] - af]; eU000.replaceChild(elm.firstChild.cloneNode(true), eU000.firstChild);
            (elm = elm.classList).add('barB0S'), elm.remove('barbut');
        } else niet = true, dFade = eCC;
        parent.blockF(true);
        pNow[1] = x[1];
        dFade.style.opacity = 1;
        pAn.fade(false, [dFade], 1, function () {
            var aant;
            function naFunc() {
                if (--aant) return;
                if (!niet) eU00.style.opacity = 0;
                document.body.replaceChild(eU0, tElC);
                if (niet) parent.blockF(false);
                else pWU.setMain([eU00], function () { eU00.removeAttribute('style'); parent.blockF(false); });
            }
            if (niet) aant = 1;
            else {
                aant = 2; var elmMain = document.getElementById('mainPageDiv'); elmMain.style.opacity = 1;
                pAn.fade(false, [elmMain], 1, naFunc);
            }
            
            

            var afstW = dom.getRec(eU0).width - 14;


            var eCS = eC.style, subT_end = 20, subT = 0, afE = afstN.width - 14, af, af0E = afstN.height - 14, af0 = (af0E - 46) / 2, subAcc, subAcc0 = mathO.acc(af0, subT_end / 2);
            var up; do {
                if (afE > afstW) up = 2; else if (afE === afstW) { up = 0; break; } else up = 1; af = mathO.diff(afE, afstW) / 2; subAcc = mathO.acc(af, subT_end / 2)
            } while (false);
            var subButVal = setInterval(function () {
                if (++subT < subT_end / 2) {
                    eCS.height = (af0E - mathO.sT(subAcc0, subT)).toString() + "px";
                    if (!up) return;
                    var rek = mathO.sT(subAcc, subT);
                    if (up === 2) rek = afE - rek;
                    else rek += afE;
                    eCS.width = rek.toString() + "px";
                }
                else if (subT < subT_end) {
                    eCS.height = (af0E - (af0 + (af0 - mathO.sT(subAcc0, subT_end - subT)))).toString() + "px";
                    if (!up) return;
                    var rek = af + (af - mathO.sT(subAcc, subT_end - subT));
                    if (up === 2) rek = afE - rek;
                    else rek = rek += afE;
                    eCS.width = rek.toString() + "px";
                }
                else {
                    clearInterval(subButVal), eCS.width = afstW.toString() + 'px', eCS.height = '46px';
                    naFunc();
                }
            }, 50);









        });
               
    },
    setMain: function (ar, nFunc) {
        var pNow = document.getElementById('mainPageDiv'), elm = pNow.cloneNode(false);
        document.body.replaceChild(elm, pNow), pNow = vars.upBarV;
        switch (pNow[0]) {
            case 0: web.window.home(pNow[1], elm);
        }
        ar.push(elm); web.anim.fade(true, ar, 1, function () { elm.removeAttribute('style'), nFunc(); });
    },
    anim: function (elm, obj) {



    },
    evBut0F: function () {
        
  
        var pWU = web.upbar, eU0 = pWU.t_u0E = document.getElementsByClassName('upbar0div')[0],
        
        eU0C = eU0.firstChild,
        eU0CC = eU0C.firstChild, bd = document.body;
        
        


        var eC = pWU.t_u0CE = eU0.cloneNode(true), eCC2 = eC.firstChild, eCC = pWU.t_u0CCE = eCC2.cloneNode(false), eCC2S = eCC2.style, eCCC = pWU.t_u0CCCE = eCC2.firstChild; eCC2.appendChild(eCC); pPpP = web.upbar; eC.onclick = function () { pPpP.mLinkBl = ''; };
        eCCC.removeAttribute('onclick'); eCCC.classList.remove('barbut'); dom.addCls(eCCC, ['barB0S', 'bar0fs']);
        var tElC = pWU.t_u0tElCE = document.createElement('div'); tElC.classList.add('container'); 
        var afstW = dom.getRec(eC).width - 14, afstN, eCS, pNow = vars.upBarV, pNm = vars.cat.naam[pNow[0]];
        tElC.setAttribute('onclick', 'web.upbar.mainLink([1, ' + pNow[1].toString() + '])');
        {
            var len = pNm.length; 
            
            if (len > 1) {
                var t = 0;
                if (t === pNow[1]) t++;
                var flag = false;
                var elm = eU0CC;
                do {
                    elm = elm.cloneNode(true);
                    if (!flag) flag = true, elm.classList.add('bar0fs');
                    elm.firstChild.nodeValue = pNm[t];
                    elm.setAttribute('onclick', 'web.upbar.mainLink([1, ' + t.toString() + '])');
                    eCC.appendChild(elm);
                } while ((++t === pNow[1] && ++t < len) || t < len);
                
            }
            (eCS = eC.style).height = 'auto'; afstN = pWU.t_afstN = dom.getRec(eC);
            eC.removeAttribute('style'); eCC.style.opacity = 0;
        }
        tElC.appendChild(eC);
        eCS.width = afstW.toString() + 'px';
        
        bd.replaceChild(tElC, eU0);
        //alert(afstW);
        parent.blockF(true);
        
        var subT_end = 20, subT = 0, afE = afstN.width - 14, af, af0E = afstN.height - 14, af0 = (af0E - 46) / 2, subAcc, subAcc0 = mathO.acc(af0, subT_end / 2);
        var up; do {
            if (afE > afstW) up = 2; else if (afE === afstW) { up = 0; break; } else up = 1; af = mathO.diff(afE, afstW) / 2; subAcc = mathO.acc(af, subT_end / 2)
        } while (false); 
        var subButVal = setInterval(function () {
            if (++subT < subT_end / 2) {
                eCS.height = (46 + mathO.sT(subAcc0, subT)).toString() + "px";
                if (!up) return;
                var rek = mathO.sT(subAcc, subT);
                if (up === 2) rek += afstW;
                else rek = afstW - rek;
                eCS.width = rek.toString() + "px";
            }
            else if (subT < subT_end) {

                eCS.height = (46 + af0 + (af0 - mathO.sT(subAcc0, subT_end - subT))).toString() + "px";

                if (!up) return;
                var rek = af + (af - mathO.sT(subAcc, subT_end - subT));
                if (up === 2) rek += afstW;
                else rek = afstW - rek;
                eCS.width = rek.toString() + "px";

            }
            else {
            clearInterval(subButVal), eCS.width = afE.toString() + 'px', eCS.height = af0E.toString() + 'px';

                web.anim.fade(true, [eCC], 1, function () { eCC.removeAttribute('style'); parent.blockF(false); });
            }
        }, 50);
        

    }


}