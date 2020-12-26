web.actie = {
    alg: function (x, y) {
        this.updateF(function (pThis) {
            pThis.aFrameF('stwz?' + '0' + (mathO.floor(y / 10) % 10).toString() + (y % 10).toString() + '=' + (x * 1).toString());
            var P = vars.cat, pN = P.varNm, pDN = P.varDimNm, pN0 = pN[0][y][1 + (x = !x * 1)];
            for (var t = 0, p, s, m = pN0.length; t < m; t++) {
                var no = function () {
                    var uit = 0, tt = 1, mm = (s = (p = pN0[t])[0]).length;
                    while (tt < mm) uit += (s.charCodeAt(tt) - 48) * function () {
                        var U = 1; for (var tel = ++tt; tel !== mm; tel++) U *= 10; return U;
                    }(); return uit;
                }();
                switch (s.charAt(0)) {
                    case 'N': {
                        pN[mathO.floor(no / 100)][no % 100][1][!p[1] * 1].checked = true;
                    } break;
                    case 'D': {
                        pDN[mathO.floor(no / 100)][no % 100][1].value = mathO.cv16(mathO.cvV100(mathO.cvN100(p[1])));
                    } break;
                }
            }
        });
    },
    updateF: function (FUNC) {
        var pUp = web.update;
        clearTimeout(pUp.int);
        pUp.cnt = true;
        FUNC(this);
        pUp.int = setTimeout(this.update, pUp.intV2 * 1000);
    },
    algCat: function (x, y, pForm) {
        this.updateF(function (pThis) {
            pForm.checked = true;
            pThis.aFrameF('stwz@' + mathO.floor(y / 100).toString() + (mathO.floor(y / 10) % 10).toString() + (y % 10).toString() + '=' + (x * 1).toString());
        });
    },
    algCatD: function (x, y, pForm) {
        this.updateF(function (pThis) {
            pForm.value = x;
            pThis.aFrameF('sdwz@' + mathO.floor(y / 100).toString() + (mathO.floor(y / 10) % 10).toString() + (y % 10).toString() + '=' + x);
        });
    },
    aFrameF: function (src) {
        var elm = document.createElement('iframe'); elm.classList.add('aFrame');
        elm.setAttribute('onload', 'document.body.removeChild(this)');
        elm.src = web.code.url(src);
        document.body.appendChild(elm);
    },
    update: function () {
        var pUp = web.update;
        pUp.int = setTimeout(web.actie.update, pUp.intV * 1000);
        var elm = document.createElement('iframe'); elm.classList.add('aFrame');
        elm.setAttribute('onload', 'web.update.cnt = true, document.body.removeChild(this)');
        pUp.cnt = false;
        elm.src = web.code.url("update.htm");
        document.body.appendChild(elm);
    },
    updatePr: function (x) {
        var p;
        for (var t in x) {
            p = x[t]; switch (t) {
                case 'N': {
                    var pVN = vars.cat.varNm;
                    for (var T = 0, pT = p[T], m = p.length, pVNn = pVN[1]; T < m; pVNn = pVN[++T + 1], pT = p[T])
                        for (var TT = 0, mm = pT.length; TT < mm; TT++) pVNn[TT][1][!pT[TT] * 1].checked = true;
                } break;
                case 'D': {
                    var pVN = vars.cat.varDimNm;
                    for (var T = 0, pT = p[T], m = p.length, pVNn = pVN[1]; T < m; pVNn = pVN[++T + 1], pT = p[T])
                        for (var TT = 0, mm = pT.length, BbB0, BbB; TT < mm; TT++) if ((BbB = pVNn[TT][1]).value !== (BbB0 = mathO.cv16(mathO.cvV100(mathO.cvN100(pT[TT]))).toString())) BbB.value = BbB0;
                } break;
                case 'Te': {
                    var pVN = vars.cat.varTmpNm;
                    if (pVN.length === p.length) for (var T = 0, m = p.length, A, B; T < m; T++) if ((A = pVN[T][1]).nodeValue !== (B = p[T])) A.nodeValue = B;
                } break;
                case 'LdPl': {
                     for (var tt = 0, PP = web.ledPl, P = vars.cat.ledPlf, m = p.length; tt < m; tt++) {
                        for (var T = 0, pp = p[tt], p2 = P[tt], M = pp.length; T < M; T++) PP.updatePr(p2[T], pp[T], T);
                    }
                } break;
                case 'Str': this.mainStr.upF(p); break;
            }
        }
    }
};