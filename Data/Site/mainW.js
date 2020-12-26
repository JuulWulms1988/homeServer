web.window = {
    new: function (x, y, ob) {
        var elm = document.createElement('div'); elm.classList.add('windowdiv');
        var elm2 = document.createElement('div'); elm2.classList.add('windowdiv0');
        elm2.appendChild(document.createTextNode(x)); elm.appendChild(elm2);
        elm.appendChild(y); return elm;
    },
    newIn: function () {
        var elm = document.createElement('div'); elm.classList.add('windowdiv1'); return elm;
    },
    header: function (x, E) {
        var elm = document.createElement('div'); elm.classList.add('h');
        elm.appendChild(document.createTextNode(x)); E.appendChild(elm);
    },
    par: function (x) {
        var elm = document.createElement('div'), eC = elm.classList;
        eC.add('p'); if (x) eC.add('p2');
        return elm;
    },
    home: function (no, E) {
        var P = vars.cat; if (no) { E.appendChild(this.homeIn(no - 1, P)); return; }
        for (var t = 0, m = P.varNm.length; t < m; t++) E.appendChild(this.homeIn(t, P));
    },
    but: function (x, y) {
        var elm = dom.addCls(document.createElement('div'), ['divBut', 'But' + ['Gr', 'Rd', 'Bl', 'Rz'][x]]);
        elm.appendChild(document.createTextNode(y)); return elm;
    },
    popUp: function (x, y, ob) {
        parent.blockF(true);
        var elm2 = function (gGg) {
            var EeE = document.createElement('div'); EeE.onclick = function () { gGg.popOut(ob); }; EeE.setAttribute('class', 'container contT1'); return EeE;
        }(this), elm = elm2.appendChild(function () { var eEe = document.createElement('div'); eEe.setAttribute('class', 'contT'); return eEe;
    }()).appendChild(this.new (x, y, ob));
        elm.onclick = function (EE) { if (!('propArgF' in ob) || ob.propArgF()) EE.stopPropagation(); };
        elm.style.opacity = 0;
        vars.cat.varPop.push([document.body.appendChild(elm2), elm]);
        web.anim.fade(true, [elm], 1, function () { elm.removeAttribute('style'); parent.blockF(false); });
    },
    popOut: function (ob) {
        parent.blockF(true);
        if ('extPopF' in ob) ob.extPopF();
        var p = vars.cat.varPop, p2 = p[p.length - 1];
        p2[1].style.opacity = 1;
        web.anim.fade(false, [p2[1]], 1, function () { document.body.removeChild(p2[0]), p.pop(), parent.blockF(false); });
    },
    cell: function () { var elm = document.createElement('div'); elm.classList.add('divTD'); return elm; },
    tab: function (ar) {
        var elm = document.createElement('div'); elm.classList.add('divT');
        for (var t = 0, m = ar.length; t < m; t++) {
            var E = document.createElement('div'); E.classList.add('divTR');
            for (var tt = 0, mm = ar[t].length, k; tt < mm; tt++) E.appendChild(ar[t][tt]);
            elm.appendChild(E);
        }
        return elm;
    },
    tab0: function (ar, x) {
        var elm = document.createElement('div'); dom.addCls(elm, function () { var uit = ['divT']; if (!x) uit.push('divTRaE'); return uit; }());
            for (var t = 0, m = ar.length; t < m; t++) {
            var E = document.createElement('div'); E.classList.add('divTRa');
            for (var tt = 0, mm = ar[t].length, k; tt < mm; tt++) E.appendChild(ar[t][tt]);
            elm.appendChild(E);
        }
        return elm;
    },
    tab1: function (ar, x) {
        var elm = document.createElement('div'); dom.addCls(elm, function () { var uit = ['divT']; if (!x) uit.push('divTRaE'); return uit; }());
        for (var t = 0, m = ar.length; t < m; t++) {
            var E = document.createElement('div'); E.classList.add('divTRb');
            for (var tt = 0, mm = ar[t].length, k; tt < mm; tt++) E.appendChild(ar[t][tt]);
            elm.appendChild(E);
        }
        return elm;
    }
}