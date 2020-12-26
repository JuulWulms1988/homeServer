web.downBar = {
    set: function () {
       (function (X) {
            switch (vars.upBarV[0]) {
                case 0: return X.set0;
            }
        })(this)(this, document.getElementById('downBarDiv'));
    },
    set0: function (pThis, elm) {
        var pW = web.window;
        for (var t = 0, Elm; t < 1; t++) {
            dom.addCls(Elm = elm.appendChild(document.createElement('div')), ['inFrIBl', 'fullHeight']);
            dom.addCls(Elm = Elm.appendChild(document.createElement('div')), ['inFrame', 'contT2']);
            dom.addCls(Elm = Elm.appendChild(document.createElement('div')), ['inFrame', 'contT3']);
            Elm.appendChild(function () {
                switch (t) {
                    case 0: return pW.new('Mediastreams', pThis.mainStrF(pW.newIn()), {});
                }
            } ());
        }
    },
    mainStrF: function (elm) {
        function nT(XX) { return document.createTextNode(XX); } var PpP = vars.cat.streams;
        elm.appendChild(web.code.tab26([[[nT('Audio')], [nT('Video')]], [[nT('Bron')], [PpP[0]], [PpP[1][1]]]]));
        return elm;
    },
}