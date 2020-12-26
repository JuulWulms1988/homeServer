web.sidebar = {
    set: function () {
       (function (X) {
            switch (vars.upBarV[0]) {
                case 0: return X.set0;
            }
        })(this)(this, document.getElementById('sideBarDiv'));
    },
    set0: function (pThis, elm) {
        var pW = web.window;
        elm.appendChild(pW.new('Temperatuur', pThis.tempF(pW.newIn()), {}));
    },
    tempF: function (elm) {
        function nT(XX) { return document.createTextNode(XX); }
        var ar = [[], [nT('°C')]], ar0 = ar[0], ar1 = ar[1];
        for (var o = vars.cat.varTmpNm, ff, m = o.length, t = 0; t < m; t++) ar0.push(nT((ff = o[t])[0])), ar1.push(ff[1]);
        elm.appendChild(web.code.tabTDiv(ar)); return elm;
    }
}