web.actie.mainStr = {
    funcR: function (val, pThis) {
        web.actie.updateF(function (pThis2) {
            pThis.value = val;
            pThis2.aFrameF('Rstr@' + val);
        });    
    },
    funcS: function (val, valOld, pThis) {
        if (val !== 'z') {
            if (val === 'zz') { if (!valOld[0]) pThis.value = valOld[1]; }
            else web.actie.updateF(function (pThis2) {
                {
                    var YYY = vars.cat.streams[1][0];
                    YYY[0] = 0, YYY[1] = pThis.value = val, YYY = pThis.children;
                    if ((YYY = YYY[YYY.length - 1]).value === 'zz') pThis.removeChild(YYY);
                }
                pThis2.aFrameF('Sstr@' + val);
            }); return;
        } pThis.value = function () { if (!valOld[0]) return valOld[1]; return 'zz'; }();
        },
    upF: function (x) {
        var P = vars.cat.streams, B;
        P[0].value = x[0];
        (P = P[1])[0][0] = (x = x[1])[0], P[0][1] = x[1];
        {
            var B;
            if ((P = P[1])[B = P.options.length - 1].value === 'zz') {
                if (!x[0]) x.remove[B];
            }
            else if (x[0]) (B = P.appendChild(document.createElement('option'))).text = 'Specifiek', B.value = 'zz';
        }
        if (x[0]) P.value = 'zz'; else P.value = x[1];
    }
};