var mathO = {
    cvCharCInt: function (x) {
        if (x > 47 && x < 58) return x - 48;
        else if (x > 64 && x < 91) return x - 55;
        return x - 61;
    },
    cvStrInt: function (x) {
        var rek = 1, t = x.length, uit = this.cvCharCInt(x.charCodeAt(--t));
        while (t) uit += this.cvCharCInt(x.charCodeAt(--t)) * (rek *= 60);
        return uit;
    },
    cvIntChar: function (x) {
        return String.fromCharCode((function () { if (x < 10) return 48; else if (x < 36) return 55; else return 61; })() + x);
    },
    cvIntStr: function (x) {
        var uit = this.cvIntChar(x % 60), reken = 60, rek, uit2 = '';
        while (rek = this.floor(x / reken) % 60) uit += this.cvIntChar(rek), reken *= 60;
        rek = uit.length; while (rek) uit2 += uit.charAt(--rek); return uit2;
    },
    floor: function (x) {
        if (x < 0)
            if ((x = -x - -x % 1) > 0) return -x;
            else return 0;
        return x - x % 1;
    },
    cvN100: function (x) {
	var uit; if (x) uit = 1; else uit = 0; while(uit < 100 && x >= this.floor((uit + 1) / 100 * 255)) uit++; return uit;
    },
    cvV100: function (x) {
        return this.floor(x / 100 * 255);
    },
    cv16: function (x) {
        function y(X) { return String.fromCharCode(function () { if (X > 9) return 97 + (X - 10); else return 48 + X; }()); }
        return y(this.floor(x / 16)) + y(x % 16);
    },
    cvPer: function (x) {
        if (!x) return '-';
        var z = 4800;
        var y = this.floor(x / z);
        if (!y) y = this.floor(x / (z = 80));
        var a = '';
        if (y) a += y.toString();
        if (y = x % z) {
            var esc = false;
            if (!esc)
                for (var t = 1; t < 8; t++)
                    if (t * z / 8 === y)
                        for (var tt = 4; tt >= 2; tt /= 2)
                            if ((y = this.floor(t / tt)) && !(t % tt)) {
                                x = y * 100 + 8 / tt;
                                break;
                            } else if (tt === 2) x = t * 100 + 8;
            a += '&frac' + (y = this.floor(x / 100)).toString() + (x % 100).toString() + ';';
        }
        if (z > 80) return a + '&nbspm';
        return a + '&nbsps';
    },
    macht: function (stelsel, demacht) {
        var uitkomst = 1;
        for (var t = 0; t < demacht; t++) uitkomst *= stelsel;
        return uitkomst;
    },
    diff: function (x, y) {
        if (x > y) return x - y;
        return y - x;
    },
    alphClr: {
        func: function (fac, cnt) {
            var out = [0, 0];
            out[1] = this.proc(20, cnt);
            for (var tel = 21; tel < 1000; tel++)
                if (out[tel % 2] === fac || mathO.diff(out[tel % 2], fac) < mathO.diff(out[[(tel + 1) % 2]] = this.proc(tel + 1, cnt), fac)) return tel - 1;
        },
        proc: function (x, cnt) {
            var out = 1000 - x;
            for (var t = 0; t < cnt - 1; t++) out = out * (1000 - (x = this.func2(x))) / 1000;
            return out;
        },
        func2: function (x) {
            return 1000 / (1000 / x + 1);
        }
    },
    hfdLttrSt: function (x, y) {
        var z = [65, 97];
        if (y.charCodeAt(0) < z[x * 1] || y.charCodeAt(0) >= z[x * 1] + 26) return y;
        var q = String.fromCharCode(y.charCodeAt(0) - z[x * 1] + z[!x * 1]);
        for (var t = 1; t < y.length; t++) q += y.charAt(t); return q;
    },
    acc: function (s, t) { return s / (t * t / 2); },
    sT: function (acc, arg) { return this.floor(acc * arg * arg / .002) / 1000; }
    

};
if ('ffBufDel0' in vars) {
    for (var t = 0, b = vars.ffBufDel0, a = ['cvNTIJDARF', 'cvNTIJD', 'cvNTIJDT', 'cvNClr', 'cvVClr', 'cvNClrS', 'cvVClrS']; t < 7; t++)
        mathO[a[t]] = b[t]; delete vars.ffBufDel0;
}

web.anim = {
    waitFOb: function (obj, key, func) {
        if (key in obj) func();
        else {
            var x = setInterval(function () {
                if (key in obj) {
                    clearInterval(x);
                    delete obj[key];
                    func();
                }
            }, 50);
        }
    },
    fade: function (inOut, el, t_end, func) {
        var t = []; t_end *= 20;
        for (var TTT = 0; TTT < el.length; TTT++)
            if (inOut && el[TTT].style.opacity > 0) t.push(mathO.floor(el[TTT].style.opacity * t_end));
            else if (!inOut && el[TTT].style.opacity < 1) t.push(mathO.floor((1 - el[TTT].style.opacity) * t_end));
            else t.push(0);
        var tim = setInterval(function () {
            for (var TEO = 0; TEO < el.length; TEO++) if (t[TEO] >= 0) {
                if (t[TEO] < t_end) t[TEO]++;
                if (t[TEO] < t_end)
                    if (inOut)
                        el[TEO].style.opacity = t[TEO] / t_end;
                    else el[TEO].style.opacity = 1 - t[TEO] / t_end;
                else { t[TEO] = -1; el[TEO].style.opacity = inOut * 1; }
            }
            for (var TEO = 0; TEO < el.length; TEO++) if (t[TEO] >= 0) return;
            clearInterval(tim); func();
        }, 50); return tim;
    }
};
var dom = {
    addCls: function (elm, x) {
        for (var t = 0, m = x.length, p = elm.classList; t < m; t++) p.add(x[t]); return elm;
    },
    getRec: function (x) {
        var y = x.classList;
        y.add('opaCls');
        var bd = document.body; bd.appendChild(x);
        var uit = x.getBoundingClientRect(); bd.removeChild(x), y.remove('opaCls');
        return uit;
    }
};
