web.window.homeIn = function (no, P) {
    var elm = this.newIn();
    var ar = []; {
        var b;
        if ((b = P.varDimNm[no]).length) ar.push([0, b]);
        if ((b = P.varNm[no]).length) ar.push([1, b]);
        if ((b = P.varOverig[no]).length) ar.push([2, b]);
    }
    for (var t = 0, m = ar.length; t < m; t++) {
        var E, aT = ar[t], aB = aT[0], aO = aT[1]; if (m === 1) E = elm;
        else this.header(function () { switch (aB) { case 0: return 'Dim'; case 1: return 'I/O'; } }(), elm),
            elm.appendChild(E = this.par(function () { if (t === m - 1) return false; else return true; }()));
        switch (aB) {
            case 0: if (no) {
                var M = aO.length, breed = false, hObj = document.createElement('div'), dObj = document.createElement('div'), d2Obj;
                hObj.classList.add('inFrBl'), dObj.classList.add('inFrIBl');
                if (M > 1) breed = true, (d2Obj = document.createElement('div')).classList.add('inFrIBl')
                for (var twee = 0; (!breed && !twee) || twee < 2; twee++)
                    for (var T = twee, aOO; T < M; T += 2) {
                        aOO = aO[T];
                        var Ar = [[]], ar2 = Ar[0];
                        {
                            var elm2;
                            ar2.push(elm2 = this.cell());
                            elm2.appendChild(elm2.appendChild(aOO[1]));
                            elm2.appendChild(document.createTextNode(' %'));
                            ar2.push(elm2 = this.cell());
                            elm2.appendChild(document.createTextNode('  ' + aOO[0] + (function () { if (breed && !twee) return '    '; else return ''; })()));
                        }
                        (function () { if (twee) return d2Obj; else return dObj; })().appendChild(this.tab0(Ar, function () { if (T + 2 >= M) return true; else return false; }()));
                    }
                hObj.appendChild(dObj); if (breed) hObj.appendChild(d2Obj);
                E.appendChild(hObj);
            }
            else E.appendChild(document.createTextNode('heejDim')); break;
            case 1:
                if (no) {
                    var M = aO.length, pSubNo = vars.cat.subNo, breed = false, hObj = document.createElement('div'), dObj = document.createElement('div'), d2Obj;
                    hObj.classList.add('inFrBl'), dObj.classList.add('inFrIBl');
                    if (M > 1) breed = true, (d2Obj = document.createElement('div')).classList.add('inFrIBl')
                    for (var twee = 0; (!breed && !twee) || twee < 2; twee++)
                        for (var T = twee, aOO; T < M; T += 2) {
                            function spaceFF() { if (breed && !twee) return true; else return false; }
                            aOO = aO[T];
                            var Ar = [[]], ar2 = Ar[0];
                            for (var tel = 0, elm2; tel < 5; tel++) {
                                ar2.push(elm2 = this.cell());
                                if (tel < 4)
                                    if (tel % 2) elm2.appendChild(document.createTextNode(function () { if (tel === 1) return 'Aan '; else return 'Uit  ' }()));
                                    else elm2.appendChild(aOO[1][mathO.floor(tel / 2)]);
                                else {

                                    var bBb, txtNde = document.createTextNode(aOO[0]);

                                    if ((bBb = 'N' + no.toString() + (mathO.floor(T / 10)).toString() + (T % 10).toString()) in pSubNo) {
                                        txtNde.nodeValue += ' '; elm2.appendChild(txtNde);
                                        {
                                            var eLm = document.createElement('div'); eLm.classList.add('subNoDiv'); eLm.appendChild(document.createTextNode('→'));
                                            bBb = pSubNo[bBb];
                                            (function (X, Y, Z) {
                                                eLm.onclick = function () { web.window.popUp(X, Y.window(Z), {}); };

                                            })(aOO[0] + function () { var xXx = P.naam[0][no + 1]; var uUu = ''; if (xXx.length && (uUu = xXx.charCodeAt(0)) > 64 && uUu < 91) uUu = ' ' + String.fromCharCode(uUu + 32); else uUu = ' ' + String.fromCharCode(uUu); for (var tTt = 1, mMm = xXx.length; tTt < mMm; tTt++) uUu += xXx.charAt(tTt); return uUu; }(),

                                                function () {
                                                switch (bBb.charCodeAt(0)) {
                                                    case 76: switch (bBb.charCodeAt(1)) {
                                                        case 80: return web.ledPl;
                                                            break;
                                                    } break;
                                                }
                                                }(), (bBb.charCodeAt(2) - 48) * 100 + (bBb.charCodeAt(3) - 48) * 10 + (bBb.charCodeAt(4) - 48));
                                            elm2.appendChild(eLm);
                                        }

                                        if (spaceFF()) txtNde = document.createTextNode('    '); else continue;
                                    }
                                    else if (spaceFF()) txtNde.nodeValue += '    ';
                                    elm2.appendChild(txtNde);
                                }
                            }
                            (function () { if (twee) return d2Obj; else return dObj; })().appendChild(this.tab(Ar));
                        }

                    hObj.appendChild(dObj); if (breed) hObj.appendChild(d2Obj);
                    E.appendChild(hObj);
                }
                else {
                    var M = aO.length, breed = false, hObj = document.createElement('div'), dObj = document.createElement('div'), d2Obj;
                    hObj.classList.add('inFrBl'), dObj.classList.add('inFrIBl');
                    if (M > 1) breed = true, (d2Obj = document.createElement('div')).classList.add('inFrIBl')
                    for (var twee = 0; (!breed && !twee) || twee < 2; twee++)
                        for (var T = twee, aOO; T < M; T += 2) {
                            aOO = aO[T];
                            var Ar = [[]], ar2 = Ar[0];
                            {
                                var elm2;
                                ar2.push(elm2 = this.cell());
                                var but = this.but(0, 'Aan'), fFunc = function (x) { but.setAttribute('onclick', 'web.actie.alg(' + function () { if (x) return 'true'; else return 'false'; }() + ', ' + T.toString() + ')'); }
                                elm2.appendChild(but);
                                elm2.appendChild(document.createTextNode(' '));
                                fFunc(true), but = this.but(1, 'Uit'), fFunc(false);
                                elm2.appendChild(but);
                                ar2.push(elm2 = this.cell());
                                elm2.appendChild(document.createTextNode('  ' + aOO[0] + (function () { if (breed && !twee) return '    '; else return ''; })()));
                            }
                            (function () { if (twee) return d2Obj; else return dObj; })().appendChild(this.tab0(Ar, function () { if (T + 2 >= M) return true; else return false; }()));
                        }
                    hObj.appendChild(dObj); if (breed) hObj.appendChild(d2Obj);
                    E.appendChild(hObj);
                }
                break;
        }
    }
    return this.new(P.naam[0][no + 1], elm, {});
};