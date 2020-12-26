web.kaas = 5;
web.update = {
    intV: 10,
    intV2: 3,
    cnt: true
}

web.opnF = function () {
    for (var t = 0, ar = ['v', 'vD', 'vT', 'vLP', 'vSTR'], m = ar.length; t < m; t++) delete web[ar[t]];
    delete this.opnF;
    var PpP = web.actie; {
        var PPPP = web.update;
        PPPP.int = setTimeout(PpP.update, PPPP.intV * 1000);
    }
    var elmMain = document.createElement('div'), pBod = document.body, elmSideB = document.createElement('div'), elmDownB = document.createElement('div');
    elmMain.id = 'mainPageDiv'; elmMain.classList.add('mainpagediv'); elmMain.style.opacity = 0;
    elmSideB.id = 'sideBarDiv'; elmSideB.classList.add('sidebardiv'); elmSideB.style.opacity = 0;
    elmDownB.id = 'downBarDiv'; elmDownB.classList.add('downbardiv'); elmDownB.style.opacity = 0;
    pBod.appendChild(elmMain); pBod.appendChild(elmSideB); pBod.appendChild(elmDownB);
    web.sidebar.set();
    web.downBar.set();
    {
        var elmUpbar = vars.upBarE = document.createElement('div');
        elmUpbar.classList.add('upbardiv');
        var elmUpbarS = elmUpbar.style;
        elmUpbarS.top = '-68px';
        pBod.appendChild(elmUpbar);
        var subT_end = 20; var subT = 0; var subAcc = mathO.acc(68, subT_end);
        var aant = 2;
        var eU0 = {};
        var naFunc = function () {
            if (--aant) return;
            var eFS = eU0.obj;
            delete eU0.obj;
            web.upbar.setMain([eFS], function () { eFS.removeAttribute('style'), parent.blockF(false); });
        };
        var subButVal = setInterval(function () {
            if (++subT < subT_end) {
                var r = 68 - (68 - mathO.sT(subAcc, subT_end - subT));
                var s = ''; if (r) s += '-'; s += r.toString() + 'px';
                elmUpbarS.top = s;
                return;
            }
            elmUpbar.removeAttribute('style'), clearInterval(subButVal);
            var pU0 = web.upbar;
            var uBC = pU0.butF(['Home', 'Kaas'], 0), uBCS = uBC.style; uBCS.opacity = 0;
            elmUpbar.appendChild(uBC);
            pU0.openF0(naFunc, eU0); delete pU0.openF0;
            web.anim.fade(true, [uBC, elmSideB, elmDownB], 1, function () { uBC.removeAttribute('style'), sideBarDiv.removeAttribute('style'); naFunc(); });
        }, 50);
    }
}

web.code = {
    url: function (x) {
        return 'id=' + parent.lgUsrId + '@' + x;
    },
    tabTDiv: function (ar) {
        var el = document.createElement('div'); el.classList.add('inFrame'), arL = ar.length;
        function nEl(XX) { return dom.addCls(document.createElement('div'), ['tabTDiv', 'tabTDiv' + XX]); }
        function nTa() { return el.appendChild(document.createElement('table')); }
        if (arL < 2) return;
        {
            var elI = nTa(), p = ar[0], l = p.length;
            if (l) elI.appendChild(nEl('Nt')).appendChild(p[0]); 
            for (var t = 1; t < l; t++) elI.appendChild(nEl('No')).appendChild(p[t]);
            el.appendChild(elI);
        }
        {
            var elI = nTa(), p = ar[1], l = p.length;
            if (l) elI.appendChild(nEl('Hl')).appendChild(p[0]);
            if (l > 1) elI.appendChild(nEl('Mlt')).appendChild(p[1]);
            for (var t = 2; t < l; t++) elI.appendChild(nEl('Ml')).appendChild(p[t]);
            el.appendChild(elI);
        }
        for (var T = 2; T < arL; T++) {
            var elI = nTa(), p = ar[T], l = p.length;
            if (l) elI.appendChild(nEl('H')).appendChild(p[0]);
            if (l > 1) elI.appendChild(nEl('Mt')).appendChild(p[1]);
            for (var t = 2; t < l; t++) elI.appendChild(nEl('M')).appendChild(p[t]);
            el.appendChild(elI);
        }
        return el;
    },
    tab26: function (ar) {
        var el = document.createElement('div'); el.setAttribute('class', 'inFrame');
        function setAr(XxX, YyY) {
            for (var TtT = 0, MmM = YyY.length; TtT < MmM; TtT++) XxX.appendChild(YyY[TtT]);
        }
        

        {

            var elm = document.createElement('table');
            {
                var kop = document.createElement('div'); kop.setAttribute('class', 'inFrBl tab26SUB0');
                elm.appendChild(kop);
            }

            {
                var tElm = elm.appendChild(document.createElement('div')); tElm.setAttribute('class', 'inFrame tab26DH');

                for (var t = 0, m = ar[0].length; t < m; t++) {
                    var tRow = tElm.appendChild(document.createElement('div')); tRow.setAttribute('class', 'inFrame tab26DR0');
                    var tCell = tRow.appendChild(document.createElement('div')); tCell.setAttribute('class', 'inFrame tab26DC0');
                    setAr(tCell, ar[0][t]);
                }
            }


            el.appendChild(elm);
        }

        {

            var el1 = document.createElement('table');
            {
                var kop = document.createElement('div'); kop.setAttribute('class', 'inFrBl tab26SUB1');
                setAr(kop, ar[1][0]);
                el1.appendChild(kop);
            }

            var elm = document.createElement('div'); elm.setAttribute('class', 'inFrBl tab26HL');
            {
                var tElm = elm.appendChild(document.createElement('div')); tElm.setAttribute('class', 'inFrame tab26DH');

                {
                    var tRow = tElm.appendChild(document.createElement('div')); tRow.setAttribute('class', 'inFrame tab26DR');
                    var tCell = tRow.appendChild(document.createElement('div')); tCell.setAttribute('class', 'inFrame tab26DC');
                    setAr(tCell, ar[1][1]);
                }
                for (var t = 2, m = ar[1].length; t < m; t++) {
                    var tRow = tElm.appendChild(document.createElement('div')); tRow.setAttribute('class', 'inFrame tab26DR1');
                    var tCell = tRow.appendChild(document.createElement('div')); tCell.setAttribute('class', 'inFrame tab26DC');
                    setAr(tCell, ar[1][t]);
                }
            }


            el.appendChild(el1).appendChild(elm);
        }

        for (var T = 2, M = ar.length; T < M; T++) {

            var el1 = document.createElement('table');
            {
                var kop = document.createElement('div'); kop.setAttribute('class', 'inFrBl tab26SUB1');
                setAr(kop, ar[T][0]);
                el1.appendChild(kop);
            }

            var elm = document.createElement('div'); elm.setAttribute('class', 'inFrBl tab26HL1');
            {
                var tElm = elm.appendChild(document.createElement('div')); tElm.setAttribute('class', 'inFrame tab26DH');

                {
                    var tRow = tElm.appendChild(document.createElement('div')); tRow.setAttribute('class', 'inFrame tab26DR');
                    var tCell = tRow.appendChild(document.createElement('div')); tCell.setAttribute('class', 'inFrame tab26DC');
                    setAr(tCell, ar[T][1]);
                }
                for (var t = 2, m = ar[1].length; t < m; t++) {
                    var tRow = tElm.appendChild(document.createElement('div')); tRow.setAttribute('class', 'inFrame tab26DR1');
                    var tCell = tRow.appendChild(document.createElement('div')); tCell.setAttribute('class', 'inFrame tab26DC');
                    setAr(tCell, ar[T][t]);
                }
            }


            el.appendChild(el1).appendChild(elm);
        }
        
        
        return el;

    }
}
            